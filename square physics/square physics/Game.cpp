#include "Game.h"
#include <iostream>
#include <SFML/Graphics.hpp>

// Updates per milliseconds
static double const MS_PER_UPDATE = 10.0;

////////////////////////////////////////////////////////////
Game::Game()
	: m_window(sf::VideoMode(800, 800, 32), "physics!", sf::Style::Default)
{
	Square.setSize(sf::Vector2f(10, 10));
	Square.setPosition(sf::Vector2f(400, 645));
	Square.setOrigin(5, 5);

	Ground.setSize(sf::Vector2f(800, 150));
	Ground.setPosition(sf::Vector2f(0,650));
	Ground.setFillColor(sf::Color::Green);

	gravity = 5.0f * gravity;

	if (Font.loadFromFile("ariblk.ttf"))
	{
		timerText.setFont(Font);
	}

	timerText.setCharacterSize(15);
	timerText.setPosition(10, 20);
	timerText.setFillColor(sf::Color::White);
}

void Game::Normalise()
{
	normVel.x = Velocity.x / sqrt(Velocity.x * Velocity.x + Velocity.y * Velocity.y);
	normVel.y = Velocity.y / sqrt(Velocity.x * Velocity.x + Velocity.y * Velocity.y);
}

sf::Vector2f Game::multiply(sf::Vector2f t_vector1, sf::Vector2f t_vector2)
{
	sf::Vector2f temp = sf::Vector2f(t_vector1.x * t_vector2.x, t_vector1.y * t_vector2.y);

	return temp;
}

////////////////////////////////////////////////////////////
void Game::run()
{
	sf::Clock clock;
	sf::Int32 lag = 0;

	while (m_window.isOpen())
	{
		sf::Time dt = clock.restart();

		lag += dt.asMilliseconds();

		processEvents();

		while (lag > MS_PER_UPDATE)
		{
			update(MS_PER_UPDATE);
			lag -= MS_PER_UPDATE;
		}
		update(MS_PER_UPDATE);

		render();
	}
}

////////////////////////////////////////////////////////////
void Game::processEvents()
{
	sf::Event event;
	while (m_window.pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
		{
			m_window.close();
		}
		processGameEvents(event);
	}
}

////////////////////////////////////////////////////////////
void Game::processGameEvents(sf::Event& event)
{
	// check if the event is a a mouse button release
	if (sf::Event::KeyPressed == event.type)
	{
		switch (event.key.code)
		{
		case sf::Keyboard::Escape:
			m_window.close();
			break;
		case sf::Keyboard::W:
			Velocity = sf::Vector2f(0, 150);
			timer = 0;
			break;
		case sf::Keyboard::D:
			Velocity = sf::Vector2f(150, 0);
			timer = 0;
			break;
		case sf::Keyboard::A:
			Velocity = sf::Vector2f(-150, 0);
			timer = 0;
			break;
		case sf::Keyboard::S:
			Square.setPosition(400, 645);
			Velocity = sf::Vector2f(0, 0);
			timer = 0;
			break;
		default:
			break;
		}
	}
}


////////////////////////////////////////////////////////////
void Game::update(double dt)
{
	time =dt/10000;

	if (Square.getGlobalBounds().intersects(Ground.getGlobalBounds()) == false)
	{
		Square.setPosition(Square.getPosition() + (Velocity * time) + (0.5f * gravity * (time * time)));
		Velocity = Velocity + (gravity * time);
	}
	else
	{
		Velocity.y = -(restitiution * Velocity.y);
		Normalise();
		Acceleration = -restitiution * gravity.y * normVel;

		Square.setPosition(Square.getPosition() + (Velocity* time) + (0.5f * Acceleration * (time * time)));
		Velocity = Velocity + (Acceleration * time);
	}

	if (Square.getPosition().x > 800 || Square.getPosition().x < 0)
	{
		Velocity = -1.0f * Velocity ;
	}
	
	if (Velocity.x > 0.1 ||  Velocity.x < -0.1 ) 
	{
		timer += time;
	}

	timerText.setString("Time = " + (std::to_string(timer)));
}

////////////////////////////////////////////////////////////
void Game::render()
{
	
	m_window.clear(sf::Color(0, 0, 0, 0));

	
	m_window.draw(Ground);
	m_window.draw(Square);
	m_window.draw(timerText);

	m_window.display();
}





