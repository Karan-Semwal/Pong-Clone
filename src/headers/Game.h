#pragma once

#include <SFML/Graphics.hpp>

#define BALL_VELOCITY 0.3f
#define BALL_INITIAL_VELOCITY 0.1f

class Game
{
public:
	Game();
	~Game();

	unsigned int getWindowWidth()  const { return m_GameWindow.getSize().x; }
	unsigned int getWindowHeight() const { return m_GameWindow.getSize().y; }

	void run();
	void resetGame();

	bool checkWin();

	// score is updated if the ball hits left or right wall
	void updateScore();

	bool isColliding();
	void onCollision();

	void ballMovement();
	void LeftWallMovement();
	void RightWallMovement();

private:
	void processEvents();
	void update();
	void render();
	void setup();

private:
	sf::RenderWindow   m_GameWindow;      /////////////////////

	sf::RectangleShape m_RightWall;
	sf::RectangleShape m_LeftWall;
	sf::CircleShape    m_ball;

	sf::RectangleShape m_middleLine;

	sf::Vector2f m_ballVelocity;
	sf::Vector2f m_wallVelocity;

	unsigned int m_LeftScore;
	unsigned int m_RightScore;

	sf::Text m_LeftScoreOnWindow;
	sf::Text m_RightScoreOnWindow;

	sf::Font m_scoreFont;
};

