#pragma once


#include "SFML/Graphics.hpp"
class Paddle
{
private:
	sf::Vector2f m_Position;
	sf::RectangleShape m_PaddleShape;

	float m_speed = 500.f;

public:

	Paddle(float startX, float startY);
	sf::RectangleShape getShape();
	void moveUp(sf::Time dt);
	void moveDown(sf::Time dt);
	sf::FloatRect getBounds();
};