// SFML_pong.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>

#include <SFML/Graphics.hpp>

#include "paddle.h"
#include "ball.h"


int main()
{
    uint32_t width = 1200.f;
    uint32_t height = 800.f;

    sf::RenderWindow window(sf::VideoMode({ width, height }), "Pong!");

    Paddle player1(30,300);
    Paddle player2(width - 50, 300);
    Ball ball(width / 2, height / 2);

//define clock and delta time
    sf::Clock clock;
    sf::Time dt;
//create timers so the ball cant bounce through barriers
	float bounceTimer = 0.1f;
	float hitTimer = 0.1f;

    sf::Font font;

//load font
	if (!font.openFromFile("font/PressStart2P-Regular.ttf"))
	{
		std::cerr << "Failed to load font!" << std::endl;
	}

//set font
    sf::Text HUDfont(font);
	HUDfont.setCharacterSize(24);
	HUDfont.setFillColor(sf::Color::White);
    HUDfont.setPosition(sf::Vector2f((width / 2 ) - 55, 20));

//player scores
	int player1Score = 0;
	int player2Score = 0;
	std::stringstream ss;
	ss << player1Score << " : " << player2Score;

	HUDfont.setString(ss.str());

    while (window.isOpen())
    {
        while (const std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
                window.close();
        }

        // delta time
        dt = clock.restart();
		bounceTimer -= dt.asSeconds();
		hitTimer -= dt.asSeconds();

        //player 1 movement
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W) && player1.getBounds().position.y >= 0)
        {
            player1.moveUp(dt);
        }


        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S) && player1.getBounds().position.y <= height - 130)
        {
            player1.moveDown(dt);
        }

        //player 2 movement
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::O) && player2.getBounds().position.y >= 0)
        {
            player2.moveUp(dt);
        }


        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::L) && player2.getBounds().position.y <= height - 130)
        {
            player2.moveDown(dt);
        }

        //ball logic

		//ceiling and wall collision
        if(ball.getBounds().position.y < 0 || ball.getBounds().position.y > height)
        {
            if (bounceTimer < 0)
            {
                ball.BarrierCollisionY();
                bounceTimer = 0.1f;

            }
		}

		//paddle collision
        if (ball.getBounds().findIntersection(player1.getBounds()) || ball.getBounds().findIntersection(player2.getBounds()))
        {
            if (hitTimer < 0)
            {
                ball.PaddleCollision();
                hitTimer = 0.1f;
            }
        }

		//point scored

        if (ball.getBounds().position.x < 0)
        {
            ball.BarrierCollisionX(width / 2, height / 2);
			player2Score ++;
			ss.str("");
			ss << player1Score << " : " << player2Score;
			HUDfont.setString(ss.str());
        }

        if (ball.getBounds().position.x > width)
        {
            ball.BarrierCollisionX(width / 2, height / 2);
            player1Score++;
            ss.str("");
            ss << player1Score << " : " << player2Score;
            HUDfont.setString(ss.str());
        }

//clear the window, draw objects
        window.clear();
		ball.Update(dt);
        window.draw(player1.getShape());
        window.draw(player2.getShape());
        window.draw(ball.getShape());
		window.draw(HUDfont);
        window.display();
    }
}

