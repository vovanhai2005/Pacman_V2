#include "Game.h"
#include "../Object/Texture.h"

int main(int argc, char *args[])
{
	Game *game = new Game();

	game-> initSDL();

	game -> runGame();

	game-> quitSDL();

	return 1;
}