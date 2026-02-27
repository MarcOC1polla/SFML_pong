#include "ball.h"

Ball::Ball(float startX, float startY)
{
	m_Position.x = startX;
	m_Position.y = startY;

	m_BallShape.setSize(sf::Vector2f(15, 15));
	m_BallShape.setPosition(m_Position);
	m_BallShape.setOrigin(sf::Vector2f(m_BallShape.getSize().x / 2, m_BallShape.getSize().y / 2));
}

sf::RectangleShape Ball::getShape()
{
	return m_BallShape;
}

float Ball::BarrierCollisionY()
{
	return directionY *= -1;
}

void Ball::BarrierCollisionX(float startX, float startY)
{
	m_Position.x = startX;
	m_Position.y = startY;
}

float Ball::PaddleCollision()
{
	return directionX *= -1;
}

sf::FloatRect Ball::getBounds()
{
	return m_BallShape.getGlobalBounds();
}

void Ball::Update(sf::Time dt)
{
	m_Position.x += directionX * m_speed * dt.asSeconds();
	m_Position.y += directionY * m_speed * dt.asSeconds();

	m_BallShape.setPosition(m_Position);
}
