#include "Engine.h"

class Blocks
{
protected:
	float blockX, blockY;
	Texture blockTextureBlue, blockTextureYellow, blockTextureGreen;

private:
	unsigned int totalBlocks;
	Vector2f middleScreen;

private:
	void Level1();
	void Level2();
	void Level3();
	void onlineLevel();

public:
	Sprite **blockSprite;
	Sprite **verticalBlockSprite;

public:
	Blocks();
	~Blocks();
	void drawBlocks(RenderWindow&, bool verticalDrawing);
	void setLevel(unsigned int level, bool singlePlayer);
};
