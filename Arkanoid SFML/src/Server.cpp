#include "Engine.h"
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

Server::Server(char gameplayType)
{
	fstream file;
	string line;
	file.open("IpAddress.txt");
	if (file.is_open())
	{
		while (getline(file, line))
			cout << line << endl;
		file.close();
	}
	else
		cout << "Cannot open the file !" << endl;

	ip = line;
	port = 7777;
	mode = 'n';
	connectionType = gameplayType;
	blockNumber = 0;
}

bool Server::Connect()
{
	if (connectionType == 's')
	{
		if (listener.listen(port) != Socket::Done)
		{
			cerr << "Cannot listen to port: " << port << endl;
			exit(1);
		}
		listener.accept(socket);
		mode = 's';
		return true;
	}
	else if (connectionType == 'c')
	{
		if (socket.connect(ip, port) != Socket::Done)
		{
			cerr << "Cannot connect to " << ip.toString() << endl;
			exit(1);
		}
		mode = 'r';
		return true;
	}
	socket.setBlocking(false);

	return false;
}

void Server::updateBall(Player player2)
{
	// Multiplayer

	if (mode == 's') // tryb wysy�ania danych
	{
		moveBall(true);
		paddleCollision(playerSprite, false);
		paddleCollision(player2.playerSprite, true);
		blockCollision(blockSprite, blockNumber);
		Packet packet;
		packet << ballSprite.getPosition().x << ballSprite.getPosition().y << blockNumber;
		socket.send(packet);
	}
	else if (mode == 'r') // tryb otrzymywania danych
	{
		Packet packet;
		socket.receive(packet);

		if (packet >> b2Position.x >> b2Position.y >> blockNumber)
		{
			verticalBlockSprite[blockNumber].setPosition(-1000, 0);
			moveBall(b2Position.x, 560 - b2Position.y);
		}
	}
}

void Server::updateBlocks()
{
	if (mode == 's') // tryb wysy�ania danych
	{
		if (blockCollision(blockSprite, blockNumber))
		{
			Packet packet;
			packet << blockNumber;
			socket.send(packet);
		}
	}
	else if (mode == 'r') // tryb otrzymywania danych
	{
		Packet packet;
		socket.receive(packet);
		if (packet >> blockNumber)
		{
			blockSprite[blockNumber].setPosition(-1000, 0);
		}
	}
}

void Server::updatePlayer(Player& player2)
{
	if (update)
		movePlayer(); // Ruch gracza

	Packet playerPacket;
	if (prevposition != playerSprite.getPosition())
	{
		block = true;
		playerPacket << playerSprite.getPosition().x << playerSprite.getPosition().y << block;
		socket.send(playerPacket);
	}
	socket.receive(playerPacket);
	if (playerPacket >> p2Position.x >> p2Position.y >> block)
	{
		if (block)
			player2.playerSprite.setPosition(p2Position.x, 560 - p2Position.y);
		block = false;
	}
}

void Server::Run(RenderWindow& window)
{
	if (Connect())
		cout << "Connected!";
	else
		return;

	Player player2("data/paddle.png");

	while (window.isOpen())
	{
		// Obs�uga zdarze�
		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed) window.close();

			if (event.type == Event::KeyPressed && event.key.code == Keyboard::Escape) // Dost�p do klawiatury za pomoc� zdarze�
				window.close();

			if (event.type == Event::GainedFocus)
				update = true;
			if (event.type == Event::LostFocus)
				update = false;
		}

		updateBall(player2);
		updatePlayer(player2);
		//updateBlocks();

		// Rysowanie sceny
		window.clear(Color(219, 176, 239)); // Kolor wrzosowy

		Player::draw(window);
		player2.draw(window);
		Ball::draw(window);
		if (mode == 'r')
			drawBlocks(window, true);
		else if (mode == 's')
			drawBlocks(window, false);
		drawInterface(window);

		window.display();
	}
}
