#pragma once

#include <iostream>
#include "mesConstantes.h"
#include "rect.h" // Ajoutez vos fichiers "rect.h" et "rect.cpp" développés dans un laboratoire précédent
#include "ship.h"

/********************************/
/* NE MODIFIEZ PAS CE FICHIER ! */
/* IL EST DÉJÀ COMPLET !        */
/********************************/
class Grid {
	private:
		Rect _gridOutline;
		Ship _ships[SHIP_MAX_NB];
		Point _missedHits[GRID_WIDTH * GRID_HEIGHT];
		int _nbShips,
			_nbMissedHits;

		bool initShips();
		bool placeShips();
		void hideShips();

	public:
		Grid();
		~Grid();
		int getNbRemainingShips() const;
		bool placeHit(const Point& hitPosition);
		void printShipsStatus(std::ostream& output) const;
		void draw(std::ostream& output) const;
		void read(std::istream& input);
};

std::ostream& operator<<(std::ostream& output, const Grid& grid);
std::istream& operator>>(std::istream& input, Grid& grid);