#include <windows.h>

#include "grid.h"
#include "game.h"
#include "mesFonctions.h"

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
	_gameOver = false;
}

void Game::play(std::ostream& output)
{
	do
	{
		_currentPlayerIndex = _currentPlayerIndex % (2);

		do
		{
			draw(output);
		} while (!_grids[_currentPlayerIndex].placeHit(getMouseClick()));

		draw(output);
		sleepMs(500);

		ignoreMouseClicks(); // clear the input record accumulated during sleep

		if (_grids[_currentPlayerIndex].getNbRemainingShips() > 0)
			_currentPlayerIndex++;
		else
			_gameOver = true;
		
	} while (!_gameOver);
	

	
}

void Game::draw(std::ostream& output) const
{
	clearScreen(output);

	output << "JEU DE BATTLESHIP : cliquez dans la grille pour tirer" << std::endl << std::endl
		<< "TOUR DU JOUEUR " << _currentPlayerIndex + 1;
	_grids[_currentPlayerIndex].draw(output);
	_grids[_currentPlayerIndex].printShipsStatus(output);
}

std::ostream& operator<<(std::ostream& output, const Game& game)
{
	game.draw(output);

	return output;
}
