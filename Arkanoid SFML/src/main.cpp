#include "Engine.h"
#include <stdlib.h>
#include <time.h>
#include <iostream> // Tymaczasowo

using namespace std;

char GameMenu(RenderWindow& window)
{
	Menu menu;
	char connectionType = menu.Run(window);

	return connectionType;
}

/************************************************
 *  ... G��wna funkcja gry online
 ***********************************************/

bool playOnline(RenderWindow& window, char gameplayType)
{
	Server server(gameplayType);
	server.Run(window);

	return false;
}

/************************************************
 *  ... G��wna funkcja pierwszego poziomu // Faza remontu
 ***********************************************/

bool Level_1(RenderWindow &window)
{
	Scene scene(1);
	scene.Run(window);
	
	return false;
}

int main()
{
	RenderWindow window(VideoMode(800, 600, 32), "Arkanoid");
	char gameplayType;

	window.setFramerateLimit(60);
	srand(time(0));
	while (true)
	{
		// Offline
		if (!Level_1(window)) break;

		// Online
		/*gameplayType = GameMenu(window);

		if (gameplayType != 'q')
			if (!playOnline(window, gameplayType)) break;
		break;*/
	}
	
	return 0;
}

		/****************/
		/*...Notatnik...*/
		/****************/


		// Niezrealizowane <<

		// P�tla ma si� znajdowa� w klasie Application oraz zamiast "if�w" w p�tli, ma znajdowa� si� switch. 
		// Funkcje typu GameMenu(), playOnline(), itp. b�d� zwraca� si� inta w celu powrotu do menu. 
		// Gra si� ko�czy wtedy, gdy:
		
		/*  -> wci�niemy escape w trybie menu z napisami Start , credits oraz Quitgame.
			-> wci�niemy enter na przycisku Quitgame.
		*/