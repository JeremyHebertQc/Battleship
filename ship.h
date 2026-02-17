#pragma once

#include <iostream>
#include "mesConstantes.h"
#include "point.h" // Ajoutez vos fichiers "point.h" et "point.cpp" développés dans un laboratoire précédent

/********************************/
/* NE MODIFIEZ PAS CE FICHIER ! */
/* IL EST DÉJÀ COMPLET !        */
/********************************/
enum Direction {
	HORIZONTAL,
	VERTICAL
};

class Ship {
	private:
		std::string _name;
		int _x;
		int _y;
		int _length;
		Direction _direction;
		Point _points[SHIP_MAX_LENGTH];
		bool _hasSunk;

		void updatePoints();
		void updateSunkStatus();

	public:
		Ship(const std::string& name = "", int length = 0);
		~Ship();
		int getLength() const;
		const Direction& getDirection() const;
		bool getSunkStatus() const;
		void setPosition(int x, int y);
		void setLength(int length);
		void setDirection(const Direction& direction);
		void rotate();
		void hide();
		bool checkCollision(const Ship& otherShip) const;
		int placeHit(const Point& hitPosition);
		void print(std::ostream& output) const;
		void draw(std::ostream& output) const;
		void read(std::istream& input);
};

std::ostream& operator<<(std::ostream& output, const Ship& ship);
std::istream& operator>>(std::istream& input, Ship& ship);