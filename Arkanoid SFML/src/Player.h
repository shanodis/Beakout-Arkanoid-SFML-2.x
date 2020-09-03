#include "Engine.h"

class Player
{
protected:
	float x, y;
	Texture playerTexture;
	void movePlayerLeft(Vector2f);
	void movePlayerRight(Vector2f);

public:
	Sprite playerSprite;

private:
	bool Collision(Sprite s1, Sprite s2);

public:
	Player();
	Player(std::string filePath);
	void movePlayer();
	bool bonusCollision(Sprite& bonusSprite);
	void draw(RenderWindow& window);
};

