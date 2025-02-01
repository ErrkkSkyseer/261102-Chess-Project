#pragma once
#include<iostream>
#include<SFML/Graphics.hpp>
#include<cstdlib>

#include "GameManager.h"

using namespace sf;

class Engine
{
private:
	GameManager m_gm;
	bool m_isRunning;

	void input();
	void update();
	void draw();

public:
	Engine();

	void run();
};

