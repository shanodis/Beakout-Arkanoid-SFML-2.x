#include "App.h"

App::App() 
{ 
	window.create(VideoMode(800, 600, 32), "Arkanoid");
	window.setFramerateLimit(60);
	gameplayType = 0;
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

bool App::Level_1()
{
	Scene scene(1);
	scene.Run(window);

	return false;
}

bool App::Level_2()
{
	Scene scene(2);
	scene.Run(window);

	return false;
}

bool App::Level_3()
{
	Scene scene(3);
	scene.Run(window);

	return false;
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
			if (!Level_1()) break;
		case '2':
			if (!Level_2()) break;
		case '3':
			if (!Level_3()) break;

		case 'q':
			break;

		default:
			if (!playOnline()) break;
		}
		break;
	}
}