#include "Engine.h"

class Menu
{
private:
	Texture **levelTexture, landscapeTexture, headerTexture, arrowTexture;
	Sprite **levelSprite, landscapeSprite, headerSprite, arrowSprite;
	Font font;
	Text *levelTxt, playTxt, creditsTxt, quitTxt, credits, backTxt;
	SoundBuffer switchSoundBuffer, chooseSoundBuffer;
	Sound switchSound, chooseSound;
	int direction, state, pageNumber;
	char connectionType;

private:
	void page6();
	void createPage6();
	void deletePage6();
	void moveInPage6();
	void changeArrowPositionCredits();
	void changeArrowPositionPages();
	void moveLandscape();
	bool EscapeButton(RenderWindow& window);
	int EnterButton();
	void moveArrow();
	int readState();
	void draw(RenderWindow& window);
	void showScorePage();

public:
	Menu();
	char Run(RenderWindow& window);
};
