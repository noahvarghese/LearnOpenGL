CC = gcc
LINKS = -lglfw -lGL -lX11 -lpthread -lXrandr -lXi -ldl
CFLAGS=-Werror -Wall
OUTPUT = ./output/main.o
INPUT = ./src/main.c ./src/lib/glad.c
INCLUDE_PATH = ./include

build:
	echo Building executable $(OUTPUT)
	$(CC) $(CFLAGS) -o $(OUTPUT) $(INPUT) $(LINKS) -I $(INCLUDE_PATH)