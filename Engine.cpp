#include "Engine.h"

Engine::Engine()
{
	m_window.setFramerateLimit(FPS_MAX);
}

void Engine::input()
{
	vector<optional<Event>> eventCollections;
	while (const optional sfEvent = m_window.pollEvent())
	{
		eventCollections.push_back(sfEvent);
	}

	auto it = eventCollections.begin();
	auto end = eventCollections.end();
	for (auto& sfEvent = it; it != end; sfEvent++)
	{
		if ((*sfEvent)->is<Event::Closed>())
			m_window.close();
	}

		m_gm.input(eventCollections);
}

void Engine::update()
{
	m_gm.update(m_clock.restart().asSeconds());
}

void Engine::draw()
{
	m_window.clear();
	m_gm.draw(m_window);
	m_window.display();
}

void Engine::run()
{
	while (m_window.isOpen())
	{
		input();
		update();
		draw();
	}
}
