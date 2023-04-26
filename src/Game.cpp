#include "./headers/Game.h"
#include <iostream>
#include <math.h>

Game::Game() :
	  m_GameWindow  (sf::VideoMode(WIDTH, HEIGHT), "Pong", sf::Style::Close),
      m_LeftPaddle    (sf::Vector2f (14.0f, 120.0f)),    // left paddle width & height
	  m_RightPaddle   (sf::Vector2f (14.0f, 120.0f)),    // right paddle width & height
	  m_ballVelocity(sf::Vector2f (BALL_INITIAL_VELOCITY_X, BALL_INITIAL_VELOCITY_Y)),
	  m_wallVelocity(sf::Vector2f (WALL_VELOCITY, WALL_VELOCITY)),
      m_gameMenu(sf::Vector2f(WIDTH, HEIGHT)),
	  m_LeftScore (0),      // initial left & right score
      m_RightScore(0)
{
	setup();
}

Game::~Game()
{
}

bool Game::spaceBarPressed()
{
    return sf::Keyboard::isKeyPressed(sf::Keyboard::Space);
}

void Game::renderGameStateBeforePLayingState()
{
    m_GameWindow.draw(m_gameMenu);
    m_GameWindow.display();
}

void Game::run()
{
	m_GameWindow.setFramerateLimit(60);

	while (m_GameWindow.isOpen())
	{
		if (checkWin() == true) 
		{
			resetGame();
			break;
		}
        
        processEvents();
        update();
		render();
	}
}

void Game::resetGame()
{
	m_LeftScore  = 0;
	m_RightScore = 0;

	setup();
}

bool Game::checkWin()
{
	if (m_LeftScore >= 10 || m_RightScore >= 10)
		return true;

	return false;
}

void Game::updateScore()
{
	// ball hits left wall
	if (m_ball.getPosition().x - m_ball.getRadius() < 0)
	{
		m_ball.setPosition((float)getWindowWidth() / 2.f, (float)getWindowHeight() / 2.f);
		m_RightScore++;
		// update score on screen
		m_RightScoreOnWindow.setString(std::to_string(m_RightScore));
		// reset ball speed
		m_ballVelocity = sf::Vector2f(m_LeftScore % 2 == 0 ? BALL_INITIAL_VELOCITY_X : -BALL_INITIAL_VELOCITY_X, BALL_INITIAL_VELOCITY_Y);
	}

	// ball hits right wall
	if (m_ball.getPosition().x + m_ball.getRadius() > (float)getWindowWidth())
	{
		m_ball.setPosition((float)getWindowWidth() / 2.f, (float)getWindowHeight() / 2.f);
		m_LeftScore++;
		// update score on screen
		m_LeftScoreOnWindow.setString(std::to_string(m_LeftScore));
		// reset ball speed
		m_ballVelocity = sf::Vector2f(BALL_INITIAL_VELOCITY_Y, BALL_INITIAL_VELOCITY_Y);
	}

}

void Game::ballMovement()
{
	sf::Vector2f objectPos = m_ball.getPosition();

	if (objectPos.y > getWindowHeight() - m_ball.getRadius() || m_ball.getPosition().y - m_ball.getRadius() < 0)
	{
		m_ballVelocity.y *= -1;
	}

	// ball's continuous movement
	objectPos.x += m_ballVelocity.x;
	objectPos.y += m_ballVelocity.y;

	m_ball.setPosition(objectPos);
}

bool Game::isColliding(sf::RectangleShape object)
{
	if (m_ball.getGlobalBounds().intersects(object.getGlobalBounds()))
		return true;

	return false;
}

void Game::onCollision()
{
	if (isColliding(m_LeftPaddle))
	{
		//increase ball veloctity at first collision
		if (m_ballVelocity.x < 0) {
			m_ballVelocity.x = -BALL_VELOCITY;
		}
		else {
			m_ballVelocity.x = BALL_VELOCITY;
		}

		if (m_ballVelocity.y < 0) {
			m_ballVelocity.y = -BALL_VELOCITY;
		}
		else {
			m_ballVelocity.y = BALL_VELOCITY;
		}

		m_ballVelocity.x *= -1;
	}

	if (isColliding(m_RightPaddle))
	{
		//increase ball veloctity at first collision
		if (m_ballVelocity.x < 0) {
			m_ballVelocity.x = -BALL_VELOCITY;
		}
		else {
			m_ballVelocity.x = BALL_VELOCITY;
		}

		if (m_ballVelocity.y < 0) {
			m_ballVelocity.y = -BALL_VELOCITY;
		}
		else {
			m_ballVelocity.y = BALL_VELOCITY;
		}

		m_ballVelocity.x *= -1;
	}
}

void Game::LeftWallMovement()
{
	sf::Vector2f objectPos = m_LeftPaddle.getPosition();

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) && (m_LeftPaddle.getPosition().y - m_LeftPaddle.getSize().y / 2) > 0 )
	{
		objectPos.y -= m_wallVelocity.y;
		m_LeftPaddle.setPosition(objectPos);
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) && (m_LeftPaddle.getPosition().y + m_LeftPaddle.getSize().y / 2) < getWindowHeight())
	{
		objectPos.y += m_wallVelocity.y;
		m_LeftPaddle.setPosition(objectPos);
	}
}

void Game::RightWallMovement()
{
	sf::Vector2f objectPos = m_RightPaddle.getPosition();

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && (m_RightPaddle.getPosition().y - m_RightPaddle.getSize().y / 2) > 0)
	{
		objectPos.y -= m_wallVelocity.y;
		m_RightPaddle.setPosition(objectPos);
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && (m_RightPaddle.getPosition().y + m_RightPaddle.getSize().y / 2 ) < getWindowHeight())
	{
		objectPos.y += m_wallVelocity.y;
		m_RightPaddle.setPosition(objectPos);
	}
}

void Game::processEvents()
{
	sf::Event event;
	while (m_GameWindow.pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
			m_GameWindow.close();

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
			m_GameWindow.close();
	}
}

void Game::update()
{
	updateScore();
	onCollision();
	ballMovement();
	LeftWallMovement();
	RightWallMovement();
}

void Game::render()
{
	m_GameWindow.clear();

	m_GameWindow.draw(m_middleLine);
	m_GameWindow.draw(m_LeftScoreOnWindow);
	m_GameWindow.draw(m_RightScoreOnWindow);
	m_GameWindow.draw(m_ball);
	m_GameWindow.draw(m_LeftPaddle);
	m_GameWindow.draw(m_RightPaddle);

	m_GameWindow.display();
}

void Game::setup()
{
	/// BALL ///
	m_ball.setRadius(13.f);
	m_ball.setOrigin(m_ball.getRadius(), m_ball.getRadius());
	m_ball.setPosition ((float)getWindowWidth() / 2, (float)getWindowHeight() / 2);
	m_ball.setFillColor(sf::Color::White);

	/// LEFT WALL ///
	m_LeftPaddle.setFillColor(sf::Color::White);
	m_LeftPaddle.setOrigin(m_LeftPaddle.getSize().x / 2.0f, m_LeftPaddle.getSize().y / 2.0f);
	m_LeftPaddle.setPosition(0 + m_LeftPaddle.getSize().x, (float)getWindowHeight() / 2);

	/// RIGHT WALL ///
	m_RightPaddle.setFillColor(sf::Color::White);
	m_RightPaddle.setOrigin(m_RightPaddle.getSize().x / 2.0f, m_RightPaddle.getSize().y / 2.0f);
	m_RightPaddle.setPosition((float)getWindowWidth() - m_RightPaddle.getSize().x, (float)getWindowHeight() / 2);

	/// MIDDLE LINE ///
	sf::Texture middleLineTexture;
	m_middleLine.setSize(sf::Vector2f(10.0f, (float)getWindowHeight()));
	m_middleLine.setPosition((float)getWindowWidth() / 2, 0.0f);

	/// FONT FOR SCORE ///
	if (!m_scoreFont.loadFromFile("./resources/fonts/dogicapixel.ttf"))
		std::cout << "Failed to load score font" << std::endl;

	/// LEFT SCORE TEXT ///
	m_LeftScoreOnWindow.setString("0");
	m_LeftScoreOnWindow.setCharacterSize(30);
	m_LeftScoreOnWindow.setFont(m_scoreFont);
	m_LeftScoreOnWindow.setPosition(m_middleLine.getPosition().x / 2, (float)getWindowHeight() / 12);
	
	/// LEFT SCORE TEXT ///
	m_RightScoreOnWindow.setString("0");
	m_RightScoreOnWindow.setCharacterSize(30);
	m_RightScoreOnWindow.setFont(m_scoreFont);
	m_RightScoreOnWindow.setPosition(m_middleLine.getPosition().x + m_middleLine.getPosition().x / 2, (float)getWindowHeight() / 12);

    // GAME MENU
    m_gameMenuText.loadFromFile("./resources/textures/Pong_game_menu.png");
    m_gameMenu.setTexture(&m_gameMenuText);

}

