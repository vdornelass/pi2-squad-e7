CC = gcc
CFLAGS = -Wall -Wextra -std=c99 -pedantic -Iinclude -Isrc
TARGET = bin/jogo
SRCS = src/main.c src/player.c src/boss.c src/bullet.c src/typing_engine.c src/ui.c src/save.c src/game_state.c src/ranking.c

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
	x86_64-w64-mingw32-gcc $(CFLAGS) $(SRCS) -Llib -lraylib -lopengl32 -lgdi32 -lwinmm -o bin/jogo.exe
	@cp lib/raylib.dll bin/ 2>/dev/null || true
	@echo "Compilacao nativa para Windows (bin/jogo.exe) concluida com sucesso!"

clean:
	rm -f bin/jogo bin/*.o bin/*.exe
	@echo "Limpeza concluida."

.PHONY: all run clean windows
