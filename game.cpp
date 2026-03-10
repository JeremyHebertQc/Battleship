#include <windows.h>

#include "grid.h"
#include "game.h"
#include "mesFonctions.h"

// Constructeur
Game::Game()
{
	_currentPlayerIndex = 0;
	_gameOver = false;

	srand(time(NULL));
}

// Destructeur
Game::~Game()
{
	_currentPlayerIndex = 0;
	_gameOver = true;
}

// Autres méthodes
void Game::play(std::ostream& output)
{
	displayCursor(false);
	while (!_gameOver)
	{
		_currentPlayerIndex = _currentPlayerIndex % (2);

		do
		{
			draw(output); // Afficher la partie
		} while (!_grids[_currentPlayerIndex].placeHit(getMouseClick())); // Obtenir et tester la position

		draw(output); // Afficher la partie
		sleepMs(500); // attendre 500Ms

		ignoreMouseClicks(); // Ignorer les clics de souris survenus durant l'attente

		if (_grids[_currentPlayerIndex].getNbRemainingShips() > 0)
			_currentPlayerIndex++;
		else
			_gameOver = true;
	}

	// Affichage du message de fin
	displayCursor(true);
	draw(output);
}

void Game::draw(std::ostream& output) const
{
	clearScreen(output);

	if (_gameOver)
	{
		output << "VICTOIRE DU JOUEUR " << _currentPlayerIndex + 1 << std::endl
			<< "Merci d'avoir joue !" << std::endl
			<< std::endl << std::endl
			<< "Appuyez sur une touche pour fermer le jeu...";
		system("pause>NUL");
	}
	else
	{
		output << "JEU DE BATTLESHIP : cliquez dans la grille pour tirer" << std::endl
			<< std::endl
			<< "TOUR DU JOUEUR " << _currentPlayerIndex + 1;

		_grids[_currentPlayerIndex].draw(output);
		_grids[_currentPlayerIndex].printShipsStatus(output);
	}
	
}

void Game::displayCursor(bool interrupter)
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO cci;
	GetConsoleCursorInfo(hConsole, &cci);
	cci.bVisible = interrupter;
	SetConsoleCursorInfo(hConsole, &cci);
}

// Surcharge des opérateurs
std::ostream& operator<<(std::ostream& output, const Game& game)
{
	game.draw(output);

	return output;
}