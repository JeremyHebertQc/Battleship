#include <assert.h>
#include <fstream>
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

// Méthode d'affichage de la grille
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

		_ships[i - 1].print(output);
	}
}

/******************************************************/
/* CODEZ ICI LES AUTRES MÉTHODES DE LA CLASSE "GRID". */
/******************************************************/
// Méthode privé
void Grid::hideShips()
{
	for (int i = 0; i < _nbShips; i++)
	{
		_ships[i].hide();
	}
}

// Constructeur
Grid::Grid()
{
	_gridOutline.setRectangle(GRID_INNER_MIN_X - 1, GRID_INNER_MIN_Y - 1, GRID_WIDTH, GRID_HEIGHT);
	_nbShips = 0;
	_nbMissedHits = 0;

	assert(initShips());
}

// Destructeur
Grid::~Grid()
{
	_nbShips = 0;
	_nbMissedHits = 0;
}

// Getter
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

// Méthode de vérification des tires
bool Grid::placeHit(const Point& hitPosition)
{
	// Vérification si le tire est dans la grille
	if ((hitPosition.getX() < GRID_INNER_MIN_X || hitPosition.getX() > GRID_INNER_MAX_X) || (hitPosition.getY() < GRID_INNER_MIN_Y || hitPosition.getY() > GRID_INNER_MAX_Y))
	{
		return false;
	}

	// Vérification si déjà tiré dans l'eau au même endroit
	for (int i = 0; i < _nbMissedHits; i++)
	{
		if (hitPosition == _missedHits[i])
			return false;
	}

	// Vérification l'emplacement du tire en fonction du navire
	for (int i = 0; i < _nbShips; i++)
	{
		switch (_ships[i].placeHit(hitPosition)) // Le navire regarde "Suis-je toucher?"
		{
		case MISSED_SHIP:  // Navire n'est pas touché
			continue;

		case SHIP_HIT: // Navire touché à un nouvel endroit (tire réussi)
			return true;

		case SHIP_SUNK: // Navire touché, mais déjà coulé
		case SHIP_HIT_TWICE: // Navire touché, mais déjà touché à cette emplacement
			return false;

		default: // Résultat inattendu, quitter le programme
			assert(true);
		}
	}

	// Si tire n'a touché aucun navire, mais tire quand même valide
	_missedHits[_nbMissedHits] = hitPosition;
	_missedHits[_nbMissedHits].setColor(GRID_MISSED_HITS_COLOR);
	_nbMissedHits++;
	return true;
}

// Méthode d'affichage de la grille
void Grid::draw(std::ostream& output) const
{
	// Affichage du contour
	_gridOutline.draw(output, 7); 

	// Affichage des navires
	for (int i = 0; i < _nbShips; i++)
	{
		_ships[i].draw(output);
	}

	// Affichage des tirs manqués
	for (int i = 0; i < _nbMissedHits; i++)
	{
		_missedHits[i].draw(output);
	}
}

// Méthode de saisie de la grille
void Grid::read(std::istream& input)
{
	while (!input.eof() && input.peek() != EOF) /*le eofbit du fstream ne devient jamais true parce qu'on essaie jamais de lire passe la fin du fichier donc aucune read operation echoue pour mettre ce bit a true donc on doit utilise le peek qui nous dit que nous somme a la fin du fichier*/
	{
		for (int i = 0; i < SHIP_MAX_NB; i++)
		{
			_ships[i].read(input);

			_nbShips++;
		}
	}
}

// Méthode d'importation des navires
bool Grid::initShips()
{
	std::ifstream monFlux;

	// Lecture du fichier
	ouvrirFichier(monFlux, GRID_SHIPS_FILENAME);
	read(monFlux);
	fermerFichier(monFlux);

	// Placement des navires
	if (placeShips())
	{
		hideShips();
		return true;
	}
	return false;
}


// Surcharge des opérateurs
std::ostream& operator<<(std::ostream& output, const Grid& grid)
{
	grid.draw(output);

	return output;
}

std::istream& operator>>(std::istream& input, Grid& grid)
{
	grid.read(input);

	return input;
}
