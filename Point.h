#pragma once

#include <string>

class Point {
public:
	Point();
	Point(int x, int y);
	Point(const Point &p);

	~Point();
	
	int getX()const;
	int getY() const;
	int getColor() const;
	Point getPoint() const;

	void setX(const int x);
	void setY(const int y);
	void setPosition(const int x, const int y);
	void setColor(const int color);
	void setPoint(const int x, const int y, const int color);

	void draw(std::ostream &os) const;
	void print(std::ostream &os) const;
	void read(std::istream &monFlux);
	
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
private:
	int _x
		, _y
		, _color;
};

void goToXY(int xpos, int ypos);

void ouvrirFichier(std::ifstream& monFlux, const std::string& nomFichier);

int lireFichier(std::ifstream &monFlux, Point tabPoints[]);

void afficherForme(const Point tabPoints[], int longueur, std::ostream &monFlux);

void fermerFichier(std::ifstream &monFlux);

void afficherMenu();

int paint(Point tabPoints[]);

void moveCursor(int &xpos, int &ypos, char direction);

void sauvegarderFichier(const std::string& nomFichier, const Point tabPoints[], int longueur);