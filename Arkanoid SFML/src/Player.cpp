#include "Engine.h"

Player::Player() 
{ 
	x = 350; y = 550; 
	playerTexture.loadFromFile("data/paddle.png");
	playerSprite.setTexture(playerTexture);
	playerSprite.setPosition(x, y);
}

Player::Player(std::string filePath)
{
	x = 350; y = 10;
	playerTexture.loadFromFile(filePath);
	playerSprite.setTexture(playerTexture);
	playerSprite.setPosition(x, y);
}

void Player::movePlayerLeft(Vector2f v) 
{ 
	if (Keyboard::isKeyPressed(Keyboard::Left) && (v.x > 0)) // Bezpoœredni dostêp do klawiatury
		playerSprite.move(-10, 0); 
}

void Player::movePlayerRight(Vector2f v)
{
	if (Keyboard::isKeyPressed(Keyboard::Right) && (v.x < 440))
		playerSprite.move(10, 0);
}

void Player::movePlayer()
{
	Vector2f v = playerSprite.getPosition();
	movePlayerLeft(v);
	movePlayerRight(v);
}

bool Player::Collision(Sprite s1, Sprite s2) { return s1.getGlobalBounds().intersects(s2.getGlobalBounds()); }

bool Player::bonusCollision(Sprite& bonusSprite)
{
	if (Collision(bonusSprite, playerSprite))
	{
		bonusSprite.setPosition(0, -10000);
		return true;
	}
	return false;
}

void Player::draw(RenderWindow& window) { window.draw(playerSprite); }
