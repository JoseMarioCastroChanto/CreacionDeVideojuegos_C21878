CC=g++
STD=-std=c++17
CFLAGS=-Wall
INC_PATH=-I./libs
SRC=src/*.cpp
LFLAGS=-lSDL2 -lSDL2_image -lSDL2_ttf -lSDL2_mixer -llua5.3
EXEC=intro

.PHONY: build run clean

build:
	$(CC) $(CFLAGS) $(STD) $(INC_PATH) $(SRC) $(LFLAGS) -o $(EXEC)

run: build
	./$(EXEC)

clean:
	rm -f $(EXEC)
