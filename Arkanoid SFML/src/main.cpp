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

void playerCollisions(Scene& scene, AnimationB& heart, int& lives)
{
	// Kolizja z dodatkowym �yciem
	if (lives < 3)
		if (scene.bonusCollision(heart.animationSprite) == true)
			if (lives < 3)
				lives++;
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
	Scene scene;
	AnimationB heart("data/Health/Hearts.png", Vector2u(8, 1), 0.12f);
	Clock animationClock;
	float deltaTime = 0.0f;

	while (window.isOpen())
	{
		// Obs�uga zdarze�
		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed) window.close();

			if (event.type == Event::KeyPressed && event.key.code == Keyboard::Escape) // Dost�p do klawiatury za pomoc� zdarze�
				window.close();
		}
		deltaTime = animationClock.restart().asSeconds();

		// Obs�uga czasu
		scene.gameTime();
		scene.movePlayer(); // Ruch gracza

		/*if (!scene.moveBall(false)) // Ruch pi�ki
		{
			scene.setStartPosition(true);
			if (lives == 1)	window.close(); // Warunek ko�cz�cy gr� (paletka nie z�apa�a pi�ki)
			lives--;
		}

		// Kolizje
		if (scene.blockCollision(scene.blockSprite) == true) scene.score += 150 + rand()%200;
		scene.paddleCollision(scene.playerSprite, false);
		playerCollisions(scene, heart, lives);

		// Animacja
		heart.startAnimation(deltaTime);

		// Rysowanie sceny
		window.clear(Color(219, 176, 239)); // Kolor wrzosowy

		scene.showTime(minutes, seconds);
		scene.showScore();
		scene.drawGame(window, lives);
		heart.drawAnimation(window);

		window.display();*/
	}
	return false;
}

int main()
{
	RenderWindow window(VideoMode(800, 600, 32), "Arkanoid");
	char gameplayType;

	window.setFramerateLimit(60);
	srand(time(0));

	Blocks blocks;
	blocks.setLevel(1, false);
	while (true)
	{
		window.clear(Color::Green);
		blocks.drawBlocks(window, false);
		window.display();
		
		/*gameplayType = GameMenu(window);

		if (gameplayType != 'q')
			if (!playOnline(window, gameplayType)) break;
		break;*/
		//if (!Level_1(window)) break;
		//if (!playOnline(window)) break;
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