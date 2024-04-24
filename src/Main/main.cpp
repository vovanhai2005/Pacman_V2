#include "Game.h"
#include "../Object/Texture.h"
using namespace std;
int main(int argc, char *args[])
{
	Game *game = new Game();
	cout << "Created game\n";
	game-> initSDL();
	cout << "Init SDL\n";
	game -> runGame();
	
	game-> quitSDL();

	return 1;
}