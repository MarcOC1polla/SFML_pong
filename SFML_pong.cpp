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

    sf::Clock clock;
    sf::Time dt;
	float bounceTimer = 0.1f;
	float hitTimer = 0.1f;

    sf::Font font;

	if (!font.openFromFile("font/PressStart2P-Regular.ttf"))
	{
		std::cerr << "Failed to load font!" << std::endl;
	}

    sf::Text HUDfont(font);
	HUDfont.setCharacterSize(24);
	HUDfont.setFillColor(sf::Color::White);
    HUDfont.setPosition(sf::Vector2f((width / 2 ) - 55, 20));

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

        window.clear();
		ball.Update(dt);
        window.draw(player1.getShape());
        window.draw(player2.getShape());
        window.draw(ball.getShape());
		window.draw(HUDfont);
        window.display();
    }
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
