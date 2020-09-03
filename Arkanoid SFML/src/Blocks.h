#include "Engine.h"
#define N 35

class Blocks
{
protected:
	float blockX, blockY;
	Texture blockTexture;

public:
	Sprite blockSprite[N];

public:
	Blocks();
	void drawBlocks(RenderWindow&);
};
