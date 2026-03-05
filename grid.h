#pragma once

#include <iostream>

#include "mesConstantes.h"
#include "Rect.h"
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
		
		// Méthodes privées
		bool initShips();
		bool placeShips();
		void hideShips();

	public:
		// Constructeur
		Grid();

		// Destructeur
		~Grid();

		// Getter
		int getNbRemainingShips() const;

		// Gestion des tirs
		bool placeHit(const Point& hitPosition);

		// Gestion de flux
		void printShipsStatus(std::ostream& output) const;
		void draw(std::ostream& output) const;
		void read(std::istream& input);
};

// Surchage des opérateurs
std::ostream& operator<<(std::ostream& output, const Grid& grid); // Méthode d'affichage de la grille
std::istream& operator>>(std::istream& input, Grid& grid); // Méthode de saisie de la grille