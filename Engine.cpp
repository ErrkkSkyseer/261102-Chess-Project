#include "Engine.h"

Engine::Engine()
{
	m_isRunning = true;
}

void Engine::input()
{
	if (Keyboard::isKeyPressed(Keyboard::Key::Escape))
	{
		m_isRunning = false;
	}
	m_gm.input();
}

void Engine::update()
{
	m_gm.update();
}

void Engine::draw()
{
	m_gm.draw();
}

void Engine::run()
{
	while (m_isRunning)
	{
		input();
		update();
		draw();
	}
}
