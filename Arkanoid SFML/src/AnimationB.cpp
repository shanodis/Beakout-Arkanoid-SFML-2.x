#include "Engine.h"

AnimationB::AnimationB(std::string texturePath, Vector2u imageCount, float switchTime)
{
	animationTexture.loadFromFile(texturePath);
	animationSprite.setTexture(animationTexture);
	animationSprite.setScale(0.05f, 0.05f);
	animationSprite.setPosition(200, 300);

	this->imageCount = imageCount;
	this->switchTime = switchTime;
	totalTime = 0.0f;
	currentImage.x = 0;
	uvRect.width = animationTexture.getSize().x / float(imageCount.x);
	uvRect.height = animationTexture.getSize().y / float(imageCount.y);
}

void AnimationB::Update(int row, float deltaTime)
{
	currentImage.y = row;
	totalTime += deltaTime;

	if (totalTime >= switchTime)
	{
		totalTime -= switchTime;
		currentImage.x++;

		if ((currentImage.x >= imageCount.x) || (restClock.getElapsedTime().asSeconds() >= 42))
		{
			currentImage.x = 0;
		}
	}

	uvRect.left = currentImage.x * uvRect.width;
	uvRect.top = currentImage.y * uvRect.height;
	
}

void AnimationB::drawAnimation(RenderWindow& window) 
{
	if (restClock.getElapsedTime().asSeconds() >= 40)
	{
		animationSprite.move(Vector2f(0, 5));
		window.draw(animationSprite);
	}
}

void AnimationB::startAnimation(float deltaTime)
{
	Update(0, deltaTime);
	if (restClock.getElapsedTime().asSeconds() >= 43)
	{
		animationSprite.setPosition(200, 300);
		restClock.restart();
	}
	animationSprite.setTextureRect(uvRect);
}