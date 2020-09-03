#include "Engine.h"
#include <iostream>
#include <string>
#include <sstream>

AnimationA::AnimationA(std::string folder, std::string firstFile, std::string fileType, int n, float switchTime)
{
	this->switchTime = switchTime;
	totalTime = 0.0f;
	counter = 0;
	totalElements = n;
	animationTexture = new Texture[totalElements];
	animationSprite = new Sprite[totalElements];

	for (int i = 0; i < n; i++)
	{
		std::stringstream stream;
		stream << i + 1;
		std::string aux;
		stream >> aux;
		std::string filePath = folder + "/" + firstFile + "_" + aux + fileType;
		animationTexture[i].loadFromFile(filePath);

		animationSprite[i].setTexture(animationTexture[i]);
		animationSprite[i].setPosition(350, 300);
		animationSprite[i].setScale(Vector2f(0.05f, 0.05f));
	}
}

AnimationA::~AnimationA() { delete[] animationTexture, animationSprite; }

void AnimationA::Update(RenderWindow& window, float deltaTime)
{
	totalTime += deltaTime;
	if (totalTime >= switchTime)
	{
		totalTime -= switchTime;
		if (counter >= totalElements - 1) counter = 0;
		else counter++;
	}
}