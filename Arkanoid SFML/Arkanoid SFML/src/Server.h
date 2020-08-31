#include "Engine.h"

class Server : public Scene
{
protected:
	IpAddress ip;
	TcpSocket socket;
	TcpListener listener;
	Vector2f prevposition, p2Position, b2Position;
	unsigned int port;
	char connectionType, mode;
	bool update = false, block = false;

private:
	std::string enterIpServer();
	bool Connect();
	void updateBall(Player player2);
	void updatePlayer(Player& player2);
	void updateBlocks();

public:
	Server();
	void Run(RenderWindow& window);
};