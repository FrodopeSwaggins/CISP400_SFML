#include "Engine.h"

void Engine::input()
{
	Event event;

	while (m_Window.pollEvent(event)) 
	{
		switch (event.type) 
		{
			case sf::Event::Closed:
				m_Window.close();
				break;

			case sf::Event::KeyPressed:
				if (event.key.code == sf::Keyboard::Escape) 
				{
					m_Window.close();
				}
				break;

			case sf::Event::MouseButtonPressed:
				if (event.mouseButton.button == sf::Mouse::Left) 
				{
					sf::Vector2i mousePos = sf::Mouse::getPosition(m_Window);
					for (int i = 0; i < 5; i++) 
					{
						int numPoints = rand() % 26 + 25;
						m_particles.emplace_back(m_Window, numPoints, mousePos);
					}
				}
				break;

			default:
				break;
		}
	}
}

void Engine::update(float dtAsSeconds)
{
	for (auto i = m_particles.begin(); i != m_particles.end();)
	{
		if (i->getTTL() > 0.0)
		{
			i->update(dtAsSeconds);
			++i;
		}
		else
		{
			i = m_particles.erase(i);
		}
	}
}

void Engine::draw()
{
	m_Window.clear();

	for (auto& i : m_particles)
	{
		m_Window.draw(i);
	}
	m_Window.display();
}

Engine::Engine()
{
	m_Window.create(VideoMode::getDesktopMode(), "Particles", Style::Fullscreen);
}

void Engine::run()
{
	Clock clock;

	cout << "Starting Particle unit tests..." << endl;
	Particle p(m_Window, 4, { (int)m_Window.getSize().x / 2, (int)m_Window.getSize().y / 2 });
	p.unitTests();
	cout << "Unit tests complete.  Starting engine..." << endl;

	while (m_Window.isOpen())
	{
		clock.restart();
		float seconds = clock.getElapsedTime().asSeconds();

		input();
		update(seconds);
		draw();
	}
}