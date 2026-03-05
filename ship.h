#pragma once

#include <iostream>
#include "mesConstantes.h"
#include "Point.h"

/********************************/
/* NE MODIFIEZ PAS CE FICHIER ! */
/* IL EST DÉJÀ COMPLET !        */
/********************************/
enum Direction {
	HORIZONTAL,
	VERTICAL
};

enum ShipStatus {
	MISSED_SHIP,
	SHIP_SUNK,
	SHIP_HIT_TWICE,
	SHIP_HIT
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

	// Méthodes privées
	void updatePoints();
	void updateSunkStatus();

public:
	// Constructeur
	Ship(const std::string& name = "", int length = 0);

	// Destructeur
	~Ship();

	// Getters
	int getLength() const;
	const Direction& getDirection() const;
	bool getSunkStatus() const;

	// Setters
	void setPosition(int x, int y);
	void setLength(int length);
	void setDirection(const Direction& direction);

	// Gestion des navires
	void rotate();
	void hide();
	bool checkCollision(const Ship& otherShip) const;
	int placeHit(const Point& hitPosition);

	// Gestion de flux
	void print(std::ostream& output) const;
	void draw(std::ostream& output) const;
	void read(std::istream& input);
};

// Surchage des opérateurs
std::ostream& operator<<(std::ostream& output, const Ship& ship);
std::istream& operator>>(std::istream& input, Ship& ship);