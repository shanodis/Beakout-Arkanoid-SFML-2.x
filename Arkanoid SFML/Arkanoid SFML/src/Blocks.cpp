#include "Engine.h"

Blocks::Blocks()
{
	blockTexture.loadFromFile("data/block_red.png");

	blockX = 70; blockY = 40;
	int n = 0;
	for(int j = 0; j < 5; j++) // Oœ Y dla bloków
		for (int i = 0; i < 7; i++) // Oœ X dla blocków
		{
			blockSprite[n].setTexture(blockTexture);
			blockSprite[n].setPosition(50 + i*blockX, 120+j*blockY);
			n++;
		}
}

void Blocks::drawBlocks(RenderWindow &window)
{
	for (int i = 0; i < N; i++)
		window.draw(blockSprite[i]);
}