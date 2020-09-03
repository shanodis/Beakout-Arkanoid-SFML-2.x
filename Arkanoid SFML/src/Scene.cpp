#include "Engine.h"
#include <iostream>
#include <string>
#include <sstream>

Scene::Scene()
{
	// Zak³adka na interfejs
	rectangle = new RectangleShape(Vector2f(250, 600));
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

	/*switch (level)
	{
	case 1:
		landscapeTexture.loadFromFile("data/fortress.png");
		landscapeSprite.setTexture(landscapeTexture);
		landscapeSprite.setPosition(-450, 0);
		break;

	default:
		break;
	}*/
}

Scene::~Scene() { delete rectangle; }

void Scene::gameTime()
{
	seconds = clock.getElapsedTime().asSeconds();
	if (seconds == 60)
	{
		clock.restart();
		minutes++;
	}
}

void Scene::showTime(int minutes, int seconds)
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


void Scene::drawHearts(RenderWindow& window, int n)
{
	for(int i = 0; i < n; i++)
		window.draw(heartSprite[i]);
}

void Scene::drawInterface(RenderWindow& window)
{
	window.draw(*rectangle);
	window.draw(liveText);
	//window.draw(timeText);
	window.draw(scoreText);
	drawHearts(window, lives);
	//Ball::draw(window);
	//Player::draw(window);
	//drawBlocks(window);
}

void Scene::drawGame(RenderWindow& window, int lives)
{
	window.draw(*rectangle);
	window.draw(liveText);
	window.draw(timeText);
	window.draw(scoreText);
	window.draw(landscapeSprite);
	drawHearts(window, lives);
	Ball::draw(window);
	Player::draw(window);
	drawBlocks(window);
}