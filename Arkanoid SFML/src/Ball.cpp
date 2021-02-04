#include "Engine.h"
#include <math.h>

Ball::Ball()
{
	ballX = 350; ballY = 520; ballSpeed = 1.3f;
	balldx = (float)cos(250 * 3.141592 / 180) * ballSpeed; 
	balldy = (float)sin(250 * 3.141592 / 180) * ballSpeed;
	ballTexture.loadFromFile("data/ball.png");
	ballSprite.setTexture(ballTexture);
	ballSprite.setPosition(ballX, ballY);

	// Dzwieki
	paddleHitSoundBuff.loadFromFile("data/Sounds/hit.wav");
	paddleHitSound.setBuffer(paddleHitSoundBuff);
	paddleHitSound.setVolume(5.0f);
	brickHitSoundBuff.loadFromFile("data/Sounds/brick hit.wav");
	brickHitSound.setBuffer(brickHitSoundBuff);
	brickHitSound.setVolume(5.0f);
}

Ball::Ball(float x, float y)
{
	ballX = x; ballY = y; ballSpeed = 1.3f;
	balldx = (float)cos(250 * 3.141592 / 180) * ballSpeed;
	balldy = (float)sin(250 * 3.141592 / 180) * ballSpeed;
	ballTexture.loadFromFile("data/ball.png");
	ballSprite.setTexture(ballTexture);
	ballSprite.setPosition(ballX, ballY);

	// Dzwieki
	paddleHitSoundBuff.loadFromFile("data/Sounds/hit.wav");
	paddleHitSound.setBuffer(paddleHitSoundBuff);
	paddleHitSound.setVolume(30.0f);
	brickHitSoundBuff.loadFromFile("data/Sounds/brick hit.wav");
	brickHitSound.setBuffer(brickHitSoundBuff);
	brickHitSound.setVolume(30.0f);
}

void Ball::setStartPosition(bool goToPaddle)
{
	ballSprite.setPosition(300.0f, 500.0f);
	if(goToPaddle)
		balldy = -balldy;
}

bool Ball::moveBall(bool isSecondPlayer)
{
	ballSprite.move(6 * balldx, 6 * balldy);

	Vector2f v = ballSprite.getPosition();
	if (v.x <= 0 || v.x > 520)
	{
		paddleHitSound.play();
		balldx = -balldx;
	}
	if (v.y < 0 || v.y > 560)
	{
		paddleHitSound.play();
		balldy = -balldy;
	}

	if (v.y > 550) return false;
	if (isSecondPlayer && v.y <= 0) return false;

	return true;
}

bool Ball::moveBall(float ballPositionX, float ballPositionY)
{

	ballSprite.setPosition(ballPositionX, ballPositionY);
	Vector2f v = ballSprite.getPosition();
	if (v.x <= 0 || v.x > 520)
	{
		paddleHitSound.play();
		balldx = -balldx;
	}
	if (v.y < 0 || v.y > 560)
	{
		paddleHitSound.play();
		balldy = -balldy;
	}

	if (v.y > 550) return false;

	return true;
}

bool Ball::Collision(Sprite s1, Sprite s2) { return s1.getGlobalBounds().intersects(s2.getGlobalBounds()); }

bool Ball::secondPlayerCollision(Sprite playerSprite)
{
	if (Collision(playerSprite, ballSprite))
	{
		
		int angle, dir = rand() % 2;
		if (dir == 0)	angle = -(240 + rand() % 30);
		else    angle = -(310 - rand() % 30);

		balldx = (float)cos(angle * 3.141592 / 180) * ballSpeed;
		balldy = (float)sin(angle * 3.141592 / 180) * ballSpeed;

		return true;
	}
	return false;
}

bool Ball::paddleCollision(Sprite playerSprite, bool isSecondPlayer)
{
	if (isSecondPlayer)
	{
		if (secondPlayerCollision(playerSprite))
			return true;
	}
	else
	{
		if (Collision(playerSprite, ballSprite))
		{
			paddleHitSound.play();
			int angle = 240 + rand() % 30, dir = rand() % 2;
			if (dir == 0)	angle = 240 + rand() % 30;
			else    angle = 310 - rand() % 30;

			balldx = (float)cos(angle * 3.141592 / 180) * ballSpeed;
			balldy = (float)sin(angle * 3.141592 / 180) * ballSpeed;

			return true;
		}
	}
	return false;
}

bool Ball::blockCollision(Sprite **blockSprite)
{
	for (int i = 0; i < N; i++)
	{
		if (Collision(ballSprite, blockSprite[i][0]))
		{
			brickHitSound.play();
			blockSprite[i][0].setPosition(-1000, 0);
			balldy = -balldy;
			return true;
		}
		else if (Collision(ballSprite, blockSprite[i][1]))
		{
			brickHitSound.play();
			blockSprite[i][1].setPosition(-1000, 0);
			balldy = -balldy;
			return true;
		}
	}

	for (int i = 0; i < N; i++)
	{
		if (Collision(ballSprite, blockSprite[i][0]))
		{
			blockSprite[i][0].setPosition(-1000, 0);
			balldx = -balldx;
			return true;
		}
		else if (Collision(ballSprite, blockSprite[i][1]))
		{
			blockSprite[i][1].setPosition(-1000, 0);
			balldx = -balldx;
			return true;
		}
	}
	return false;
}

bool Ball::blockCollision(Sprite **blockSprite, Vector2u& blockNumber)
{
	for (int i = 0; i < N; i++)
	{
		if (Collision(ballSprite, blockSprite[i][0]))
		{
			blockSprite[i][0].setPosition(-1000, 0);
			balldy = -balldy;
			blockNumber.x = i;
			return true;
		}
		else if (Collision(ballSprite, blockSprite[i][1]))
		{
			blockSprite[i][1].setPosition(-1000, 0);
			balldy = -balldy;
			blockNumber.y = i;
			return true;
		}
	}

	for (int i = 0; i < N; i++)
	{
		if (Collision(ballSprite, blockSprite[i][0]))
		{
			blockSprite[i][0].setPosition(-1000, 0);
			balldx = -balldx;
			blockNumber.x = i;
			return true;
		}
		else if (Collision(ballSprite, blockSprite[i][1]))
		{
			blockSprite[i][1].setPosition(-1000, 0);
			balldx = -balldx;
			blockNumber.y = i;
			return true;
		}
	}
	return false;
}

void Ball::draw(RenderWindow& window) { window.draw(ballSprite); }