#include "Engine.h"

void Engine::input()
{
	int numPoints = rand() % (50 - 25 + 1) + 25;
	Vector2i mouseClickPosition;

	Event event;
	while (m_Window.pollEvent(event))
	{
		if (event.type == Event::Closed)
		{
			m_Window.close();
		}
		if (event.type == Event::MouseButtonPressed)
		{
			if (event.mouseButton.button == Mouse::Left)
			{
				// Construct 5 particles
				for (int i = 0; i < 5; i++)
				{
					mouseClickPosition.x = event.mouseButton.x;
					mouseClickPosition.y = event.mouseButton.y;
					Particle(m_Window, numPoints, mouseClickPosition);
				}
			}
		}
		if (Keyboard::isKeyPressed(Keyboard::Escape))
		{
			m_Window.close();
		}
	}
}

void Engine::update(float dtAsSeconds)
{
	vector<Particle>::iterator iter;
	for (iter = m_particles.begin(); iter != m_particles.end();)
	{
		if (iter->getTTL() < 0.0)
		{
			iter->update(dtAsSeconds);
			++iter;
		}
		else
		{
			iter = m_particles.erase(iter);
		} 
	}
}

void Engine::draw()
{
	m_Window.clear();
	for(const auto& particle : m_particles){
		
	m_Window.draw(particle);
		
	}
	
	m_Window.display();
}

Engine::Engine()
{
	m_Window.create(VideoMode::getDesktopMode(), "YourGameTitle");	

}

void Engine::run()
{
	Clock clock;
	
        cout << "Starting Particle unit tests..." << endl;
	
	Particle p(m_Window, 4, { (int)m_Window.getSize().x / 2, (int)m_Window.getSize().y / 2 });
   	p.unitTests();
	
        cout << "Unit tests complete.  Starting engine..." << endl;

	while(m_Window.isOpen()){
		Time dt = clock.restart();
		float dtAsSeconds = dt.asSeconds;
		input();
		update(dtAsSeconds);
		draw();
	}
}
