#include <iostream>
#include <string>
#include <assert.h>
#include <Windows.h>
#include <fstream>
#include <conio.h>

#include "Point.h"

using namespace std;

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

Point::~Point()
{
	_x = _y = _color = 0;
}

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
	assert(color >= 0 && color <= 25);

	_color = color;
}

void Point::setPoint(const int x, const int y, const int color)
{
	assert(color >= 0 && color <= 25);
	assert(x >= 0 && y >= 0);
	

	_x = x;
	_y = y;
	_color = color;
}

void Point::draw(ostream& os) const
{
	goToXY(_x, _y);

	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), _color);

	os << "\xFE";

	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
}

void Point::print(ostream &os) const
{
	os << "(" << _x << "," << _y << ") " << _color;
}

void Point::read(std::istream &monFlux)
{
	char trash;
	
	monFlux >> trash >> _x >> trash >> _y >> trash >> _color;
}

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

ostream& operator<<(ostream& os, const Point& Point)
{
	Point.print(os);

	return os;
}

istream& operator>>(istream& is, Point& Point)
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

void goToXY(int xpos, int ypos)
{
	COORD scrn = { 0 };

	HANDLE hOuput = GetStdHandle(STD_OUTPUT_HANDLE);

	scrn.X = xpos;
	scrn.Y = ypos;
	
	SetConsoleCursorPosition(hOuput, scrn);
}

void ouvrirFichier(ifstream& monFlux, const string &nomFichier)
{
	monFlux.open(nomFichier);
	if (!monFlux.is_open() || monFlux.peek() == EOF)
	{
		cout << "Erreur de lecture du fichier" << endl;
		system("pause>NUL");
		exit(1);
	}
}


int lireFichier(ifstream& monFlux, Point tabPoints[])
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

void afficherForme(const Point tabPoints[], int longueur, std::ostream &monFlux)
{
	for (int i = 0; i < longueur; i++)
	{
		tabPoints[i].draw(monFlux);
	}

}

void fermerFichier(std::ifstream &monFlux)
{
	monFlux.close();
}

void afficherMenu()
{
	system("cls");

	cout << "Menu de l'application" << endl
		<< "--------------------------------------------" << endl
		<< "0 - Quitter" << endl
		<< "1 - Afficher une forme" << endl
		<< "2 - Faire mon dessin" << endl << endl;
}

int paint(Point tabPoints[])
{
	int longueur = 0;
	int x = 0;
	int y = 0;
	system("cls");

	do
	{
		char key = _getch();
		
		if (key == 32)
			longueur++;
		else if (key == 'q')
			return longueur;
		else if (key == 'e')
			if (tabPoints[longueur].getColor() == 25)
				tabPoints[longueur].setColor(0);
			else
				tabPoints[longueur].setColor(tabPoints[longueur].getColor() + 1);
		else
		{
			moveCursor(x, y, key);
			tabPoints[longueur].setX(x);
			tabPoints[longueur].setY(y);
			tabPoints[longueur].setColor(tabPoints[longueur].getColor());
			system("cls");
			afficherForme(tabPoints, longueur + 1, cout);
		}
	} while (true);

	return longueur;
}

void moveCursor(int &xpos, int &ypos, char direction)
{
	switch (direction)
	{
	case-32:
		break;
	case 'w':
	case 72:
		if (ypos > 0)
			ypos--;
		break;
	case 's':
	case 80:
		if (ypos < 20)
			ypos++;
		break;
	case 'a':
	case 75:
		if (xpos > 0)
			xpos--;
		break;
	case 'd':
	case 77:
		if (xpos < 50)
			xpos++;
		break;
	default:
		cout << "Deplacement impossible!";
		break;
	}
}

void sauvegarderFichier(const string &nomFichier, const Point tabPoints[], int longueur)
{
	ofstream fichierSortie(nomFichier);

	if (fichierSortie.is_open())
	{
		for (int i = 0; i < longueur; i++)
		{
			tabPoints[i].print(fichierSortie);
		}

		fichierSortie.close();

		cout << "Données sauvegardées dans " << nomFichier << endl;
	}
	else
	{
		cout << "Impossible d'ouvrir le fichier " << nomFichier << " pour sauvegarde." << endl;
	}
}