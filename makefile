CC = gcc
LINKS = -lGL -lglfw -lX11 -lpthread -lXrandr -lXi -ldl -lm
CFLAGS=-Werror -Wall
OUTPUT = ./output/main.o

build:
	clear
	echo Building executable $(OUTPUT)
	$(CC) $(CFLAGS) -o $(OUTPUT) src/*.c src/**/*.c -I ./include $(LINKS)