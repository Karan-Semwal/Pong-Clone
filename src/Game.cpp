#include "./headers/Game.h"
#include <iostream>


Game::Game() :
	  m_GameWindow  (sf::VideoMode(800, 600), "Pong", sf::Style::Close),
      m_LeftWall    (sf::Vector2f (20.0f, 140.0f)),
	  m_RightWall   (sf::Vector2f (20.0f, 140.0f)),
	  m_ballVelocity(sf::Vector2f (BALL_INITIAL_VELOCITY, BALL_INITIAL_VELOCITY)),
	  m_wallVelocity(sf::Vector2f (0.18f, 0.18f)),
	  m_LeftScore (0),
      m_RightScore(0)
{
	setup();
}

Game::~Game()
{
}

void Game::run()
{
	while (m_GameWindow.isOpen())
	{
		if (checkWin()) 
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
	m_ballVelocity = sf::Vector2f(0.1f, 0.1f);
	m_wallVelocity = sf::Vector2f(0.1f, 0.1f);
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
		m_ballVelocity = sf::Vector2f(BALL_INITIAL_VELOCITY, BALL_INITIAL_VELOCITY);
	}

	// ball hits right wall
	if (m_ball.getPosition().x + m_ball.getRadius() > (float)getWindowWidth())
	{
		m_ball.setPosition((float)getWindowWidth() / 2.f, (float)getWindowHeight() / 2.f);
		m_LeftScore++;
		// update score on screen
		m_LeftScoreOnWindow.setString(std::to_string(m_LeftScore));
		// reset ball speed
		m_ballVelocity = sf::Vector2f(BALL_INITIAL_VELOCITY, BALL_INITIAL_VELOCITY);
	}

}

void Game::ballMovement()
{
	sf::Vector2f objectPos = m_ball.getPosition();

	if (m_ball.getPosition().y > getWindowHeight() || m_ball.getPosition().y < 0)
	{
		m_ballVelocity.y *= -1;
	}

	objectPos.x += m_ballVelocity.x;
	objectPos.y += m_ballVelocity.y;

	m_ball.setPosition(objectPos);
}

bool Game::isColliding()
{
	if (m_ball.getGlobalBounds().intersects(m_LeftWall.getGlobalBounds()))
		return true;

	if (m_ball.getGlobalBounds().intersects(m_RightWall.getGlobalBounds()))
		return true;

	return false;
}

void Game::onCollision()
{
	if (isColliding())
	{
		if (m_ballVelocity.x < 0) {
			m_ballVelocity.x = -BALL_VELOCITY;
		}
		m_ballVelocity.x = BALL_VELOCITY;

		if (m_ballVelocity.y < 0) {
			m_ballVelocity.y = -BALL_VELOCITY;
		}
		m_ballVelocity.y = BALL_VELOCITY;

		m_ballVelocity.x *= -1;
		m_ball.setPosition(m_ball.getPosition().x + m_ballVelocity.x, m_ball.getPosition().y + m_ballVelocity.y);

		// for objects pause scenerio on collision
		if (isColliding())
		{
			m_ballVelocity.x *= -1;
			m_ballVelocity.y *= -1;

			while (isColliding())
			{
				m_ball.setPosition(m_ball.getPosition().x + m_ballVelocity.x, m_ball.getPosition().y + m_ballVelocity.y);
			}
		}
	}
}

void Game::LeftWallMovement()
{
	sf::Vector2f objectPos = m_LeftWall.getPosition();

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) && (m_LeftWall.getPosition().y - m_LeftWall.getSize().y / 2) > 0 )
	{
		objectPos.y -= m_wallVelocity.y;
		m_LeftWall.setPosition(objectPos);
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) && (m_LeftWall.getPosition().y + m_LeftWall.getSize().y / 2) < getWindowHeight())
	{
		objectPos.y += m_wallVelocity.y;
		m_LeftWall.setPosition(objectPos);
	}
}

void Game::RightWallMovement()
{
	sf::Vector2f objectPos = m_RightWall.getPosition();

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && (m_RightWall.getPosition().y - m_RightWall.getSize().y / 2) > 0)
	{
		objectPos.y -= m_wallVelocity.y;
		m_RightWall.setPosition(objectPos);
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && (m_RightWall.getPosition().y + m_RightWall.getSize().y / 2 ) < getWindowHeight())
	{
		objectPos.y += m_wallVelocity.y;
		m_RightWall.setPosition(objectPos);
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
	m_GameWindow.draw(m_LeftWall);
	m_GameWindow.draw(m_RightWall);

	m_GameWindow.display();
}

void Game::setup()
{
	/// BALL ///
	m_ball.setRadius(15.f);
	m_ball.setOrigin(m_ball.getRadius(), m_ball.getRadius());
	m_ball.setPosition ((float)getWindowWidth() / 2, (float)getWindowHeight() / 2);
	m_ball.setFillColor(sf::Color::White);

	/// LEFT WALL ///
	m_LeftWall.setFillColor(sf::Color::White);
	m_LeftWall.setOrigin(m_LeftWall.getSize().x / 2.0f, m_LeftWall.getSize().y / 2.0f);
	m_LeftWall.setPosition(0 + m_LeftWall.getSize().x, (float)getWindowHeight() / 2);

	/// RIGHT WALL ///
	m_RightWall.setFillColor(sf::Color::White);
	m_RightWall.setOrigin(m_RightWall.getSize().x / 2.0f, m_RightWall.getSize().y / 2.0f);
	m_RightWall.setPosition((float)getWindowWidth() - m_RightWall.getSize().x, (float)getWindowHeight() / 2);

	/// MIDDLE LINE ///
	sf::Texture middleLineTexture;
	m_middleLine.setSize(sf::Vector2f(10.0f, (float)getWindowHeight()));
	m_middleLine.setPosition((float)getWindowWidth() / 2, 0.0f);
	m_middleLine.setTexture(&middleLineTexture);

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


}

