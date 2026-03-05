#include <assert.h>

#include "ship.h"

// Méthodes privées
void Ship::updatePoints() {
	for (int i = 0; i < _length; i++)
	{
		if (_direction == HORIZONTAL)
		{
			_points[i].setX(_x + i);
			_points[i].setY(_y);
		}

		else
		{
			_points[i].setX(_x);
			_points[i].setY(_y + i);
		}
	}
}

void Ship::updateSunkStatus()
{
	for (int i = 0; i < _length; i++)
	{
		if (_points[i].getColor() == SHIP_HIT_COLOR)
			continue;
		return;
	}

	for (int i = 0; i < getLength(); i++)
	{
		_points[i].setColor(SHIP_SUNK_COLOR);	
	}

	_hasSunk = true;
}

// Constructeur
Ship::Ship(const std::string& name, int length)
{
	_name = name;
	_x = _y = _hasSunk = false;
	_direction = HORIZONTAL;
	setLength(length);
}

// Destructeur
Ship::~Ship()
{
	_name = "";
	_x = _y = _hasSunk = false;
	_direction = HORIZONTAL;
	_length = 0;
}

// Getters
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

// Setters
void Ship::setPosition(int x, int y)
{
	assert(x >= 0 && y >= 0);

	_x = x;
	_y = y;

	updatePoints();
}

void Ship::setLength(int length)
{
	assert(length >= 0 && length <= SHIP_MAX_LENGTH);

	_length = length;
}

void Ship::setDirection(const Direction& direction)
{
	_direction = direction;

	updatePoints();
}

// Gestion des navires
void Ship::rotate()
{
	if (_direction)
		_direction = HORIZONTAL;
	else
		_direction = VERTICAL;

	updatePoints();
}

void Ship::hide()
{
	for (int i = 0; i < getLength(); i++)
	{
		_points[i].setColor(SHIP_HIDDEN_COLOR);
	}
}

bool Ship::checkCollision(const Ship& otherShip) const
{
	for (int i = 0; i < getLength(); i++)
	{
		for (int j = 0; j < otherShip.getLength(); j++)
		{
			if (_points[i].getX() == otherShip._points[j].getX() && _points[i].getY() == otherShip._points[j].getY())
				return true;
		}
	}

	return false;
}


int Ship::placeHit(const Point& hitPosition)
{
	for (Point& point : _points)
	{
		if (hitPosition == point)
		{
			if (_hasSunk)
				return SHIP_SUNK;
			else if (point.getColor() == SHIP_HIT_COLOR)
				return SHIP_HIT_TWICE;
			else
			{
				point.setColor(SHIP_HIT_COLOR);

				updateSunkStatus();

				return SHIP_HIT;
			}
		}	
	}

	return MISSED_SHIP;
}

// Gestion de flux
void Ship::print(std::ostream& output) const
{
	output << _name << " (" << _length << ")";
}

void Ship::draw(std::ostream& output) const
{
	for (int i = 0; i < _length; i++)
		_points[i].draw(output);
	
}

void Ship::read(std::istream& input)
{
	char trash;
	int length;
	 
	input >> _name >> trash >> length >> trash;
	setLength(length);
}

// Surcharge des opérateurs
std::ostream& operator<<(std::ostream& output, const Ship& ship)
{
	ship.draw(output);

	return output;
}

std::istream& operator>>(std::istream& input, Ship& ship)
{
	ship.read(input);

	return input;
}