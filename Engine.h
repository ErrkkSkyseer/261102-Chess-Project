#pragma once
#include<iostream>
#include<SFML/Graphics.hpp>
#include<cstdlib>

#include "GameManager.h"

#define WINDOW_WIDTH  1000
#define WINDOW_HEIGHT  1000
#define FPS_MAX  60

using namespace sf;

class Engine
{
private:
	GameManager m_gm;
	Clock m_clock;

	RenderWindow m_window = RenderWindow(sf::VideoMode({ WINDOW_WIDTH, WINDOW_HEIGHT }), "SFML window");


	void input();
	void update();
	void draw();

public:
	Engine();

	void run();
};

