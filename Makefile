all: ReleaseLinux/sudoku

ReleaseLinux/sudoku:
	mkdir -p ReleaseLinux/
	g++ -std=gnu++11 -Wshadow main.cpp src/*.cpp -o ReleaseLinux/sudoku -Iinclude -I/usr/include/SDL -lSDL -lSDL_image -lSDL_ttf -lSDL_gfx

clean:
	rm -fr ReleaseLinux/
