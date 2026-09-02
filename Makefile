CC = gcc
CFLAGS = -Wall -Wextra -std=c99 -pedantic
TARGET = bin/jogo
SRCS = src/main.c

all: $(TARGET)

$(TARGET): $(SRCS)
	@mkdir -p bin
	$(CC) $(CFLAGS) $(SRCS) -o $(TARGET)

run: all
	./$(TARGET)

clean:
	rm -f bin/jogo bin/*.o bin/*.exe
	@echo "Limpeza concluida."

.PHONY: all run clean