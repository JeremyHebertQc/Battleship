#include <iostream>
#include <string>
#include <assert.h>
#include <Windows.h>
#include <fstream>
#include <conio.h>

#include "Point.h"

// Constructeurs
Point::Point()
{
	_x = 0;
	_y = 0;
	_color = 7;
}

Point::Point(int x, int y)
{
	_x = x;
	_y = y;
	_color = 7;
}

Point::Point(const Point &p)
{
	_x = p._x;
	_y = p._y;
	_color = p._color;
}

// Destructeur 
Point::~Point()
{
	_x = _y = _color = 0;
}

// Getters
int Point::getX() const
{
	return _x;
}

int Point::getY() const
{
	return _y;
}

int Point::getColor() const
{
	return _color;
}

Point Point::getPoint() const
{
	return *this;
}

// Setters
void Point::setX(const int x)
{
	assert(x >= 0);
	
	_x = x;
}

void Point::setY(const int y)
{
	assert(y >= 0);

	_y = y;
}

void Point::setPosition(const int x, const int y)
{
	assert(x >= 0 && y >= 0);

	_x = x;
	_y = y;
}

void Point::setColor(const int color)
{
	assert(color >= 0);

	_color = color;
}

void Point::setPoint(const int x, const int y, const int color)
{
	assert(color >= 0 && x >= 0 && y >= 0);
	
	_x = x;
	_y = y;
	_color = color;
}

// Gestion de flux
void Point::draw(std::ostream& os) const
{
	goToXY(_x, _y);

	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), _color);

	char carre = 219;
	os << carre;

	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
}

void Point::print(std::ostream &os) const
{
	os << "(" << _x << "," << _y << ") " << _color;
}

void Point::read(std::istream &monFlux)
{
	char trash;
	
	monFlux >> trash >> _x >> trash >> _y >> trash >> _color;
}

// Surcharge des opérateurs
const Point& Point::operator=(const Point& autrePoint)
{
	_x = autrePoint._x;
	_y = autrePoint._y;
	_color = autrePoint._color;

	return *this;
}

bool Point::operator==(const Point& autrePoint) const
{
	return _x == autrePoint._x
		&& _y == autrePoint._y;
}

bool Point::operator!=(const Point& autrePoint) const
{
	return !(operator==(autrePoint));
}

bool Point::operator>(const Point& autrePoint) const
{
	return _x > autrePoint._x
		&& _y > autrePoint._y;
}

bool Point::operator<(const Point& autrePoint) const
{
	return _x < autrePoint._x
		&& _y < autrePoint._y;
}

bool Point::operator>=(const Point& autrePoint) const
{
	return operator>(autrePoint) || operator==(autrePoint);
}

bool Point::operator<=(const Point& autrePoint) const
{
	return operator<(autrePoint) || operator==(autrePoint);
}

std::ostream& operator<<(std::ostream& os, const Point& Point)
{
	Point.print(os);

	return os;
}

std::istream& operator>>(std::istream& is, Point& Point)
{
	Point.read(is);

	return is;
}

Point Point::operator+(Point& autrePoint)
{
	return Point(_x + autrePoint._x, _y + autrePoint._y);
}

Point Point::operator-(Point& autrePoint){
	return Point(_x - autrePoint._x, _y - autrePoint._y);
}

// Déplacement dans la grille
void goToXY(int xpos, int ypos)
{
	COORD scrn = { 0 };

	HANDLE hOuput = GetStdHandle(STD_OUTPUT_HANDLE);

	scrn.X = xpos;
	scrn.Y = ypos;
	
	SetConsoleCursorPosition(hOuput, scrn);
}

// Gestion des fichiers
void ouvrirFichier(std::ifstream& monFlux, const std::string &nomFichier)
{
	monFlux.open(nomFichier);
	if (!monFlux.is_open() || monFlux.peek() == EOF)
	{
		std::cout << "Erreur de lecture du fichier" << std::endl;
		system("pause>NUL");
		exit(1);
	}
}


int lireFichier(std::ifstream& monFlux, Point tabPoints[])
{
	int cpt = 0;
	
	while (!monFlux.eof())
	{
		tabPoints[cpt].read(monFlux);

		if(tabPoints[cpt].getColor() != 7 || tabPoints[cpt].getX() != 0 || tabPoints[cpt].getY() != 0)
		cpt++;
	}

	return cpt;
}

void fermerFichier(std::ifstream &monFlux)
{
	monFlux.close();
}