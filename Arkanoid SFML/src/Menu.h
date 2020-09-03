#include "Engine.h"

class Menu
{
private:
	Texture landscapeTexture, headerTexture, arrowTexture;
	Sprite landscapeSprite, headerSprite, arrowSprite;
	Font font;
	Text playTxt, creditsTxt, quitTxt, credits, backTxt;
	SoundBuffer switchSoundBuffer, chooseSoundBuffer;
	Music themeMusic;
	Sound switchSound, chooseSound;
	int direction, state, pageNumber;
	char connectionType;

private:
	void changeArrowPositionCredits();
	void changeArrowPositionPages();
	void moveLandscape();
	bool EscapeButton(RenderWindow& window);
	int EnterButton();
	void moveArrow();
	int readState();
	void draw(RenderWindow& window);

public:
	Menu();
	char Run(RenderWindow& window);
};
