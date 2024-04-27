#include "Engine.h"

void Engine::input()
{
	int numPoints = rand() % (50 - 25 + 1) + 25;
	Vector2i mouseClickPosition;

	Event event;
	while (window.pollEvent(event))
	{
		if (event.type == Event::Closed)
		{
			window.close();
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

}

Engine::Engine()
{

}

void Engine::run()
{

}
