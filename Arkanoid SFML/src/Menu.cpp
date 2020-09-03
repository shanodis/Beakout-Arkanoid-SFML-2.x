#include "Engine.h"
#include <iostream>
#include <fstream>

/************************************************
 *  ... Konstruktor inicjalizuj¹cy
 ***********************************************/

Menu::Menu()
{
	direction = 0; pageNumber = state = 1;
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
	playTxt.setPosition(20, 200);

	// Ustawienia tekstu creditsTxt
	creditsTxt.setFont(font);
	creditsTxt.setCharacterSize(34);
	creditsTxt.setFillColor(Color::White);
	creditsTxt.setString("Credits");
	creditsTxt.setPosition(20, 250);

	// Ustawienia tekstu quitTxt
	quitTxt.setFont(font);
	quitTxt.setCharacterSize(34);
	quitTxt.setFillColor(Color::White);
	quitTxt.setString("Exit");
	quitTxt.setPosition(20, 300);

	// Ustawienia tekstu credits
	credits.setFont(font);
	credits.setCharacterSize(34);
	credits.setFillColor(Color::White);
	credits.setString("Created by Dominik Grudzieñ\nSources:\nhttps://opengameart.org");
	credits.setPosition(200, 300);

	// Ustawienia tekstu backTxt
	backTxt.setFont(font);
	backTxt.setCharacterSize(34);
	backTxt.setFillColor(Color::Red);
	backTxt.setString("Back");
	backTxt.setPosition(90, 500);

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
	arrowSprite.setPosition(130, 210);
	arrowSprite.setScale(Vector2f(0.05f, 0.05f));

	// Ustawienia nag³ówka
	headerSprite.setScale(Vector2f(2.0f, 2.0f));
	headerSprite.setColor(Color(255, 255, 255, 128));
	headerSprite.setPosition(0, -150);

	// Ustawienia muzyki
	switchSoundBuffer.loadFromFile("data/Sounds/misc_menu_4.wav");
	switchSound.setBuffer(switchSoundBuffer);
	/*themeMusic.openFromFile("data/theme.ogg");
	themeMusic.play();
	themeMusic.setLoop(true);*/
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

void Menu::changeArrowPositionCredits() // Zmiana pozycji strza³ki przy stronie credits
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
			if (pageNumber == 1) changeArrowPositionPages();
			if (pageNumber != 4)
			{
				pageNumber = 3;
				playTxt.setString("Singleplayer");
				creditsTxt.setString("Multiplayer");
				quitTxt.setString("Back");
			}
			if (pageNumber == 4)
			{
				state = 2;
				pageNumber = 5;
				changeArrowPositionPages();
				creditsTxt.setPosition(20, 200);
				playTxt.setString("Remember to enter your server ip in IpAddress.txt");
				playTxt.setFillColor(Color::White);
				creditsTxt.setFillColor(Color::Red);
				creditsTxt.setString("Connect");
				creditsTxt.setPosition(20, 400);
				quitTxt.setPosition(20, 450);
				connectionType = 'c';
			}
			return 1;

		case 2:
			if (pageNumber == 1)
			{
				pageNumber = 2;
				changeArrowPositionCredits();
			}
			if (pageNumber == 4)
			{
				pageNumber = 5;
				changeArrowPositionPages();
				playTxt.setString("Remember to enter your server ip in IpAddress.txt");
				creditsTxt.setString("Connect");
				creditsTxt.setPosition(20, 400);
				quitTxt.setPosition(20, 450);
				connectionType = 's';
			}
			if (pageNumber == 3)
			{
				pageNumber = 4;
				playTxt.setString("Join game");
				creditsTxt.setString("Host game"); 
				quitTxt.setString("Back");
			}
			return 2;

		case 3:
			if (pageNumber == 1) return -1;
			if (pageNumber == 3)
			{
				changeArrowPositionPages();
				pageNumber = 1;
				playTxt.setString("Play");
				creditsTxt.setString("Credits");
				quitTxt.setString("Exit");
			}
			if (pageNumber == 4)
			{
				pageNumber = 3;
				playTxt.setString("Singleplayer");
				creditsTxt.setString("Multiplayer");
				quitTxt.setString("Back");
			}
			return 3;
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
				if (pageNumber == 5)
				{
					if (var == 100) return 's';
					else if (var == 200) return 'c';
				}
			}

			if ((event.type == Event::KeyPressed && event.key.code == Keyboard::Down || event.key.code == Keyboard::Up)
				&& (pageNumber != 2))
				moveArrow();
		}
		// Aktualizacja menu...
		moveLandscape();

		// Rysowanie sceny
		window.clear(Color(219, 176, 239)); // Kolor wrzosowy

		draw(window);

		window.display();
	}
}

