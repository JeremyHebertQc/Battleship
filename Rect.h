#pragma once

#include "Point.h"

class Rect{
private:
	Point _coord;
	int _w;
	int _h;

public:
	// Constructeurs
	Rect();
	Rect(const int x, const int y, const int w = 0, const int h = 0);

	// Destructeur
	~Rect();

	// Getters
	const int getWidth() const;
	const int getHeight() const;
	Point& getPosition();
	const Point& getPosition() const;
	
	// Setters
	void setWidth(int w);
	void setHeight(int h);
	void setSize(int w, int h);
	void setRectangle(int x, int y, int w, int h);
	friend void setColor(int color, Rect& r1);

	// Gestion de flux
	void read(std::istream& flux);
	void print(std::ostream& flux) const;
	void draw(std::ostream& flux, int color) const;
};