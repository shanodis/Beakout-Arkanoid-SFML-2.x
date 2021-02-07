#include "App.h"
#include <fstream>

App::App() 
{ 
	window.create(VideoMode(800, 600, 32), "Arkanoid");
	window.setFramerateLimit(60);
	gameplayType = 0;
	themeMusic.openFromFile("data/theme.ogg");
	themeMusic.play();
	themeMusic.setLoop(true);
	themeMusic.setVolume(20.0f);

	// Okno zapisu wyników
	font.loadFromFile("data/font1.ttf");
	sfmlText.setFillColor(Color::Black);
	sfmlText.setFont(font);
	sfmlText.setCharacterSize(32);
	sfmlText.setPosition(200.0f, 300.0f);
	enterTxtText.setFillColor(Color::White);
	enterTxtText.setFont(font);
	enterTxtText.setCharacterSize(32);
	enterTxtText.setPosition(200.0f, 250.0f);
	enterTxtText.setString("Enter your nickname:");
	textBarTexture.loadFromFile("data/textbox.png");
	textBarSprite.setTexture(textBarTexture);
	textBarSprite.setPosition(190.0f, 300.0f);
	textBarSprite.setScale(0.23f, 0.23f);

	backgroundTexture.loadFromFile("data/fortress.png");
	backgroundTexture.setSmooth(true);
	backgroundSprite.setTexture(backgroundTexture);
}

char App::GameMenu()
{
	Menu menu;
	char connectionType = menu.Run(window);

	return connectionType;
}

bool App::playOnline()
{
	Server server(gameplayType);
	server.Run(window);

	return false;
}

void App::Level_1()
{
	Scene scene(1);
	scene.Run(window);
}

void App::Level_2()
{
	Scene scene(2);
	scene.Run(window);
}

void App::Level_3()
{
	Scene scene(3);
	scene.Run(window);
}

void App::drawScoreWindow()
{
	window.draw(backgroundSprite);
	window.draw(textBarSprite);
	window.draw(enterTxtText);
	window.draw(sfmlText);
}

void App::saveToFile(string playerName)
{
	if (playerName != "")
	{
		ifstream outfile;
		outfile.open("score.txt");
		int score;
		outfile >> score;
		outfile.close();

		ofstream infile;
		infile.open("playerScore.txt", ios::app);
		infile << playerName << " " << score << endl;
		infile.close();
	}
}

void App::saveScoreWindow()
{
	window.create(VideoMode(800, 600, 32), "Arkanoid");
	window.setFramerateLimit(60);
	string playerName;

	while (window.isOpen())
	{
		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::TextEntered)
			{
				if (event.text.unicode != 32)
				{
					if (event.text.unicode != 8)
						playerName += (char)event.text.unicode;
					else
						playerName = playerName.substr(0, playerName.length() - 1);

					sfmlText.setString(playerName);
				}
			}

			if (event.type == Event::KeyPressed && event.key.code == Keyboard::Enter)
			{
				saveToFile(playerName);
				window.close();
			}
		}

		window.clear(Color(219, 176, 239));
		drawScoreWindow();
		window.display();
	}
}

void App::Run()
{
	srand(time(0));
	while (true)
	{
		gameplayType = GameMenu();

		switch (gameplayType)
		{
		case '1':
			Level_1();
			saveScoreWindow();
			break;

		case '2':
			Level_2();
			saveScoreWindow();
			break;

		case '3':
			Level_3();
			saveScoreWindow();
			break;

		case 'q':
			break;

		default:
			if (!playOnline()) break;
		}
		
		break;
	}
}