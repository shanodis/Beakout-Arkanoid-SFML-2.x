#include "Engine.h"

class Blocks
{
protected:
	float blockX, blockY;
	Texture blockTextureRed, blockTextureYellow, blockTextureGreen;

private:
	unsigned int totalBlocks;
	Vector2f middleScreen;

private:
	void Level1();
	void onlineLevel1();
	void onlineLevel2();
	void onlineLevel3();

public:
	Sprite **blockSprite;
	Sprite **verticalBlockSprite;

public:
	Blocks();
	~Blocks();
	void drawBlocks(RenderWindow&, bool verticalDrawing);
	void setLevel(unsigned int level, bool singlePlayer);
};
