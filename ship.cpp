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

Ship::Ship(const std::string& name, int length)
{
	_name = "name";
	_x = _y = _hasSunk = false;
	_direction = HORIZONTAL;
	//setLength(length);
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

void Ship::setPosition(int x, int y)
{
	//assert(_x >= 0);
	//assert(_y >= 0);

	_x = x;
	_y = y;

	updatePoints();
}

void Ship::setDirection(const Direction& direction)
{
	_direction = direction;

	updatePoints();
}

bool Ship::checkCollision(const Ship& otherShip) const
{
	for (const Point& point : _points)
	{
		for (const Point& otherPoint : otherShip._points)
		{
			if (point.getX() == otherPoint.getX() && point.getY() == otherPoint.getY())
				return true;
		}
	}

	return false;
}
