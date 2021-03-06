#pragma once

#include <SFML/Graphics.hpp>


class Game
{
public:
	/// <summary>
	/// @brief Default constructor that initialises the SFML window, 
	///   and sets vertical sync enabled. 
	/// </summary>
	Game();
	void Normalise();

	sf::Vector2f multiply(sf::Vector2f t_vector1 , sf::Vector2f t_vector2);

	sf::RectangleShape Square;
	sf::RectangleShape Ground;

	 sf::Vector2f gravity{ 0.0f, 9.81f };

	sf::Vector2f Velocity{ 0.0,0.0 };

	float time = (1.0f / 60.0f);

	float timer = 0;

	float restitiution = 0.8;

	sf::Vector2f Acceleration{ 0.0,0.0 };

	sf::Vector2f normVel{ 0.0f,0.0f };

	sf::Text timerText;

	sf::Font Font;

	/// <summary>
	/// @brief the main game loop.
	/// 
	/// A complete loop involves processing SFML events, updating and drawing all game objects.
	/// The actual elapsed time for a single game loop results (lag) is stored. If this value is 
	///  greater than the notional time for one loop (MS_PER_UPDATE), then additional updates will be 
	///  performed until the lag is less than the notional time for one loop.
	/// The target is one update and one render cycle per game loop, but slower PCs may 
	///  perform more update than render operations in one loop.
	/// </summary>
	void run();

protected:
	/// <summary>
	/// @brief Placeholder to perform updates to all game objects.
	/// </summary>
	/// <param name="time">update delta time</param>
	void update(double dt);

	/// <summary>
	/// @brief Draws the background and foreground game objects in the SFML window.
	/// The render window is always cleared to black before anything is drawn.
	/// </summary>
	void render();

	/// <summary>
	/// @brief Checks for events.
	/// Allows window to function and exit. 
	/// Events are passed on to the Game::processGameEvents() method.
	/// </summary>	
	void processEvents();

	/// <summary>
	/// @brief Handles all user input.
	/// </summary>
	/// <param name="event">system event</param>
	void processGameEvents(sf::Event&);

	// main window
	sf::RenderWindow m_window;
};
