#include "ship.h"

/********************************************/
/* NE MODIFIEZ PAS LA MÉTHODE QUI SUIT !    */
/* ELLE EST DÉJÀ PLEINEMENT FONCTIONNELLE ! */
/********************************************/
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

	_hasSunk = true;
}

Ship::Ship(const std::string& name, int length)
{
	_name = name;
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

void Ship::setPosition(int x, int y)
{
	if (x < 0 || y < 0) {
		std::cout << std::endl << "posistion de bateau invalide" << std::endl;

		std::system("pause>NUL");
		std::exit(1);
	}

	_x = x;
	_y = y;

	updatePoints();
}

void Ship::setLength(int length)
{
	if (length < 0 || length > SHIP_MAX_LENGTH) {
		std::cout << std::endl << "Longueur de bateau invalide" << std::endl;

		std::system("pause>NUL");
		std::exit(1);
	}

	_length = length;
}

void Ship::setDirection(const Direction& direction)
{
	_direction = direction;

	updatePoints();
}

void Ship::rotate()
{
	if (_direction)
		_direction = (Direction)0;
	else
		_direction = (Direction)1;

	updatePoints();
}

void Ship::hide()
{
	for (Point& point : _points)
	{
		if (_direction == HORIZONTAL)
		{
			point.setColor(SHIP_HIDDEN_COLOR);
		}
		else
		{
			point.setColor(SHIP_HIDDEN_COLOR);
		}
	}
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

int Ship::placeHit(const Point& hitPosition)
{
	for (Point& point : _points)
	{
		if (hitPosition == point)
		{
			if (_hasSunk)
				return HIT_SUNK;
			else if (point.getColor() == SHIP_HIT_COLOR)
				return HIT_TWICE;
			else
			{
				point.setColor(SHIP_HIT_COLOR);

				updateSunkStatus();

				return HIT_STANDARD;
			}
		}	
	}

	return HIT_WATER;
}

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
	std::string length;

	input >> _name >> length;
	setLength(length[1]);

	//char trash;
	//int length;
	// 
	//input >> _name >> trash >> length >> trash;
	//setLength(length);
}

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
