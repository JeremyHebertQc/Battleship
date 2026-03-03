/*====================================
AUTEUR : Jérémy Hébert & Vincent Gagnon
PROJET : Battleship - TP1
DATE : 17 février 2026
====================================*/

/******************************************************/
/* PLACEZ VOS TESTS ICI, MAIS RETIREZ-LES DU "MAIN()" */
/* UNE FOIS QUE VOTRE JEU DE BATTLESHIP EST COMPLÉTÉ. */
/******************************************************/

//#include "game.h"
#include "grid.h"
#include "ship.h"

int main() {
	Grid grid;
	int nbShipsRemaining = grid.getNbRemainingShips();
	std::cout << nbShipsRemaining << std::endl;

	Point p1(9, 9), p2(8, 8), p3(50, 50), p4(7, 7);

	std::cout << "--------------------------------------------" << std::endl;

	for (int i = 0; i < 3; i++)
	{
		std::cout << "Attaque grid p1 # " << i + 1 << " : " << grid.placeHit(p1) << std::endl;
		std::cout << "Attaque grid p2 # " << i + 1 << " : " << grid.placeHit(p2) << std::endl;
		std::cout << "Attaque grid p3 # " << i + 1 << " : " << grid.placeHit(p3) << std::endl;
		if (i != 0)
			std::cout << "Attaque grid p4 # " << i + 1 << " : " << grid.placeHit(p4) << std::endl;
		std::cout << "--------------------------------------------" << std::endl;
	}
	system("pause");
	return 0;
}