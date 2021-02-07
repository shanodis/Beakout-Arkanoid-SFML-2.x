#pragma once
#include "Engine.h"

class App
{
private:
	RenderWindow window;
	Music themeMusic;
	Texture textBarTexture, backgroundTexture;
	Sprite textBarSprite, backgroundSprite;
	Text sfmlText, enterTxtText;
	Font font;
	char gameplayType;

private:
	char GameMenu();
	bool playOnline();
	void Level_1();
	void Level_2();
	void Level_3();
	void saveScoreWindow();
	void saveToFile(string playerName);
	void drawScoreWindow();

public:
	App();
	void Run();
};