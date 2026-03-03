#include <assert.h>
#include "grid.h"

/***********************************************/
/* NE MODIFIEZ PAS LES MÉTHODES QUI SUIVENT !  */
/* ELLES SONT DÉJÀ PLEINEMENT FONCTIONNELLES ! */
/***********************************************/
bool Grid::placeShips()
{
	bool collides;
	int maxX, maxY;

	for (int i = 0; i < _nbShips; i++)
	{
		do
		{
			if ((_ships[i].getLength() > (GRID_WIDTH - 2)) || (_ships[i].getLength() > (GRID_HEIGHT - 2)))
			{
				return false;
			}

			collides = false;
			_ships[i].setDirection(Direction(rand() % 2));

			if (_ships[i].getDirection() == HORIZONTAL)
			{
				maxX = GRID_INNER_MAX_X - _ships[i].getLength();
				maxX = ((maxX < GRID_INNER_MIN_X) ? GRID_INNER_MIN_X : maxX);
				maxY = GRID_INNER_MAX_Y;
			}
			else
			{
				maxX = GRID_INNER_MAX_X;
				maxY = GRID_INNER_MAX_Y - _ships[i].getLength();
				maxY = ((maxY < GRID_INNER_MIN_Y) ? GRID_INNER_MIN_Y : maxY);
			}

			const int randX = (rand() % (maxX - GRID_INNER_MIN_X + 1) + GRID_INNER_MIN_X);
			const int randY = (rand() % (maxY - GRID_INNER_MIN_Y + 1) + GRID_INNER_MIN_Y);
			_ships[i].setPosition(randX, randY);

			for (int j = 0; j < i; j++)
			{
				if ((i != j) && _ships[i].checkCollision(_ships[j]))
				{
					collides = true;
					break;
				}
			}
		} while (collides);
	}

	return true;
}

void Grid::printShipsStatus(std::ostream& output) const
{
	goToXY(GRID_SHIPS_STATUS_X, GRID_SHIPS_STATUS_Y);
	output << "BATEAUX RESTANTS";

	goToXY((GRID_SHIPS_STATUS_X + 23), GRID_SHIPS_STATUS_Y);
	output << "BATEAUX COULES";

	for (int i = 1; i <= _nbShips; i++)
	{
		if (_ships[i - 1].getSunkStatus())
		{
			goToXY((GRID_SHIPS_STATUS_X + 23), (GRID_SHIPS_STATUS_Y + i));
		}
		else
		{
			goToXY((GRID_SHIPS_STATUS_X), (GRID_SHIPS_STATUS_Y + i));
		}

		//_ships[i - 1].print(output);
	}
}

/******************************************************/
/* CODEZ ICI LES AUTRES MÉTHODES DE LA CLASSE "GRID". */
/******************************************************/

Grid::Grid()
{
	_gridOutline.setRectangle(GRID_INNER_MIN_X - 1, GRID_INNER_MIN_Y - 1, GRID_WIDTH, GRID_HEIGHT);
	_nbShips = 0;
	_nbMissedHits = 0;

	initShips();
}

Grid::~Grid()
{
	_nbShips = 0;
	_nbMissedHits = 0;
}

int Grid::getNbRemainingShips() const
{
	unsigned int nbRemainingShips = _nbShips;

	for (int i = 0; i < _nbShips; i++)
	{
		if (_ships[i].getSunkStatus())
		{
			nbRemainingShips--;
		}
	}

	return nbRemainingShips;
}

bool Grid::placeHit(const Point& hitPosition)
{
	// Vérification si dedans tableau
	if ((hitPosition.getX() < GRID_INNER_MIN_X || hitPosition.getX() > GRID_INNER_MAX_X) || (hitPosition.getY() < GRID_INNER_MIN_Y))
	{
		return false;
	}

	// Vérification si déjà tiré dans l'eau a cette endroit la
	for (int i = 0; i < _nbMissedHits; i++)
	{
		if (hitPosition == _missedHits[i])
			return false;
	}

	// Vérification l'emplacement du tire si...
	for (int i = 0; i < _nbShips; i++)
	{
		switch (_ships[i].placeHit(hitPosition)) // Le bateau qui regarde "Suis-je toucher ?"
		{
		case MISSED_SHIP:  // ... touche pas le bateau *MISSED_SHIP*
			continue;

		case SHIP_HIT: // ... touche un bateau a un endroit qu'il était pas toucher *ship hit*
			return true;

		case SHIP_SUNK: // ... touche un bateau couler *ship sunk*
		case SHIP_HIT_TWICE: // ... touche une deuxième fois *ship hit twice*
			return false;

		default: // ERROR!!! GIVE UP!!!
			assert(true);
		}
	}

	// Si tire à touché aucun bateau
	_missedHits[_nbMissedHits] = hitPosition;
	_missedHits[_nbMissedHits].setColor(GRID_MISSED_HITS_COLOR);
	_nbMissedHits++;
	return true;
}

bool Grid::initShips()
{
	_nbShips++;
	_ships[0] = Ship("existe", 1);
	_ships[0].setPosition(9, 9);
	_ships[1] = Ship("stan", 1);
	_ships[1].setPosition(7, 7);

	_nbShips++;
	return false;
}