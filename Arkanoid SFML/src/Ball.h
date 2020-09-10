#include "Engine.h"

class Ball
{
protected:
	float ballX, ballY, balldx, balldy, ballSpeed;
	Texture ballTexture;

public:
	Sprite ballSprite;

private:
	bool Collision(Sprite s1, Sprite s2);
	bool secondPlayerCollision(Sprite playerSprite);

public:
	Ball();
	Ball(float x, float y);
	bool moveBall(bool isSecondPlayer);
	bool moveBall(float x, float y);
	void setStartPosition(bool goToPaddle);
	bool paddleCollision(Sprite playerSprite, bool isSecondPlayer);
	bool blockCollision(Sprite **blockSprite);
	bool blockCollision(Sprite **blockSprite, Vector2u& blockNumber);
	void draw(RenderWindow &window);
};
