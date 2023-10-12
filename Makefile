all:
	gcc sdl_test.c -o bin/sdl_test -I./include -L./lib -lmingw32 -lSDL2main -lSDL2