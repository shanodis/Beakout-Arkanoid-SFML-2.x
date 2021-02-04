#pragma once
#include "Engine.h"

class App
{
private:
	RenderWindow window;
	char gameplayType;

private:
	char GameMenu();
	bool playOnline();
	bool Level_1();
	bool Level_2();
	bool Level_3();

public:
	App();
	void Run();
};