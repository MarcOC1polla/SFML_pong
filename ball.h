#pragma once

#include <SFML/Graphics.hpp>

class Ball
{
private:
	sf::Vector2f m_Position;
	sf::RectangleShape m_BallShape;
	float m_speed = 500.f;
	float directionX = .5f;
	float directionY = .5f;

public:
	Ball(float startX, float startY);
	sf::RectangleShape getShape();
	float BarrierCollisionY();
	void BarrierCollisionX(float startX, float startY);
	float PaddleCollision();
	sf::FloatRect getBounds();
	void Update(sf::Time dt);

};