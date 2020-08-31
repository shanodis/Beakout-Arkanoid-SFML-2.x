#include "Engine.h"

class AnimationA
{
private:
	Texture *animationTexture;
	float totalTime, switchTime;
	int totalElements;

public:
	Sprite *animationSprite;
	int counter;

public:
	AnimationA(std::string, std::string, std::string, int, float);
	~AnimationA();
	void Update(RenderWindow&, float);
};
