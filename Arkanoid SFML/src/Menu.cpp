#include "Engine.h"
#include <fstream>
#include <sstream>
#include <vector>

/************************************************
 *  ... Konstruktor inicjalizuj¹cy
 ***********************************************/

Menu::Menu()
{
	direction = 0; pageNumber = state = 1;
	levelSprite = NULL; levelTexture = NULL; levelTxt = NULL;
	connectionType = 'n';
	font.loadFromFile("data/font1.ttf");

/************************************************
*  ... Ustawienia tekstów
***********************************************/

	// Ustawienia tekstu playTxt
	playTxt.setFont(font);
	playTxt.setCharacterSize(34);
	playTxt.setFillColor(Color::Red);
	playTxt.setString("Play");
	playTxt.setPosition(20.0f, 200.0f);

	// Ustawienia tekstu creditsTxt
	creditsTxt.setFont(font);
	creditsTxt.setCharacterSize(34);
	creditsTxt.setFillColor(Color::White);
	creditsTxt.setString("Credits");
	creditsTxt.setPosition(20.0f, 250.0f);

	// Ustawienia tekstu quitTxt
	quitTxt.setFont(font);
	quitTxt.setCharacterSize(34);
	quitTxt.setFillColor(Color::White);
	quitTxt.setString("Exit");
	quitTxt.setPosition(20.0f, 300.0f);

	// Ustawienia tekstu credits
	credits.setFont(font);
	credits.setCharacterSize(34);
	credits.setFillColor(Color::White);
	credits.setString("Created by Dominik Grudzieñ\nSources:\nhttps://opengameart.org");
	credits.setPosition(200.0f, 300.0f);

	// Ustawienia tekstu backTxt
	backTxt.setFont(font);
	backTxt.setCharacterSize(34);
	backTxt.setFillColor(Color::Red);
	backTxt.setString("Back");
	backTxt.setPosition(90.0f, 500.0f);

/************************************************
*  ... Ustawienia sprite'ów
***********************************************/

	// £adowanie tekstur, ustawienia
	landscapeTexture.loadFromFile("data/fortress.png");
	landscapeTexture.setSmooth(true);
	headerTexture.loadFromFile("data/Header.png");
	headerTexture.setSmooth(true);
	arrowTexture.loadFromFile("data/arrow.png");

	// Przypisywanie tektur do sprite'ów
	landscapeSprite.setTexture(landscapeTexture);
	headerSprite.setTexture(headerTexture);
	arrowSprite.setTexture(arrowTexture);

	// Ustawienia strza³ki
	arrowSprite.setPosition(130.0f, 210.0f);
	arrowSprite.setScale(Vector2f(0.05f, 0.05f));

	// Ustawienia nag³ówka
	headerSprite.setScale(Vector2f(2.0f, 2.0f));
	headerSprite.setColor(Color(255, 255, 255, 128));
	headerSprite.setPosition(0.0f, -150.0f);

	// Ustawienia muzyki
	switchSoundBuffer.loadFromFile("data/Sounds/misc_menu_4.wav");
	switchSound.setBuffer(switchSoundBuffer);
	switchSound.setVolume(10.0f);
}

/************************************************
 *  ... Funkcje operuj¹ce
 ***********************************************/

void Menu::moveLandscape()
{
	if ((landscapeSprite.getPosition().x <= 0) && (direction == 0))
	{
		if (landscapeSprite.getPosition().x <= -119) direction = 1;
		landscapeSprite.move(Vector2f(-0.3f, 0.0f));
	}

	if ((landscapeSprite.getPosition().x >= -120) && (direction == 1))
	{
		if (landscapeSprite.getPosition().x >= -1) direction = 0;
		landscapeSprite.move(Vector2f(0.3f, 0.0f));
	}
}

void Menu::createPage6()
{
	// Obrazy
	levelTexture = new Texture * [3];
	levelSprite = new Sprite * [3];
	for (int i = 0; i < 3; i++)
	{
		levelTexture[i] = new Texture[3];
		levelSprite[i] = new Sprite[3];
	}

	levelTexture[0][0].loadFromFile("data/Level Images/Level1.png");
	levelTexture[0][1].loadFromFile("data/Level Images/Chosen Level1.png");
	levelTexture[1][0].loadFromFile("data/Level Images/Level2.png");
	levelTexture[1][1].loadFromFile("data/Level Images/Chosen Level2.png");
	levelTexture[2][0].loadFromFile("data/Level Images/Level3.png");
	levelTexture[2][1].loadFromFile("data/Level Images/Chosen Level3.png");

	int multiplier = 0;
	for (int i = 0; i < 3; i++)
	{
		levelSprite[i][0].setTexture(levelTexture[i][0]);
		levelSprite[i][1].setTexture(levelTexture[i][1]);

		levelSprite[i][0].setScale(Vector2f(0.35f, 0.35f));
		levelSprite[i][1].setScale(Vector2f(0.35f, 0.35f));

		levelSprite[i][0].setPosition(50 + multiplier, 200);
		levelSprite[i][1].setPosition(50 + multiplier, 200);
		multiplier += 200;
	}

	// Teksty
	levelTxt = new Text[3];
	for (int i = 0; i < 3; i++)
	{
		levelTxt[i].setFont(font);
		levelTxt[i].setCharacterSize(34);
		levelTxt[i].setFillColor(Color::White);
	}
	levelTxt[0].setFillColor(Color::Red);
	levelTxt[0].setString("Level 1");
	levelTxt[0].setPosition(90, 430);
	levelTxt[1].setString("Level 2");
	levelTxt[1].setPosition(290, 430);
	levelTxt[2].setString("Level 3");
	levelTxt[2].setPosition(490, 430);
}

void Menu::deletePage6()
{
	if (levelTexture != NULL)
	{
		for (int i = 0; i < 3; i++)
			delete[] levelTexture[i];
		delete[] levelTexture;
		for (int i = 0; i < 3; i++)
			delete[] levelSprite[i];
		delete[] levelSprite;
		levelSprite = NULL; levelTexture = NULL;
		delete[] levelTxt;
		levelTxt = NULL;
	}
}



void Menu::page6() // Funkcja g³ówna strony z poziomami OFFLINE
{
	if (levelTexture == NULL)
	{
		createPage6();
	}
}

void Menu::changeArrowPositionPages()
{
	if (pageNumber == 1) arrowSprite.setPosition(200, 210);
	if (pageNumber == 3)
	{
		if(state == 1)
			arrowSprite.setPosition(130, 210);
		else if (state == 2)
			arrowSprite.setPosition(130, 260);
		else if (state == 3)
			arrowSprite.setPosition(130, 310);
	}
	if (pageNumber == 4)
	{
		///if (state == 1)
			//arrowSprite.setPosition(200, 210);
		if (state == 2)
			arrowSprite.setPosition(200, 260);
		else if (state == 3)
			arrowSprite.setPosition(200, 310);
	}
	if (pageNumber == 5)
	{
		arrowSprite.setPosition(160, 410);
	}
}

void Menu::changeArrowPositionCredits() // Zmiana pozycji strza³ki na stronie credits
{
	if (pageNumber == 1) arrowSprite.setPosition(130, 260);
	if (pageNumber == 2) arrowSprite.setPosition(200, 500);
}

int Menu::readState() // Odczytywanie stanu przycisków
{
	if (Keyboard::isKeyPressed(Keyboard::Enter) && (state == 1))
		return 1;

	if (Keyboard::isKeyPressed(Keyboard::Enter) && (state == 2))
		return 2;

	if (Keyboard::isKeyPressed(Keyboard::Enter) && (state == 3))
		return 3;
	return 0;
}

bool Menu::EscapeButton(RenderWindow& window) // Przycisk Escape
{
	if (pageNumber == 1)
	{
		window.close();
		return false;
	}
	else if (pageNumber == 2)
	{
		pageNumber = 1;
		changeArrowPositionCredits();
	}
	else if (pageNumber == 3)
	{
		changeArrowPositionPages();
		pageNumber = 1;
		playTxt.setString("Play");
		creditsTxt.setString("Credits");
		quitTxt.setString("Exit");
	}
	else if (pageNumber == 4)
	{
		pageNumber = 3;
		playTxt.setString("Singleplayer");
		creditsTxt.setString("Multiplayer");
		quitTxt.setString("Back");
	}
	else if (pageNumber == 5)
	{
		pageNumber = 4;
		changeArrowPositionPages();
		playTxt.setString("Join game");
		creditsTxt.setString("Host game");
		quitTxt.setString("Back");
		creditsTxt.setPosition(20, 250);
		quitTxt.setPosition(20, 300);
	}
	else if (pageNumber == 6)
	{
		deletePage6();
		pageNumber = 3;
		state = 1;
	}
	return true;
}

int Menu::EnterButton() // Przycisk Enter
{
	if (pageNumber == 2)
	{
		pageNumber = 1;
		changeArrowPositionCredits();
	}
	else if (pageNumber != 5)
	{
		switch (readState())
		{
		case 1:
			if (pageNumber == 1)
			{
				changeArrowPositionPages();
				pageNumber = 3;
				playTxt.setString("Singleplayer");
				creditsTxt.setString("Multiplayer");
				quitTxt.setString("Back");
			}
			else if (pageNumber == 3)
			{
				pageNumber = 6;
				state = 1;
				page6();
			}
			else if (pageNumber == 4)
			{
				state = 2;
				pageNumber = 5;
				changeArrowPositionPages();
				creditsTxt.setPosition(20, 200);
				playTxt.setString("Connecting as a client");
				playTxt.setFillColor(Color::White);
				creditsTxt.setFillColor(Color::Red);
				creditsTxt.setString("Connect");
				creditsTxt.setPosition(20, 400);
				quitTxt.setPosition(20, 450);
				connectionType = 'c';
			}
			else if (pageNumber == 6)
			{
				connectionType = '1';
				return 1;
			}
			break;

		case 2:
			if (pageNumber == 1)
			{
				pageNumber = 2;
				changeArrowPositionCredits();
			}
			else if (pageNumber == 4)
			{
				pageNumber = 5;
				changeArrowPositionPages();
				playTxt.setString("Connecting as a host");
				creditsTxt.setString("Connect");
				creditsTxt.setPosition(20, 400);
				quitTxt.setPosition(20, 450);
				connectionType = 's'; // Like server
			}
			else if (pageNumber == 3)
			{
				pageNumber = 4;
				playTxt.setString("Join game");
				creditsTxt.setString("Host game"); 
				quitTxt.setString("Back");
			}
			else if (pageNumber == 6)
			{
				connectionType = '2';
				return 1;
			}
			break;

		case 3:
			if (pageNumber == 1) return -1;
			else if (pageNumber == 3)
			{
				changeArrowPositionPages();
				pageNumber = 1;
				playTxt.setString("Play");
				creditsTxt.setString("Credits");
				quitTxt.setString("Exit");
			}
			else if (pageNumber == 4)
			{
				pageNumber = 3;
				playTxt.setString("Singleplayer");
				creditsTxt.setString("Multiplayer");
				quitTxt.setString("Back");
			}
			else if (pageNumber == 6)
			{
				connectionType = '3';
				return 1;
			}
			break;
		}
	}
	else
	{
		int buttonState = readState();
		if (buttonState == 2)
		{
			if (connectionType == 's')
			{
				std::cout << "Waiting for client connection...";
				return 100;
			}
			else if (connectionType == 'c')
				return 200;
		}
		else if (buttonState == 3)
		{
			pageNumber = 4;
			changeArrowPositionPages();
			playTxt.setString("Join game");
			creditsTxt.setString("Host game");
			quitTxt.setString("Back");
			creditsTxt.setPosition(20, 250);
			quitTxt.setPosition(20, 300);
		}
	}
	return 0;
}

void Menu::moveInPage6()
{
	if (pageNumber == 6)
	{
		if (Keyboard::isKeyPressed(Keyboard::Left) && (state > 1))
		{
			switchSound.play();
			state--;
		}

		if (Keyboard::isKeyPressed(Keyboard::Right) && (state < 3))
		{
			switchSound.play();
			state++;
		}

		switch (state)
		{
		case 1:
			levelTxt[0].setFillColor(Color::Red);
			levelTxt[1].setFillColor(Color::White);
			levelTxt[2].setFillColor(Color::White);
			break;

		case 2:
			levelTxt[0].setFillColor(Color::White);
			levelTxt[1].setFillColor(Color::Red);
			levelTxt[2].setFillColor(Color::White);
			break;

		case 3:
			levelTxt[0].setFillColor(Color::White);
			levelTxt[1].setFillColor(Color::White);
			levelTxt[2].setFillColor(Color::Red);
			break;
		}
	}
}

void Menu::moveArrow() // Poruszanie siê strza³ki oraz kolorowanie napisów
{
	if (pageNumber == 5)
	{
		if (Keyboard::isKeyPressed(Keyboard::Up) && (state > 2))
		{
			switchSound.play();
			arrowSprite.move(Vector2f(0.0f, -50.0f));
			state--;
		}
	}
	else
	{
		if (Keyboard::isKeyPressed(Keyboard::Up) && (state > 1))
		{
			switchSound.play();
			arrowSprite.move(Vector2f(0.0f, -50.0f));
			state--;
		}
	}
	
	if (Keyboard::isKeyPressed(Keyboard::Down) && (state < 3))
	{
		switchSound.play();
		arrowSprite.move(Vector2f(0.0f, 50.0f));
		state++;
	}
	

	switch (state)
	{
	case 1:
		playTxt.setFillColor(Color::Red);
		creditsTxt.setFillColor(Color::White);
		quitTxt.setFillColor(Color::White);
		break;

	case 2:
		playTxt.setFillColor(Color::White);
		creditsTxt.setFillColor(Color::Red);
		quitTxt.setFillColor(Color::White);
		break;
	
	case 3:
		playTxt.setFillColor(Color::White);
		creditsTxt.setFillColor(Color::White);
		quitTxt.setFillColor(Color::Red);
		break;
	}
}

/************************************************
 *  ... Funkcje rysuj¹ce
 ***********************************************/

void Menu::draw(RenderWindow& window)
{
	window.draw(landscapeSprite);
	window.draw(headerSprite);

	if (pageNumber != 6)
	{
		window.draw(arrowSprite);
		if (pageNumber == 2)
		{
			window.draw(credits);
			window.draw(backTxt);
		}
		else
		{
			window.draw(playTxt);
			window.draw(creditsTxt);
			window.draw(quitTxt);
		}
	}
	else
	{
		for (int i = 0; i < 3; i++)
		{
			window.draw(levelSprite[i][0]);
			window.draw(levelTxt[i]);
		}
		window.draw(levelSprite[state - 1][1]);
	}
}

void Menu::showScorePage()
{
	RenderWindow* window = new RenderWindow;
	window->create(VideoMode(800, 600, 32), "ScoreList");
	window->setFramerateLimit(60);

	int score = 0;
	vector<string> nameVector;
	vector<int> scoreVector;
	string line;
	ifstream file;

	file.open("playerScore.txt");
	while (!file.eof())
	{
		file >> line;
		nameVector.push_back(line);
		file >> line;
		stringstream tmp(line);
		tmp >> score;
		scoreVector.push_back(score);
	}
	file.close();

	ScoreList list;
	
	int i = 0;
	while (i < nameVector.size() - 1)
	{
		list.add_node(scoreVector[i], nameVector[i]);
		i++;
	}

	int size = nameVector.size() - 1;
	Text* sfmlText = new Text[size];

	list.saveStrings(sfmlText);

	float x = 190.0f, y = 100.0f;
	int multiplier = 0;
	for (int i = 0; i < size; i++)
	{
		multiplier += 50;
		sfmlText[i].setPosition(x, y + multiplier);
		sfmlText[i].setCharacterSize(32);
		sfmlText[i].setFillColor(Color::White);
		sfmlText[i].setFont(font);
	}
	sfmlText[0].setFillColor(Color::Yellow);

	while (window->isOpen())
	{
		Event event;
		while (window->pollEvent(event))
		{
			if ((event.type == Event::KeyPressed) && (event.key.code == Keyboard::F2 || event.key.code == Keyboard::Escape))
				window->close();

			if (event.type == Event::Closed)
				window->close();
		}

		window->clear(Color::Magenta);

		window->draw(landscapeSprite);

		for (int i = 0; i < size; i++)
			window->draw(sfmlText[i]);

		window->display();
	}
	delete window;
	delete[] sfmlText;
}

char Menu::Run(RenderWindow& window)
{
	while (window.isOpen())
	{
		// Obs³uga zdarzeñ
		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
			{
				window.close();
				break;
			}

			// Obs³uga klawiatury w menu
			if (event.type == Event::KeyPressed && event.key.code == Keyboard::Escape)
			{
				if (!EscapeButton(window)) return 'q';
			}

			if (event.type == Event::KeyPressed && event.key.code == Keyboard::Enter)
			{
				int var = EnterButton();
				if (var == -1) return 'q';
				if (pageNumber == 6)
				{
					if(var > 0)
						return connectionType;
				}
				if (pageNumber == 5)
				{
					if (var == 100) return 's';
					else if (var == 200) return 'c';
				}
			}

			if ((event.type == Event::KeyPressed && event.key.code == Keyboard::Down || event.key.code == Keyboard::Up)
				&& (pageNumber != 2) && (pageNumber != 6))
				moveArrow();
			else if (event.type == Event::KeyPressed && event.key.code == Keyboard::Left || event.key.code == Keyboard::Right)
				moveInPage6();
			if (event.type == Event::KeyPressed && event.key.code == Keyboard::F2)
				showScorePage();
		}
		// Aktualizacja menu...
		moveLandscape();

		// Rysowanie sceny
		window.clear(Color(219, 176, 239)); // Kolor wrzosowy

		draw(window);

		window.display();
	}
}

