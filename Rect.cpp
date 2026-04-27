#include <iostream>
#include <assert.h>

#include "rect.h"
#include "point.h"

// Constructeurs
Rect::Rect()
{
	_coord = Point();
	_w = 0;
	_h = 0;
}

Rect::Rect(const int x, const int y, const int w, const int h)
{
	setRectangle(x, y, w, h);
}

// Destructeur
Rect::~Rect()
{
	_w = 0;
	_h = 0;
}

// Getters
const int Rect::getWidth() const
{
	return _w;
}

const int Rect::getHeight() const
{
	return _h;
}

Point& Rect::getPosition()
{
	return _coord;
}

const Point& Rect::getPosition() const
{
	return _coord.getPoint();
}

// Setters
void Rect::setWidth(int w)
{
	assert(w >= 0);
	
	_w = w;
}

void Rect::setHeight(int h)
{
	assert(h >= 0);

	_h = h;
}

void Rect::setSize(int w, int h)
{
	assert(w >= 0 && h >= 0);

	setWidth(w);
	setHeight(h);
}

void Rect::setRectangle(int x, int y, int w, int h)
{
	assert(w >= 0 && h >= 0 && x >= 0 && y >= 0);

	_coord.setPosition(x, y);
	setSize(w, h);
}

void setColor(int color, Rect& r1)
{
	assert(color >= 0);

	r1._coord.setColor(color);
}

// Gestion de flux
void Rect::read(std::istream& flux)
{
	char trash;

	_coord.read(flux);
	flux >> _w >> trash >> _h;
}

void Rect::print(std::ostream& flux) const
{
	_coord.print(flux);
	flux << " " << _w << " X " << _h << std::endl;
}

void Rect::draw(std::ostream& flux, int color) const
{
	Point temp;	

	for (int i = 0; i < _h; i++)
	{
		for (int j = 0; j < _w; j++)
		{
			if (i == 0 || i == _h - 1 || j == 0 || j == _w - 1)
			{
				temp.setPoint(_coord.getX() + j, _coord.getY() + i, color);

				temp.draw(flux);
			}
		}
		flux << std::endl;
	}
}
