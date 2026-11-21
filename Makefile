CC = gcc
WIN_CC ?= x86_64-w64-mingw32-gcc
CFLAGS = -Wall -Wextra -std=c99 -pedantic -Iinclude -Isrc
TARGET = bin/jogo
SRCS = src/main.c src/player.c src/boss.c src/bullet.c src/typing_engine.c src/ui.c src/save.c src/game_state.c src/ranking.c src/audio.c src/tutorial.c src/report.c

# Deteccao de Sistema Operacional
UNAME_S := $(shell uname -s 2>/dev/null || echo Windows)

ifeq ($(UNAME_S), Linux)
    LDFLAGS = -Llib -Wl,-rpath,'$$ORIGIN/../lib' -lraylib -lm -lpthread -ldl
else
    # Windows MinGW
    LDFLAGS = -Llib -lraylib -lopengl32 -lgdi32 -lwinmm
endif

all: $(TARGET)

$(TARGET): $(SRCS)
	@mkdir -p bin
	$(CC) $(CFLAGS) $(SRCS) $(LDFLAGS) -o $(TARGET)
	@cp lib/raylib.dll bin/ 2>/dev/null || true
	@echo "Compilacao do AI Safety em C (Raylib) concluida com sucesso!"

run: all
ifeq ($(UNAME_S), Linux)
	LD_LIBRARY_PATH=lib:$$LD_LIBRARY_PATH ./$(TARGET)
else
	./$(TARGET)
endif

windows: $(SRCS)
	@mkdir -p bin
	@x86_64-w64-mingw32-windres src/icon.rc -O coff -o bin/icon.res 2>/dev/null || true
	$(WIN_CC) $(CFLAGS) $(SRCS) bin/icon.res -Llib -lraylib -lopengl32 -lgdi32 -lwinmm -static-libgcc -o bin/jogo.exe
	@cp bin/jogo.exe AI_Safety.exe 2>/dev/null || true
	@cp lib/raylib.dll bin/ 2>/dev/null || true
	@echo "Compilacao nativa para Windows (bin/jogo.exe e AI_Safety.exe) concluida com sucesso!"

test-lmc:
	@mkdir -p bin
	$(CC) $(CFLAGS) tests/test_logica_lmc.c src/typing_engine.c src/boss.c src/bullet.c src/player.c src/ui.c $(LDFLAGS) -o bin/test_lmc
	LD_LIBRARY_PATH=lib:$$LD_LIBRARY_PATH ./bin/test_lmc

verificar-certificado:
	@mkdir -p bin
	$(CC) $(CFLAGS) tests/verificar_certificado.c src/report.c src/ui.c src/typing_engine.c src/boss.c src/bullet.c src/player.c $(LDFLAGS) -o bin/verificar_certificado
	LD_LIBRARY_PATH=lib:$$LD_LIBRARY_PATH ./bin/verificar_certificado

clean:
	rm -f bin/jogo bin/test_lmc bin/verificar_certificado bin/*.o bin/*.exe
	@echo "Limpeza concluida."

.PHONY: all run clean windows test-lmc verificar-certificado
