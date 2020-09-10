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
	// Kolizja z dodatkowym ¿yciem
	if (lives < 3)
		if (scene.bonusCollision(heart.animationSprite) == true)
			if (lives < 3)
				lives++;
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
	Scene scene;
	AnimationB heart("data/Health/Hearts.png", Vector2u(8, 1), 0.12f);
	Clock animationClock;
	float deltaTime = 0.0f;

	while (window.isOpen())
	{
		// Obs³uga zdarzeñ
		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed) window.close();

			if (event.type == Event::KeyPressed && event.key.code == Keyboard::Escape) // Dostêp do klawiatury za pomoc¹ zdarzeñ
				window.close();
		}
		deltaTime = animationClock.restart().asSeconds();

		// Obs³uga czasu
		scene.gameTime();
		scene.movePlayer(); // Ruch gracza

		/*if (!scene.moveBall(false)) // Ruch pi³ki
		{
			scene.setStartPosition(true);
			if (lives == 1)	window.close(); // Warunek koñcz¹cy grê (paletka nie z³apa³a pi³ki)
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
	while (true)
	{
		
		gameplayType = GameMenu(window);

		if (gameplayType != 'q')
			if (!playOnline(window, gameplayType)) break;
		break;
		//if (!Level_1(window)) break;
		//if (!playOnline(window)) break;
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