#include "Engine.h"

class Scene : public Player, public Ball, public Blocks
{
private:
	RectangleShape *rectangle;
	Texture heartTexture, landscapeTexture;
	Sprite *heartSprite, landscapeSprite;
	Font font;
	Text liveText, scoreText, timeText;
	Clock clock;
	int minutes, seconds, lives;
	unsigned int level;

public:
	int score;

private:
	void playerCollisions(AnimationB& heart);
	void drawHearts(RenderWindow&);
	void setInterface();

public:
	Scene();
	Scene(unsigned int level);
	~Scene();
	void Run(RenderWindow& window);
	void drawInterface(RenderWindow& window);
	void gameTime();
	void showTime();
	void showScore();
	void drawGame(RenderWindow&);
};
