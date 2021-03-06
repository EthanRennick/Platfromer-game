// platform game.....
//

#include "stdafx.h"

#ifdef _DEBUG 
#pragma comment(lib,"sfml-graphics-d.lib") 
#pragma comment(lib,"sfml-audio-d.lib") 
#pragma comment(lib,"sfml-system-d.lib") 
#pragma comment(lib,"sfml-window-d.lib") 
#pragma comment(lib,"sfml-network-d.lib") 
#else 
#pragma comment(lib,"sfml-graphics.lib") 
#pragma comment(lib,"sfml-audio.lib") 
#pragma comment(lib,"sfml-system.lib") 
#pragma comment(lib,"sfml-window.lib") 
#pragma comment(lib,"sfml-network.lib") 
#endif 

#include <SFML/Graphics.hpp>
#include <iostream>
#include <stdlib.h> 
#include <time.h> 

int main()
{



	//create Window
	sf::RenderWindow window(sf::VideoMode(800, 600), "platform game");
	//do this once to "seed" the random number generator
	srand(time(NULL));
	sf::View view = window.getDefaultView();
	float randomNum;

	sf::Sprite background;
	sf::Texture backgroundTexture;
	if (!backgroundTexture.loadFromFile("png-platform.png"));
	{
		// error...
	}
	background.setTexture(backgroundTexture);
	background.setPosition(200,300);

	sf::Sprite deathSprite;
	sf::Texture spriteTexture;
	if (!spriteTexture.loadFromFile("gameover.png"));
	{
		// error...
	}
	deathSprite.setTexture(spriteTexture);
	deathSprite.setPosition(100, 100);

	sf::RectangleShape playerShape;
	int overAllCounter = 1000;

	sf::CircleShape enemyBasic;
	enemyBasic.setRadius(15);
	enemyBasic.setPosition(400, 400);
	enemyBasic.setFillColor(sf::Color::Yellow);

	playerShape.setSize(sf::Vector2f(10, 10));
	playerShape.setPosition(160, -20);
	float velocityX = 0, velocityY = 0, gravity = 0.3;

	int  health = 3;
	int score = 0;
	int messages = 0;

	//ttext stuff
	sf::Font font;
	if (!font.loadFromFile("arial.ttf"))
	{
		// error...
	}

	sf::Text healthText;
	healthText.setFont(font);
	healthText.setPosition(0, 26);
	healthText.setString("Health: " + std::to_string(health));
	healthText.setCharacterSize(24);
	healthText.setFillColor(sf::Color::White);

	sf::Text scoreText;
	scoreText.setFont(font);
	scoreText.setString("Score: " + std::to_string(score));
	scoreText.setCharacterSize(24);
	scoreText.setFillColor(sf::Color::White);

	sf::Text messagesText;
	messagesText.setFont(font);
	messagesText.setString(" Press Enter to play ");
	messagesText.setCharacterSize(40);
	messagesText.setFillColor(sf::Color::Green);
	messagesText.setPosition(220, 250);

	bool menu = true;
	bool death = false;

	float whiteCountDown = 30.0f;

	bool rotatingView = false;
	randomNum = rand() % 750 + 0;
	const int numRows = 15;
	const int numCols = 20;
	int levelData[numRows][numCols] = {
		{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
	{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,3,0,0,0,0,0 },
	{ 0,0,0,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
	{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
	{ 0,0,0,0,3,0,0,0,1,0,0,0,0,1,2,0,0,0,0,0 },
	{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,0 },
	{ 0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0 },
	{ 0,0,0,0,0,0,0,1,1,2,1,0,0,0,0,0,0,0,0,0 },
	{ 0,0,3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
	{ 0,0,0,0,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0 },
	{ 0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,2,0,0 },
	{ 0,0,0,1,1,1,0,0,0,0,0,0,0,1,0,0,0,0,0,0 },
	{ 0,0,0,0,0,0,0,1,1,1,1,2,0,1,0,0,0,0,0,0 },
	{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
	{ 0,0,1,1,1,1,1,0,0,0,0,3,3,3,0,0,0,0,0,0 } };

	sf::RectangleShape level[numRows][numCols];

	for (int row = 0; row < numRows; row++)
	{
		for (int col = 0; col < numCols; col++)
		{
			std::cout << levelData[row][col];
			level[row][col].setSize(sf::Vector2f(40, 10));
			level[row][col].setPosition(col * 40, row * 40);
			if (levelData[row][col] == 1)
			{
				level[row][col].setFillColor(sf::Color::Red);
			}
			if (levelData[row][col] == 0)
			{
				level[row][col].setFillColor(sf::Color::Black);
			}
			if (levelData[row][col] == 2)
			{
				level[row][col].setFillColor(sf::Color::Blue);
			}
			if (levelData[row][col] == 3)
			{
				level[row][col].setFillColor(sf::Color::White);
			}

		}
		std::cout << std::endl;
	}


	// set timePerFrame to 1 60th of a second. 60 frames per second

	sf::Time timePerFrame = sf::seconds(1.0f / 60.0f);


	sf::Time timeSinceLastUpdate = sf::Time::Zero;

	// the clock object keeps the time.
	sf::Clock clock;

	clock.restart();

	while (window.isOpen())
	{
		// check if the close window button is clicked on.
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		//add to the time since last update and restart the clock
		timeSinceLastUpdate += clock.restart();

		//update every 60th of a second
		//only when the time since last update is greater than 1/60 update the world.

		if (timeSinceLastUpdate > timePerFrame)
		{
			if (menu == true)
			{

				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter))
				{
					menu = false;
				}
			}
			if (menu == false)
			{
				// get keyboard input.

			

				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
				{
					playerShape.move(-4, 0);
					if (playerShape.getPosition().x < 0)
					{
						playerShape.setPosition(790, playerShape.getPosition().y);
					}

				}
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
				{
					playerShape.move(4, 0);
					if (playerShape.getPosition().x > 800)
					{
						playerShape.setPosition(0, playerShape.getPosition().y);
					}
				}
				if (playerShape.getPosition().y > 600)
				{
					playerShape.setPosition(playerShape.getPosition().x, 0);
					health--;
				}
				if (playerShape.getGlobalBounds().intersects(enemyBasic.getGlobalBounds()))
				{
					score++;
					overAllCounter += 360;
					enemyBasic.setPosition(rand() % 750 + 10, rand() % 400 + 20);
				}
				else
				{
					overAllCounter--;
				}

				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && velocityY == 0)
				{
					velocityY = -10;
				}

				velocityY = velocityY + gravity;
				playerShape.move(0, velocityY);
				gravity = 0.3;
				if (overAllCounter == 0 || health == 0)
				{
					death = true;

				}

				if (death == true)
				{
					if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter))
					{

						menu = true;
						death = false;
						overAllCounter = 1000;
						health = 3;
						score = 0;
						playerShape.setPosition(100, 100);
					}
				}
				if (velocityY >= 0)
				{
					for (int row = 0; row < numRows; row++)
					{
						for (int col = 0; col < numCols; col++)
						{
							if (levelData[row][col] == 1)
							{
								if (playerShape.getGlobalBounds().intersects(level[row][col].getGlobalBounds()))
								{
									gravity = 0;
									velocityY = 0;
									playerShape.setPosition(playerShape.getPosition().x, level[row][col].getPosition().y);
									playerShape.move(0, -playerShape.getGlobalBounds().height);
									break;
								}
							}
							if (levelData[row][col] == 2)
							{
								if (playerShape.getGlobalBounds().intersects(level[row][col].getGlobalBounds()))
								{
									gravity = .0;
									velocityY = 0.1;
									playerShape.setPosition(playerShape.getPosition().x, level[row][col].getPosition().y);
									playerShape.move(0, -playerShape.getGlobalBounds().height);
									break;
								}
							}
							if (levelData[row][col] == 3)
							{
								if (playerShape.getGlobalBounds().intersects(level[row][col].getGlobalBounds()))
								{
									gravity = .0;
									velocityY = 0.0;
									playerShape.setPosition(playerShape.getPosition().x, level[row][col].getPosition().y);
									playerShape.move(0, -playerShape.getGlobalBounds().height);
									whiteCountDown--;
									if (whiteCountDown == 0)
									{
										levelData[row][col] = 0;
										if (levelData[row][col] == 0)
										{
											level[row][col].setFillColor(sf::Color::Black);
										}
										if (levelData[row][col] == 3)
										{
											level[row][col].setFillColor(sf::Color::White);
										}
										levelData[row + 1][col] = 3;
										whiteCountDown = 30;
									}
									break;
								}
							}
						}
					}
				}
			}
			else
			{

			}

			//clear the screen and draw the shapes.
			window.clear();

			scoreText.setString("Score: " + std::to_string(score));
			healthText.setString("Health: " + std::to_string(health));
			messagesText.setString("Press Enter to play! ");
			
			if (death == false)
			{
				for (int row = 0; row < numRows; row++)
				{
					for (int col = 0; col < numCols; col++)
					{
						if (levelData[row][col] == 0)
						{
							level[row][col].setFillColor(sf::Color::Black);
						}
						if (levelData[row][col] == 3)
						{
							level[row][col].setFillColor(sf::Color::White);
						}
						window.draw(level[row][col]);

					}
				}

				window.draw(playerShape);
				if (menu == true)
				{
					window.clear(sf::Color::Black);
					window.draw(background);
					window.draw(messagesText);
				}
				if (menu == false)
				{
					window.draw(scoreText);
					window.draw(healthText);
					window.draw(enemyBasic);
					messagesText.setCharacterSize(14);
					messagesText.setPosition(10, 520);
					messagesText.setString("White platforms will slowly fall if you stand on them. \nBlue platforms are sticky, so you cannot jump on them. ");
					window.draw(messagesText);

					messagesText.setCharacterSize(20);
					messagesText.setPosition(500, 0);
					messagesText.setString("You are on a timer... " + std::to_string(overAllCounter));
					window.draw(messagesText);

				}
			}
			else
			{
				messagesText.setCharacterSize(40);
				messagesText.setFillColor(sf::Color::Green);
				messagesText.setPosition(220, 250);
				messagesText.setString(" The enemy have won, \n   and you are dead. \n \n   Enter to play again ");
				window.draw(messagesText);
				window.draw(deathSprite);
			}
			//tell SFML  to display everything 
			window.display();

			// reset the timeSinceLastUpdate to 0 
			timeSinceLastUpdate = sf::Time::Zero;
		}
	}

	return 0;
}
