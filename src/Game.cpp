#include "./headers/Game.h"

Game::Game()
	: m_GameWindow(sf::VideoMode(800, 600), "Pong", sf::Style::Close),
      m_LeftWall (sf::Vector2f(25.0f, 150.0f)),
	  m_RightWall(sf::Vector2f(25.0f, 150.0f)),
	  m_ballVelocity(sf::Vector2f(0.2f, 0.2f)),
	  m_wallVelocity(sf::Vector2f(0.2f, 0.2f))
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
		processEvents();
		update();
		render();
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
	if (isColliding() || isColliding())
	{
		m_ballVelocity.x *= -1;
		m_ball.setPosition(m_ball.getPosition().x + m_ballVelocity.x, m_ball.getPosition().y + m_ballVelocity.y);

		// for objects pause scenerio on collision
		if (isColliding() || isColliding())
		{
			m_ballVelocity.x *= -1;
			m_ballVelocity.y *= -1;

			while (isColliding() || isColliding())
			{
				m_ball.setPosition(m_ball.getPosition().x + m_ballVelocity.x, m_ball.getPosition().y + m_ballVelocity.y);
			}
		}
	}
}

void Game::LeftWallMovement()
{
	sf::Vector2f objectPos = m_LeftWall.getPosition();

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) && m_LeftWall.getPosition().y > 0)
	{
		objectPos.y -= m_wallVelocity.y;
		m_LeftWall.setPosition(objectPos);
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) && m_LeftWall.getPosition().y < getWindowHeight())
	{
		objectPos.y += m_wallVelocity.y;
		m_LeftWall.setPosition(objectPos);
	}
}

void Game::RightWallMovement()
{
	sf::Vector2f objectPos = m_RightWall.getPosition();

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && m_RightWall.getPosition().y > 0)
	{
		objectPos.y -= m_wallVelocity.y;
		m_RightWall.setPosition(objectPos);
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && m_RightWall.getPosition().y < getWindowHeight())
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
	onCollision();
	ballMovement();
	LeftWallMovement();
	RightWallMovement();
}

void Game::render()
{
	m_GameWindow.clear();

	m_GameWindow.draw(m_ball);
	m_GameWindow.draw(m_LeftWall);
	m_GameWindow.draw(m_RightWall);

	m_GameWindow.display();
}

void Game::setup()
{
	/// BALL ///
	m_ball.setRadius(25.f);
	m_ball.setOrigin(25.f, 25.f);
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
}

