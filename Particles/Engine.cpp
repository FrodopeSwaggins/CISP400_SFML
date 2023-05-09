#include "Engine.h"

void Engine::input()
{
	Event event;

	while (m_Window.pollEvent(event)) 
	{
		switch (event.type) 
		{
			case Event::Closed:
				m_Window.close();
				break;

			case Event::KeyPressed:
				if (event.key.code == Keyboard::Escape) 
				{
					m_Window.close();
				}
				break;

			case Event::MouseButtonPressed:
				if (event.mouseButton.button == Mouse::Left) 
				{
					for (int i = 0; i < 5; i++) 
					{
						int numPoints = rand() % 26 + 25;
						m_particles.emplace_back(m_Window, numPoints, Mouse::getPosition(m_Window));
					}
				}
				break;
		}
	}
}

void Engine::update(float dtAsSeconds)
{

	for (auto it = m_particles.begin(); it != m_particles.end();)
	{
		if (it->getTTL() > 0.0)
		{
			it->update(dtAsSeconds);
			++it;
		}
		else
		{
			it = m_particles.erase(it);
		}
	}
}

void Engine::draw()
{
	m_Window.clear();

	for (int i = 0; i < m_particles.size(); i++)
	{
		m_Window.draw(m_particles.at(i));
	}

	m_Window.display();
}

Engine::Engine()
{
	m_Window.create(VideoMode::getDesktopMode(), "Particles", Style::Fullscreen);
}

void Engine::run()
{

	cout << "Starting Particle unit tests..." << endl;
	Particle p(m_Window, 4, { (int)m_Window.getSize().x / 2, (int)m_Window.getSize().y / 2 });
	p.unitTests();
	cout << "Unit tests complete.  Starting engine..." << endl;

	while (m_Window.isOpen())
	{
		clock_t clock = std::clock();

		input();
		update((double)(std::clock() - clock) / CLOCKS_PER_SEC);
		draw();
	}
}