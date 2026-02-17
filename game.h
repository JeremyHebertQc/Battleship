#pragma once

#include <iostream>
#include "mesConstantes.h"
#include "grid.h"

/********************************/
/* NE MODIFIEZ PAS CE FICHIER ! */
/* IL EST DÉJÀ COMPLET !        */
/********************************/
class Game {
	private:
		Grid _grids[GAME_NB_PLAYERS];
		int _currentPlayerIndex;
		bool _gameOver;

	public:
		Game();
		~Game();

		void play(std::ostream& sortie);
		void draw(std::ostream& output) const;
};

std::ostream& operator<<(std::ostream& output, const Game& game);