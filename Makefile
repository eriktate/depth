SRC = src/*.c lib/*.c
OBJ_NAME = depth
LANG_STANDARD = c99
STATIC_LIBS = `pkg-config --static --libs glfw3`
CC = gcc
CFLAGS = -Wall -g
CPATH = ./include:./src

all:
	make build
	make run

clean:
	rm -f bin/*

build:
	CPATH=$(CPATH) $(CC) $(SRC) $(STATIC_LIBS) $(CFLAGS) -std=$(LANG_STANDARD) -o bin/$(OBJ_NAME)

run:
	bin/$(OBJ_NAME)

.PHONY: all clean build run
