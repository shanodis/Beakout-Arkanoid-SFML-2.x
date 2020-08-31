#ifndef ENGINE_H
#define ENGINE_H

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
using namespace sf;

#include "Menu.h"
#include "Player.h"
#include "Ball.h"
#include "Blocks.h"
#include "AnimationA.h"
#include "AnimationB.h"
#include "Scene.h"
#include "Server.h"

extern bool GameMenu(RenderWindow &window);

#endif // !ENGINE.h
