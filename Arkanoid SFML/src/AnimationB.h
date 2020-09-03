#include "Engine.h"

class AnimationB
{
private:
	float totalTime, switchTime;
	Vector2u currentImage, imageCount;
	Texture animationTexture;
	Clock restClock;
	IntRect uvRect;

public:
	Sprite animationSprite;

public:
	AnimationB(std::string texturePath, Vector2u imageCount, float switchTime);
	void Update(int row, float deltaTime);
	void drawAnimation(RenderWindow& window);
	void startAnimation(float deltaTime);
};
