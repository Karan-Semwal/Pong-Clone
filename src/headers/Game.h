#pragma once

#include <SFML/Graphics.hpp>

#define WIDTH  850
#define HEIGHT 600

#define BALL_VELOCITY 10.5f
#define WALL_VELOCITY 8.5f

#define BALL_INITIAL_VELOCITY_X 5.f
#define BALL_INITIAL_VELOCITY_Y 3.5f

class Game
{
public:
	Game();
	~Game();

	unsigned int getWindowWidth()  const { return m_GameWindow.getSize().x; }
	unsigned int getWindowHeight() const { return m_GameWindow.getSize().y; }

    bool spaceBarPressed();
    void renderGameStateBeforePLayingState();

	void run();
	void resetGame();

	bool checkWin();

	// score is updated if the ball hits left or right wall
	void updateScore();

	bool isColliding(sf::RectangleShape object);
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
	sf::RenderWindow   m_GameWindow;

    sf::RectangleShape m_gameMenu;
    sf::Texture m_gameMenuText;

	sf::RectangleShape m_RightPaddle;
	sf::RectangleShape m_LeftPaddle;
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

