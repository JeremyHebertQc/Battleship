#include "game.h"

/***********************************************/
/* CODEZ ICI LES MÉTHODES DE LA CLASSE "GAME". */
/***********************************************/

Game::Game()
{
	_currentPlayerIndex = 0;
	_gameOver = false;

	srand(time(NULL));
}

Game::~Game()
{
	_currentPlayerIndex = 0;
	_gameOver = true;
}

void Game::play(std::ostream& sortie)
{
	while (!_gameOver)
	{
		//*this->draw(std::cout);

		//while()
	}
}