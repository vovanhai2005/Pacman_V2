all: main run 

main: src/main.cpp
	g++ -Iinclude -Iinclude/SDL2 -Iinclude/headers -Llib src/*.cpp -o main.exe -lmingw32 -lSDL2main -lSDL2 -lSDL2_image -lSDL2_mixer -lSDL2_ttf

run: main 
	./main.exe

.PHONY: all run