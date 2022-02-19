CC = gcc
LINKS = -lGL -lglfw -lX11 -lpthread -lXrandr -lXi -ldl
CFLAGS=-Werror -Wall
OUTPUT = ./output/main.o
INCLUDE_PATH = ./include

build:
	clear
	echo Building executable $(OUTPUT)
	$(CC) $(CFLAGS) -o $(OUTPUT) src/*.c src/**/*.c -I $(INCLUDE_PATH) $(LINKS)