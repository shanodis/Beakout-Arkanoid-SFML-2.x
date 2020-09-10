#include "Engine.h"

Blocks::Blocks() 
{ 
	blockX = blockY = 0; 
	blockSprite = verticalBlockSprite = NULL;
}

Blocks::~Blocks()
{
	delete[] blockSprite;
	delete[] verticalBlockSprite;
}

void Blocks::Level1()
{
	blockSprite = new Sprite[N];
	blockTextureRed.loadFromFile("data/block green.png");
	blockX = 70; blockY = 40;
	int n = 0;
	for (int j = 0; j < 5; j++) // Oœ Y dla bloków
		for (int i = 0; i < 7; i++) // Oœ X dla blocków
		{
			blockSprite[n].setTexture(blockTextureRed);
			blockSprite[n].setPosition(50 + i * blockX, 120 + j * blockY);
			n++;
		}
}

void Blocks::onlineLevel1()
{
	blockSprite = new Sprite[N];
	verticalBlockSprite = new Sprite[N];
	blockTextureYellow.loadFromFile("data/block yellow.png");
	blockX = 70; blockY = 40;
	for (int i = 0; i < N; i++)
	{
		blockSprite[i].setTexture(blockTextureYellow);
		blockSprite[i].setPosition(-1000, 0);
		verticalBlockSprite[i].setTexture(blockTextureYellow);
		verticalBlockSprite[i].setPosition(-1000, 0);
	}

	int i, j, n = 0;
	for (i = 3; i > 0; i--) // Poziom 2 Online, Schodki wywrócone
	{
		for (j = i; j > 0; j--)
		{
			int x = 330 + j * blockX;
			int y = 140 + i * blockY;
			blockSprite[n].setPosition(x, y);
			n++;
		}
	}

	for (i = 0; i < 3; i++)
	{
		for (j = i; j < 3; j++)
		{
			int x = 190 + j * blockX;
			int y = 300 + i * blockY;
			blockSprite[n].setPosition(x, y);
			n++;
		}
	}
}
void Blocks::onlineLevel2()
{
	blockSprite = new Sprite[N];
	verticalBlockSprite = new Sprite[N];
	blockTextureRed.loadFromFile("data/block_red.png");
	blockTextureYellow.loadFromFile("data/block yellow.png");
	blockX = 70; blockY = 40;
	for (int i = 0; i < N; i++)
	{
		blockSprite[i].setTexture(blockTextureRed);
		blockSprite[i].setPosition(-1000, 0);
		verticalBlockSprite[i].setTexture(blockTextureRed);
		verticalBlockSprite[i].setPosition(-1000, 0);
	}

	middleScreen.x = 360.0f; middleScreen.y = 260.0f;

	int i, j, n = 0;

	for (i = 0; i < 2; i++)
	{
		for (j = 0; j < 3; j++)
		{
			int x = j * blockX;
			int y = (int)middleScreen.y + (40 * i);
			blockSprite[n].setPosition(x, y);
			n++;
		}
	}
	for (i = 0; i < 3; i++)
	{
		int x = 570 - (int)middleScreen.x + (40 * i);
		int y = (int)middleScreen.y - (40 * i);
		blockSprite[n].setPosition(x, y);
		blockSprite[n].setTexture(blockTextureYellow);
		n++;
	}
	for (i = 0; i < 3; i++)
	{
		int x = 570 - (int)middleScreen.x + (40 * i);
		int y = 40 + (int)middleScreen.y + (40 * i);
		blockSprite[n].setPosition(x, y);
		blockSprite[n].setTexture(blockTextureYellow);
		n++;
	}
	for (i = 0; i < 2; i++)
	{
		for (j = 0; j < 3; j++)
		{
			int x = 600 + j * blockX;
			int y = (int)middleScreen.y + (40 * i);
			blockSprite[n].setPosition(x, y);
			blockSprite[n].setTexture(blockTextureYellow);
			n++;
		}
	}

	/*for (i = 0; i < 3; i++)
	{
		int x = 10 + middleScreen.x + (40 * i);
		int y = -80 + (int)middleScreen.y + (40 * i);
		blockSprite[n].setPosition(x, y);
		n++;
	}

	for (i = 0; i < 3; i++)
	{
		int x = 10 + middleScreen.x + (40 * i);
		int y = 120 + (int)middleScreen.y - (40 * i);
		blockSprite[n].setPosition(x, y);
		n++;
	}*/
}

void Blocks::onlineLevel3()
{
	int i, j, n = 0;
	for (i = 7; i > 0; i--) // Poziom 3 Online, Schodki
	{
		for (j = i; j > 0; j--)
		{
			int x = 50 + j * blockX;
			int y = 120 + i * blockY;
			blockSprite[n].setPosition(x, y);
			n++;
		}
	}
}

void Blocks::setLevel(unsigned int level, bool singlePlayer)
{
	if (singlePlayer)
	{
		switch (level)
		{
		case 1:
			Level1();
			break;

		default: break;
		}
	}
	else
	{
		switch (level)
		{
		case 1:
			onlineLevel1();
			break;
		case 2:
			onlineLevel2();
			break;
		case 3:
			onlineLevel3();

		default: break;
		}
	}
}

void Blocks::drawBlocks(RenderWindow &window, bool verticalDrawing)
{
	if (verticalDrawing)
	{
		for (int i = 0; i < N; i++)
			window.draw(verticalBlockSprite[i]);
	}
	else
	{
		for (int i = 0; i < N; i++)
			window.draw(blockSprite[i]);
	}
}