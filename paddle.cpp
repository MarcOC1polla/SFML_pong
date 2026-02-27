#include "paddle.h"

Paddle::Paddle(float startX, float startY)
{
	m_Position.x = startX;
	m_Position.y = startY;

	m_PaddleShape.setSize(sf::Vector2f(20, 130));
	m_PaddleShape.setPosition(m_Position);
}


sf::RectangleShape Paddle::getShape()
{
	return m_PaddleShape;
}

void Paddle::moveUp(sf::Time dt)
{
	m_Position.y -= m_speed * dt.asSeconds();

	m_PaddleShape.setPosition(m_Position);
}

void Paddle::moveDown(sf::Time dt)
{
	m_Position.y += m_speed * dt.asSeconds();

	m_PaddleShape.setPosition(m_Position);
}

sf::FloatRect Paddle::getBounds()
{
	return m_PaddleShape.getGlobalBounds();
}

