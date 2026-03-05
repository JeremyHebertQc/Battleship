#pragma once

#include <iostream>

#include "mesConstantes.h"
#include "grid.h"

class Game {
	private:
		Grid _grids[GAME_NB_PLAYERS];
		int _currentPlayerIndex;
		bool _gameOver;

	public:
		// Constructeur
		Game();

		// Destructeur
		~Game();

		// Autres méthodes
		void play(std::ostream& output);
		void draw(std::ostream& output) const;
};

// Surcharge des opérateurs
std::ostream& operator<<(std::ostream& output, const Game& game);