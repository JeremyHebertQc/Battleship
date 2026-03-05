#pragma once

#include <string>

class Point {
private:
	int _x,
		_y,
		_color;

public:
	// Constructeurs
	Point();
	Point(int x, int y);
	Point(const Point &p);

	// Destructeur
	~Point();
	
	// Getters
	int getX()const;
	int getY() const;
	int getColor() const;
	Point getPoint() const;
	
	// Setters
	void setX(const int x);
	void setY(const int y);
	void setPosition(const int x, const int y);
	void setColor(const int color);
	void setPoint(const int x, const int y, const int color);

	// Gestion de flux
	void draw(std::ostream &os) const;
	void print(std::ostream &os) const;
	void read(std::istream &monFlux);
	
	// Surcharge des opérateurs
	const Point& operator=(const Point &autrePoint);
	bool operator==(const Point &autrePoint) const;
	bool operator!=(const Point &autrePoint) const;
	bool operator>(const Point & autrePoint) const;
	bool operator<(const Point& autrePoint) const;
	bool operator>=(const Point &autrePoint) const;
	bool operator<=(const Point &autrePoint) const;
	friend std::ostream& operator<<(std::ostream& os, const Point &Point);
	friend std::istream& operator>>(std::istream& os, Point &Point);
	Point operator+( Point &autrePoint);
	Point operator-( Point &autrePoint);
};


void goToXY(int xpos, int ypos);

// Gestion des fichiers
void ouvrirFichier(std::ifstream& monFlux, const std::string& nomFichier);
int lireFichier(std::ifstream &monFlux, Point tabPoints[]);
void fermerFichier(std::ifstream &monFlux);