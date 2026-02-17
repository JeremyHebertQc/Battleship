#include "grid.h"

using namespace std;

/***********************************************/
/* NE MODIFIEZ PAS LES MÉTHODES QUI SUIVENT !  */
/* ELLES SONT DÉJÀ PLEINEMENT FONCTIONNELLES ! */
/***********************************************/
bool Grid::placeShips() {
	bool collides;
	int maxX, maxY;

	for (int i = 0; i < _nbShips; i++) {
		do {
			if ((_ships[i].getLength() > (GRID_WIDTH - 2)) ||
				(_ships[i].getLength() > (GRID_HEIGHT - 2))) {
				return false;
			}

			collides = false;
			_ships[i].setDirection(Direction(rand() % 2));

			if (_ships[i].getDirection() == HORIZONTAL) {
				maxX = GRID_INNER_MAX_X - _ships[i].getLength();
				maxX = ((maxX < GRID_INNER_MIN_X) ? GRID_INNER_MIN_X : maxX);
				maxY = GRID_INNER_MAX_Y;
			}

			else {
				maxX = GRID_INNER_MAX_X;
				maxY = GRID_INNER_MAX_Y - _ships[i].getLength();
				maxY = ((maxY < GRID_INNER_MIN_Y) ? GRID_INNER_MIN_Y : maxY);
			}

			const int randX = (rand() % (maxX - GRID_INNER_MIN_X + 1) + GRID_INNER_MIN_X);
			const int randY = (rand() % (maxY - GRID_INNER_MIN_Y + 1) + GRID_INNER_MIN_Y);
			_ships[i].setPosition(randX, randY);

			for (int j = 0; j < i; j++) {
				if ((i != j) && _ships[i].checkCollision(_ships[j])) {
					collides = true;
					break;
				}
			}
		} while (collides);
	}

	return true;
}

void Grid::printShipsStatus(ostream& output) const {
	goToXY(GRID_SHIPS_STATUS_X, GRID_SHIPS_STATUS_Y);
	output << "BATEAUX RESTANTS";

	goToXY((GRID_SHIPS_STATUS_X + 23), GRID_SHIPS_STATUS_Y);
	output << "BATEAUX COULES";

	for (int i = 1; i <= _nbShips; i++) {
		if (_ships[i - 1].getSunkStatus()) {
			goToXY((GRID_SHIPS_STATUS_X + 23), (GRID_SHIPS_STATUS_Y + i));
		} else {
			goToXY((GRID_SHIPS_STATUS_X), (GRID_SHIPS_STATUS_Y + i));
		}

		_ships[i - 1].print(output);
	}
}

/******************************************************/
/* CODEZ ICI LES AUTRES MÉTHODES DE LA CLASSE "GRID". */
/******************************************************/