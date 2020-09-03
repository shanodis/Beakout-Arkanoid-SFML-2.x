#include "Engine.h"

class Scene : public Player, public Ball, public Blocks
{
private:
	RectangleShape *rectangle;
	Texture heartTexture, landscapeTexture;
	Sprite heartSprite[3], landscapeSprite;
	Font font;
	Text liveText, scoreText, timeText;
	Clock clock;
	int minutes, seconds, lives;

public:
	int score;

private:
	void drawHearts(RenderWindow&, int);

public:
	Scene();
	Scene(unsigned int level);
	~Scene();
	void drawInterface(RenderWindow& window);
	void gameTime();
	void showTime(int, int);
	void showScore();
	void drawGame(RenderWindow&,int);
};
