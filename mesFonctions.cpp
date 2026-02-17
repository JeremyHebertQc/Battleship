#include <cassert>
#include "mesConstantes.h"
#include "mesFonctions.h"

#ifdef _WIN32
#include <windows.h>
#else
#include <termios.h>
#include <unistd.h>
#include <fcntl.h>
#include <cstdio>
#include <cstring>
#endif

using namespace std;

/***********************************************/
/* NE MODIFIEZ PAS LES FONCTIONS QUI SUIVENT ! */
/* ELLES SONT DÉJÀ PLEINEMENT FONCTIONNELLES ! */
/***********************************************/

// Pause le programme pendant ms millisecondes (cross-platform)
void sleepMs(int ms) {
#ifdef _WIN32
	Sleep(ms);
#else
	usleep(ms * 1000);
#endif
}

// Attend un clic de souris et retourne la position du clic sous forme de Point
Point getMouseClick() {
#ifdef _WIN32
	bool clicked = false;

	HANDLE hStdin = GetStdHandle(STD_INPUT_HANDLE);
	INPUT_RECORD irInBuf[128];
	DWORD cNumRead;
	MOUSE_EVENT_RECORD mer;

	DWORD fdwMode = ENABLE_EXTENDED_FLAGS | ENABLE_MOUSE_INPUT;
	SetConsoleMode(hStdin, fdwMode);

	while (!clicked) {
		ReadConsoleInput(hStdin, irInBuf, 128, &cNumRead);

		for (DWORD i = 0; i < cNumRead; ++i) {
			if (irInBuf[i].EventType == MOUSE_EVENT) {
				mer = irInBuf[i].Event.MouseEvent;
				if (mer.dwButtonState & FROM_LEFT_1ST_BUTTON_PRESSED) {
					clicked = true;
					break;
				}
			}
		}
	}

	return Point(mer.dwMousePosition.X, mer.dwMousePosition.Y);

#else
	// macOS / Linux : utilisation du protocole xterm SGR mouse
	struct termios oldTerm, newTerm;
	tcgetattr(STDIN_FILENO, &oldTerm);
	newTerm = oldTerm;
	newTerm.c_lflag &= ~(ICANON | ECHO);
	tcsetattr(STDIN_FILENO, TCSANOW, &newTerm);

	// Activer le rapport des clics souris (mode 1000 = clics, 1006 = format SGR)
	fprintf(stderr, "\033[?1000h\033[?1006h");
	fflush(stderr);

	int x = 0, y = 0;
	char buf[32];
	size_t bufLen = 0;
	bool done = false;

	while (!done) {
		char c;
		if (read(STDIN_FILENO, &c, 1) > 0) {
			if (bufLen < sizeof(buf) - 1) {
				buf[bufLen++] = c;
				buf[bufLen] = '\0';
			}

			// Format SGR : ESC [ < b ; x ; y M (press) ou m (release)
			// Accepter uniquement 'M' (press), pas 'm' (release), pour éviter
			// qu'un même clic physique soit compté pour les deux joueurs
			if (c == 'M' || c == 'm') {
				int b = 0, px = 0, py = 0;
				if (sscanf(buf, "\033[<%d;%d;%d", &b, &px, &py) >= 3) {
					if (c == 'M' && b < 32) {
						x = px - 1;
						y = py - 1;
						done = true;
					}
				}
				bufLen = 0;
			}
			// Réinitialiser si la séquence est trop longue
			else if (bufLen >= 20) {
				bufLen = 0;
			}
		}
	}

	// Désactiver le rapport souris
	fprintf(stderr, "\033[?1006l\033[?1000l");
	fflush(stderr);

	tcsetattr(STDIN_FILENO, TCSANOW, &oldTerm);

	return Point(x, y);
#endif
}

// Vide la file d'attente des clics de souris. À utiliser après un Sleep pour
// ignorer les clics survenus pendant celui-ci.
void ignoreMouseClicks() {
#ifdef _WIN32
	HANDLE hStdin = GetStdHandle(STD_INPUT_HANDLE);
	DWORD fdwMode = ENABLE_EXTENDED_FLAGS | ENABLE_MOUSE_INPUT;
	SetConsoleMode(hStdin, fdwMode);

	INPUT_RECORD irInBuf[128];
	DWORD cNumRead;

	// Clear any existing input events
	while (true) {
		PeekConsoleInput(hStdin, irInBuf, 128, &cNumRead);

		if (!cNumRead) {
			break;
		}
		ReadConsoleInput(hStdin, irInBuf, 128, &cNumRead);
	}
#else
	// macOS / Linux : vider stdin (les séquences souris sont dans stdin)
	int flags = fcntl(STDIN_FILENO, F_GETFL, 0);
	fcntl(STDIN_FILENO, F_SETFL, flags | O_NONBLOCK);

	char buf[64];
	while (read(STDIN_FILENO, buf, sizeof(buf)) > 0) {
		;
	}

	fcntl(STDIN_FILENO, F_SETFL, flags);
#endif
}

// Efface l'écran. À utiliser à la place de system("cls") ou system("clear") pour
// éviter des problèmes avec la fonction getMouseClick.
void clearScreen(std::ostream& output) {
	output << "\033[2J\033[1;1H";
}