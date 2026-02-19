#include "ship.h"

/********************************************/
/* NE MODIFIEZ PAS LA MÉTHODE QUI SUIT !    */
/* ELLE EST DÉJÀ PLEINEMENT FONCTIONNELLE ! */
/********************************************/
void Ship::updatePoints() {
	for (int i = 0; i < _length; i++) {
		if (_direction == HORIZONTAL) {
			_points[i].setX(_x + i);
			_points[i].setY(_y);
		}

		else {
			_points[i].setX(_x);
			_points[i].setY(_y + i);
		}
	}
}

void Ship::updateSunkStatus()
{
}

Ship::Ship(const std::string& name, int length)
{
	_name = "name";
	_x = _y = _hasSunk = false;
	_direction = HORIZONTAL;
	setLength(length);
}

Ship::~Ship()
{
	_name = "";
	_x = _y = _hasSunk = false;
	_direction = HORIZONTAL;
	_length = 0;
}

int Ship::getLength() const
{
	return _length;
}

const Direction& Ship::getDirection() const
{
	return _direction;
}

bool Ship::getSunkStatus() const
{
	return _hasSunk;
}

//std::ostream& operator<<(std::ostream& output, const Ship& ship)
//{
//	// TODO: insérer une instruction return ici
//}
//
//std::istream& operator>>(std::istream& input, Ship& ship)
//{
//	// TODO: insérer une instruction return ici
//}

void Ship::setLength(int length)
{
}

void Ship::setDirection(const Direction& direction)
{
}

void Ship::rotate()
{
}

void Ship::hide()
{
}

bool Ship::checkCollision(const Ship& otherShip) const
{
	return false;
}