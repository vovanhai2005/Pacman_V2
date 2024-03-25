#include <Game.h>

int main(int argc , char* argc[])
{
	Window* window = new Window();

	window -> initSDL();

	window -> runGame();

	window -> quitSDL();

	return 0;
}