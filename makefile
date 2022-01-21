CC = gcc
CFLAGS = -lglfw -lGL -lX11 -lpthread -lXrandr -lXi -ldl
OUTPUT = ./output/main.o
INPUT = ./src/main.c ./src/lib/glad.c
INCLUDE_PATH = ./include

build:
	echo Building executable $(OUTPUT)
	$(CC) $(CFLAGS) -I $(INCLUDE_PATH) -o $(OUTPUT) $(INPUT)