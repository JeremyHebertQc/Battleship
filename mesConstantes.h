#pragma once

#include <string>

/********************************/
/* NE MODIFIEZ PAS CE FICHIER ! */
/* IL EST DÉJÀ COMPLET !        */
/********************************/

// Constantes pour les bateaux (objet "Ship")
constexpr int SHIP_MAX_NB =	5;
constexpr int SHIP_MAX_LENGTH = 15;
constexpr int SHIP_HIDDEN_COLOR = 0;
constexpr int SHIP_HIT_COLOR = 13;
constexpr int SHIP_SUNK_COLOR = 12;

// Constantes pour la grille de jeu (objet "Grid")
constexpr int GRID_INNER_MIN_X = 1;
constexpr int GRID_INNER_MIN_Y = 5;
constexpr int GRID_INNER_MAX_X = 10;
constexpr int GRID_INNER_MAX_Y = 14;
constexpr int GRID_WIDTH = (GRID_INNER_MAX_X - GRID_INNER_MIN_X + 3);
constexpr int GRID_HEIGHT = (GRID_INNER_MAX_Y - GRID_INNER_MIN_Y + 3);
const std::string GRID_SHIPS_FILENAME = "ships.txt";
constexpr int GRID_SHIPS_STATUS_X = (GRID_INNER_MAX_X + 5);
constexpr int GRID_SHIPS_STATUS_Y = (GRID_INNER_MIN_Y - 1);
constexpr int GRID_MISSED_HITS_COLOR = 11;

// Constantes pour le déroulement de la partie (objet "Game")
constexpr int GAME_NB_PLAYERS = 2;