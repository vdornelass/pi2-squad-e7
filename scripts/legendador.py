import os
import re
import subprocess
import cv2
import numpy as np
from PIL import Image, ImageDraw, ImageFont

FFMPEG_PATH = r"C:\Program Files\Studio 2.0\PhotoRealisticRenderer\win\64\ffmpeg.exe"
FONT_PATH = r"C:\Windows\Fonts\arial.ttf"

def parse_srt(srt_path):
    subtitles = []
    with open(srt_path, "r", encoding="utf-8") as f:
        content = f.read()

    blocks = re.split(r"\n\s*\n", content.strip())
    for block in blocks:
        lines = block.strip().split("\n")
        if len(lines) >= 3:
            time_match = re.match(
                r"(\d{2}):(\d{2}):(\d{2})[,.](\d{3})\s*-->\s*(\d{2}):(\d{2}):(\d{2})[,.](\d{3})",
                lines[1].strip()
            )
            if time_match:
                h1, m1, s1, ms1, h2, m2, s2, ms2 = map(int, time_match.groups())
                start_sec = h1 * 3600 + m1 * 60 + s1 + ms1 / 1000.0
                end_sec = h2 * 3600 + m2 * 60 + s2 + ms2 / 1000.0
                text = " ".join([l.strip() for l in lines[2:]])
                subtitles.append((start_sec, end_sec, text))
    return subtitles

def get_active_subtitle(subtitles, current_sec):
    for start, end, text in subtitles:
        if start <= current_sec <= end:
            return text
    return None

def wrap_text(text, font, max_width, draw):
    words = text.split()
    lines = []
    current_line = []
    for word in words:
        test_line = " ".join(current_line + [word])
        bbox = draw.textbbox((0, 0), test_line, font=font)
        w = bbox[2] - bbox[0]
        if w <= max_width:
            current_line.append(word)
        else:
            if current_line:
                lines.append(" ".join(current_line))
                current_line = [word]
            else:
                lines.append(word)
                current_line = []
    if current_line:
        lines.append(" ".join(current_line))
    return lines

def burn_subtitles_to_video(input_video_path, srt_path, output_video_path):
    if not os.path.exists(input_video_path):
        raise FileNotFoundError(f"Vídeo de entrada não encontrado: {input_video_path}")
    if not os.path.exists(srt_path):
        raise FileNotFoundError(f"Arquivo SRT não encontrado: {srt_path}")

    subtitles = parse_srt(srt_path)
    cap = cv2.VideoCapture(input_video_path)
    if not cap.isOpened():
        raise RuntimeError("Não foi possível abrir o vídeo de entrada.")

    width = int(cap.get(cv2.CAP_PROP_FRAME_WIDTH))
    height = int(cap.get(cv2.CAP_PROP_FRAME_HEIGHT))
    fps = cap.get(cv2.CAP_PROP_FPS) or 30.0
    total_frames = int(cap.get(cv2.CAP_PROP_FRAME_COUNT))

    temp_video = "temp_burned_video.mp4"
    temp_audio = "temp_audio.aac"

    # Extrai áudio original se houver
    has_audio = False
    audio_cmd = [FFMPEG_PATH, "-y", "-i", input_video_path, "-vn", "-acodec", "copy", temp_audio]
    try:
        res = subprocess.run(audio_cmd, capture_output=True)
        if res.returncode == 0 and os.path.exists(temp_audio) and os.path.getsize(temp_audio) > 100:
            has_audio = True
    except Exception:
        has_audio = False

    fourcc = cv2.VideoWriter_fourcc(*"mp4v")
    out = cv2.VideoWriter(temp_video, fourcc, fps, (width, height))

    # Tamanho da fonte proporcional à altura
    font_size = max(20, int(height * 0.04))
    font = ImageFont.truetype(FONT_PATH, font_size)

    frame_idx = 0
    print(f"Processando {total_frames} frames a {fps:.1f} FPS ({width}x{height})...")

    while True:
        ret, frame = cap.read()
        if not ret:
            break

        current_sec = frame_idx / fps
        sub_text = get_active_subtitle(subtitles, current_sec)

        if sub_text:
            # Converte BGR para RGB para o Pillow
            rgb_frame = cv2.cvtColor(frame, cv2.COLOR_BGR2RGB)
            img = Image.fromarray(rgb_frame)
            draw = ImageDraw.Draw(img, "RGBA")

            # Quebra texto se necessário
            max_w = int(width * 0.85)
            lines = wrap_text(sub_text, font, max_w, draw)

            line_height = int(font_size * 1.35)
            total_text_h = len(lines) * line_height
            bottom_margin = int(height * 0.08)
            start_y = height - bottom_margin - total_text_h

            # Fundo semitransparente escuro
            pad_x = 24
            pad_y = 12
            max_line_w = 0
            for l in lines:
                bbox = draw.textbbox((0, 0), l, font=font)
                w = bbox[2] - bbox[0]
                if w > max_line_w:
                    max_line_w = w

            box_x0 = (width - max_line_w) // 2 - pad_x
            box_y0 = start_y - pad_y
            box_x1 = (width + max_line_w) // 2 + pad_x
            box_y1 = start_y + total_text_h + pad_y

            draw.rounded_rectangle(
                [box_x0, box_y0, box_x1, box_y1],
                radius=10,
                fill=(0, 0, 0, 190)
            )

            # Desenha linhas centralizadas em branco com contorno preto suave
            cur_y = start_y
            for l in lines:
                bbox = draw.textbbox((0, 0), l, font=font)
                lw = bbox[2] - bbox[0]
                cur_x = (width - lw) // 2
                draw.text((cur_x, cur_y), l, font=font, fill=(255, 255, 255, 255))
                cur_y += line_height

            frame = cv2.cvtColor(np.array(img), cv2.COLOR_RGB2BGR)

        out.write(frame)
        frame_idx += 1
        if frame_idx % 150 == 0:
            pct = (frame_idx / total_frames) * 100 if total_frames > 0 else 0
            print(f"Progresso: {pct:.1f}% ({frame_idx}/{total_frames})")

    cap.release()
    out.release()

    # Junta com áudio se existia
    if has_audio:
        merge_cmd = [
            FFMPEG_PATH, "-y",
            "-i", temp_video,
            "-i", temp_audio,
            "-c:v", "copy",
            "-c:a", "copy",
            output_video_path
        ]
        subprocess.run(merge_cmd, check=True, capture_output=True)
        if os.path.exists(temp_audio):
            os.remove(temp_audio)
    else:
        if os.path.exists(output_video_path):
            os.remove(output_video_path)
        os.rename(temp_video, output_video_path)

    if os.path.exists(temp_video):
        os.remove(temp_video)

    print(f"Vídeo com legendas embutidas gerado com sucesso: {output_video_path}")
    return output_video_path

if __name__ == "__main__":
    import sys
    if len(sys.argv) >= 4:
        burn_subtitles_to_video(sys.argv[1], sys.argv[2], sys.argv[3])
    else:
        print("Uso: python legendador.py <video_entrada.mp4> <legendas.srt> <video_saida.mp4>")
