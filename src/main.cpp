#include <iostream>

#include <graphics_setup.hpp>

using namespace std;

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600
#define WINDOW_TITLE "High Christmas Tree!"

int main(int argc, char *argv[]){

	Window window = Window(WINDOW_WIDTH, WINDOW_HEIGHT, (char*) WINDOW_TITLE);

	window.run();

	return 0;
}
