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
 *  ... G³ówna funkcja gry online
 ***********************************************/

bool playOnline(RenderWindow& window, char gameplayType)
{
	Server server(gameplayType);
	server.Run(window);

	return false;
}

/************************************************
 *  ... G³ówna funkcja pierwszego poziomu // Faza remontu
 ***********************************************/

bool Level_1(RenderWindow &window)
{
	Scene scene(1);
	scene.Run(window);
	
	return false;
}

bool Level_2(RenderWindow& window)
{
	Scene scene(2);
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

		// Online
		gameplayType = GameMenu(window);

		switch(gameplayType)
		{
		case '1':
			if (!Level_1(window)) break;
		case '2':
			if (!Level_2(window)) break;

		case 'q':
			break;

		default:
			if (!playOnline(window, gameplayType)) break;
		}
		break;
	}
	
	return 0;
}

		/****************/
		/*...Notatnik...*/
		/****************/


		// Niezrealizowane <<

		// Pêtla ma siê znajdowaæ w klasie Application oraz zamiast "ifów" w pêtli, ma znajdowaæ siê switch. 
		// Funkcje typu GameMenu(), playOnline(), itp. bêd¹ zwracaæ siê inta w celu powrotu do menu. 
		// Gra siê koñczy wtedy, gdy:
		
		/*  -> wciœniemy escape w trybie menu z napisami Start , credits oraz Quitgame.
			-> wciœniemy enter na przycisku Quitgame.
		*/