#include "Engine.h"
#include <iostream>
#include <string>
#include <sstream>

void Scene::setInterface()
{
	rectangle = new RectangleShape(Vector2f(250, 600));
	heartSprite = new Sprite[3];
	rectangle->setPosition(550, 0);
	rectangle->setFillColor(Color(122, 125, 128));
	score = 0;

	seconds = minutes = 0;
	lives = 3;

	// Teksty
	font.loadFromFile("data/font1.ttf");
	liveText.setFont(font);
	liveText.setCharacterSize(24);
	liveText.setFillColor(Color::White);
	liveText.setPosition(560, 120);
	liveText.setString("Remaining lifes:");

	timeText.setFont(font);
	timeText.setCharacterSize(24);
	timeText.setFillColor(Color::White);
	timeText.setPosition(560, 20);

	scoreText.setFont(font);
	scoreText.setCharacterSize(24);
	scoreText.setFillColor(Color::White);
	scoreText.setPosition(560, 72);

	// Sprite'y
	heartTexture.loadFromFile("data/heart.png");
	for (int i = 0; i < 3; i++)
	{
		heartSprite[i].setTexture(heartTexture);
		heartSprite[i].setPosition(560 + (float)i * 45, 150);
		heartSprite[i].setScale(Vector2f(0.7f, 0.7f));
	}
}

Scene::Scene()
{
	// Zak³adka na interfejs
	rectangle = new RectangleShape(Vector2f(250, 600));
	heartSprite = new Sprite[3];
	rectangle->setPosition(550, 0);
	rectangle->setFillColor(Color(122, 125, 128));		
	score = 0;

	seconds = minutes = 0;
	lives = 3;

	// Teksty
	font.loadFromFile("data/font1.ttf");
	liveText.setFont(font);
	liveText.setCharacterSize(24);
	liveText.setFillColor(Color::White);
	liveText.setPosition(560, 120);
	liveText.setString("Remaining lifes:");

	timeText.setFont(font);
	timeText.setCharacterSize(24);
	timeText.setFillColor(Color::White);
	timeText.setPosition(560, 20);

	scoreText.setFont(font);
	scoreText.setCharacterSize(24);
	scoreText.setFillColor(Color::White);
	scoreText.setPosition(560, 72);

	// Sprite'y
	heartTexture.loadFromFile("data/heart.png");
	for (int i = 0; i < 3; i++)
	{
		heartSprite[i].setTexture(heartTexture);
		heartSprite[i].setPosition(560 + (float)i * 45, 150);
		heartSprite[i].setScale(Vector2f(0.7f, 0.7f));
	}
}

Scene::Scene(unsigned int level) // Dla trybu pojedynczego gracza
{
	setInterface();

	switch (level)
	{
	case 1:
		landscapeTexture.loadFromFile("data/shore.png");
		landscapeSprite.setTexture(landscapeTexture);
		landscapeSprite.setPosition(-450, 0);
		break;

	default:
		break;
	}
}

Scene::~Scene() 
{ 
	delete rectangle;
	delete[] heartSprite;
}

void Scene::gameTime()
{
	seconds = (int)clock.getElapsedTime().asSeconds();
	if (seconds == 60)
	{
		clock.restart();
		minutes++;
	}
}

void Scene::playerCollisions(AnimationB& heart)
{
	// Kolizja z dodatkowym ¿yciem
	if (lives < 3)
		if (bonusCollision(heart.animationSprite) == true)
			if (lives < 3)
				lives++;
}

void Scene::showTime()
{
	std::string str = "Time: ";
	std::stringstream stream1, stream2;
	stream1 << minutes;
	stream2 << seconds;
	std::string auxMinutes, auxSeconds;
	stream1 >> auxMinutes;
	stream2 >> auxSeconds;
	if (seconds < 10) str += auxMinutes + ":0" + auxSeconds;
	else str += auxMinutes + ":" + auxSeconds;
	timeText.setString(str);
}

void Scene::showScore()
{
	std::string str = "Score: ";
	std::stringstream stream;
	stream << score;
	std::string auxScore;
	stream >> auxScore;
	str += auxScore;
	scoreText.setString(str);
}


void Scene::drawHearts(RenderWindow& window)
{
	for(int i = 0; i < lives; i++)
		window.draw(heartSprite[i]);
}

void Scene::drawInterface(RenderWindow& window)
{
	window.draw(*rectangle);
	window.draw(liveText);
	//window.draw(timeText);
	window.draw(scoreText);
	drawHearts(window);
	//Ball::draw(window);
	//Player::draw(window);
	//drawBlocks(window);
}

void Scene::drawGame(RenderWindow& window)
{
	window.draw(*rectangle);
	window.draw(liveText);
	window.draw(timeText);
	window.draw(scoreText);
	window.draw(landscapeSprite);
	drawHearts(window);
	Ball::draw(window);
	Player::draw(window);
	drawBlocks(window, false);
}

void Scene::Run(RenderWindow& window)
{
	AnimationB heart("data/Health/Hearts.png", Vector2u(8, 1), 0.12f);
	Clock animationClock;
	float deltaTime = 0.0f;

	setLevel(1, true);
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
		gameTime();
		movePlayer(); // Ruch gracza

		if (!moveBall(false)) // Ruch pi³ki
		{
			setStartPosition(true);
			if (lives == 1)	window.close(); // Warunek koñcz¹cy grê (paletka nie z³apa³a pi³ki)
			lives--;
		}

		// Kolizje
		if (blockCollision(blockSprite) == true) score += 150 + rand() % 200;
		paddleCollision(playerSprite, false);
		playerCollisions(heart);

		// Animacja
		heart.startAnimation(deltaTime);

		// Rysowanie sceny
		window.clear(Color(219, 176, 239)); // Kolor wrzosowy

		showTime();
		showScore();
		drawGame(window);
		heart.drawAnimation(window);

		window.display();
	}
}