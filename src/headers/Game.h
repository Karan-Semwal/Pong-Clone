#pragma once

#include <SFML/Graphics.hpp>

class Game
{
public:
	Game();
	~Game();

	unsigned int getWindowWidth()  const { return m_GameWindow.getSize().x; }
	unsigned int getWindowHeight() const { return m_GameWindow.getSize().y; }

	void run();

	void ballMovement();
	bool isColliding();
	void onCollision();
	void LeftWallMovement();
	void RightWallMovement();

private:
	void processEvents();
	void update();
	void render();
	void setup();

private:
	sf::RenderWindow   m_GameWindow;

	sf::RectangleShape m_RightWall;
	sf::RectangleShape m_LeftWall;
	sf::CircleShape    m_ball;

	sf::Vector2f m_ballVelocity;
	sf::Vector2f m_wallVelocity;
};

