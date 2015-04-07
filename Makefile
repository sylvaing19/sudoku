debug:
	g++ -std=gnu++11 -Wall -g main.cpp src/*.cpp -o ./bin/Debug/sudoku -Iinclude -I/usr/include/SDL -lSDL -lSDL_image -lSDL_ttf -lSDL_gfx
	
release:
	g++ -std=gnu++11 -Wall main.cpp src/*.cpp -o ./bin/Release/sudoku -Iinclude -I/usr/include/SDL -lSDL -lSDL_image -lSDL_ttf -lSDL_gfx
