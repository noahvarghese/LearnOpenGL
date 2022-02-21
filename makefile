CC = gcc
LINKS = -lGL -lglfw -lX11 -lpthread -lXrandr -lXi -ldl -lm
CFLAGS=-Werror -Wall
OUTPUT = ./bin/main.bin

build:
	if [ -n "${TERM}" ]; then clear; fi
	echo Building executable $(OUTPUT)
	$(CC) $(CFLAGS) -o $(OUTPUT) src/*.c src/**/*.c -I ./include $(LINKS)
