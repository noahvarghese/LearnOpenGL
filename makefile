SHELL := /bin/bash
CC := gcc
LINKS := -lGL -lglfw -lX11 -lpthread -lXrandr -lXi -ldl -lm
CFLAGS := -Werror -Wall
OUTPUT := ./bin/main.bin

CGLM_VERSION := 0.8.4

build: clear
	$(CC) $(CFLAGS) -o $(OUTPUT) src/*.c src/**/*.c -I ./include $(LINKS)

clear:
	if [ -n "${TERM}" ]; then clear; fi