#include <iostream>

#include "Rect.h"
#include "Point.h"

using namespace std;

Rect::Rect(){
	_coord = Point();
	_w = 0;
	_h = 0;
}

Rect::Rect(const int x, const int y, const int w, const int h){
	setRectangle(x, y, w, h);
}

Rect::~Rect(){
	_w = _h = 0;
}

const int Rect::getWidth() const{
	return _w;
}

const int Rect::getHeight() const{
	return _h;
}

Point& Rect::getPosition(){
	return _coord;
}

const Point& Rect::getPosition() const{
	return _coord.getPoint();
}

void Rect::setWidth(int w){
	if (w < 0) {
		cout << endl << "Erreur: largeur invalide" << endl;
		system("pause>NUL");
		exit(1);
	}
	
	_w = w;
}

void Rect::setHeight(int h){
	if (h < 0) {
		cout << endl << "Erreur: hauteur invalide" << endl;
		system("pause>NUL");
		exit(2);
	}

	_h = h;
}

void Rect::setSize(int w, int h){
	if (w < 0) {
		cout << endl << "Erreur: largeur invalide" << endl;
		system("pause>NUL");
		exit(1);
	}

	if (h < 0) {
		cout << endl << "Erreur: hauteur invalide" << endl;
		system("pause>NUL");
		exit(2);
	}

	setWidth(w);
	setHeight(h);
}

void Rect::setRectangle(int x, int y, int w, int h){
	if (w < 0) {
		cout << endl << "Erreur: largeur invalide" << endl;
		system("pause>NUL");
		exit(1);
	}

	if (h < 0) {
		cout << endl << "Erreur: hauteur invalide" << endl;
		system("pause>NUL");
		exit(2);
	}

	_coord.setPosition(x, y);
	setSize(w, h);
}

void Rect::read(istream &flux){
	char trash;

	_coord.read(flux);
	flux >> _w >> trash >> _h;
}

void Rect::print(std::ostream &flux) const{
	_coord.print(flux);
	flux << " " << _w << " X " << _h << endl;
}

void Rect::draw(std::ostream &flux, int color) const{
	Point temp;	

	for (int i = 0; i < _h; i++){
		for (int j = 0; j < _w; j++){
			if (i == 0 || i == _h - 1 || j == 0 || j == _w - 1) {
				temp.setPoint(_coord.getX() + j, _coord.getY() + i, color);

				temp.draw(cout);
			}

		}

		cout << endl;
	}
}

int Rect::surface() const{
	return (2 * _w + 2 * _h);
}

int Rect::perimetre() const{
	return (_w * _h);
}

void setColor(int color, Rect& r1){
	r1._coord.setColor(color);
}
