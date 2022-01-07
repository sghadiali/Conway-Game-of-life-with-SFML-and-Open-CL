#include "GOL.h"
#include <iostream>
GOL::GOL() :window(sf::VideoMode(width, height), "SFML works!"), Rect(W, std::vector<sf::RectangleShape>(H))
{
	memset(oldVal, false, sizeof(oldVal));
	memset(newVal, false, sizeof(newVal));
	colorMap.insert(std::pair<bool, sf::Color>(false, sf::Color::White));
	colorMap.insert(std::pair<bool, sf::Color>(true, sf::Color::Black));
}

void GOL::run()
{
	initializeRects();
	initialize();
	while (window.isOpen())
	{
		processEvents();
		update();
		render();
	}
}

void GOL::fillColor()
{
	for (int i = 0; i < W; i++)
	{
		for (int j = 0; j < H; j++)
		{
			Rect[i][j].setFillColor(colorMap[newVal[i + W * j]]);
		}
	}
}

void GOL::draw()
{
	for (int i = 0; i < W; i++)
	{
		for (int j = 0; j < H; j++)
		{
			window.draw(Rect[i][j]);
		}
	}
}

void GOL::initializeRects()
{
	for (int i = 0; i < W; i++)
	{
		for (int j = 0; j < H; j++)
		{
			Rect[i][j].setSize(sf::Vector2f(blockSize, blockSize));
			Rect[i][j].setFillColor(sf::Color::Green);
			Rect[i][j].setPosition(sf::Vector2f(10.0f + i * (blockSize + 2.0f), 10.0f + j * (blockSize + 2.0f)));
		}
	}
}

void GOL::processEvents()
{
	sf::Event event;
	while (window.pollEvent(event))
	{
		switch (event.type)
		{
		case sf::Event::Closed:
			window.close();
			break;
		case sf::Event::MouseButtonPressed:
			getMouseInput();			
			break;
		case sf::Event::KeyPressed:
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
			{
				isPaused = !isPaused;
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
			{
				resetRects();
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::R))
			{
				randomizeRects();
			}
			break;
		}
	}
}

void GOL::update()
{
	if (!isPaused)
	{
		calculateGol();
	}
	fillColor();
}

void GOL::render()
{
	window.clear();
	draw();
	window.display();
	memcpy(oldVal, newVal, sizeof(bool) * W * H);
}

void GOL::randomizeRects()
{
	srand(time(NULL));
	for (int i = 0; i < W; i++)
	{
		for (int j = 0; j < H; j++)
		{
			bool r = rand() % 2 == 0;
			newVal[i + W * j] = r;
		}
	}
}


void GOL::resetRects()
{
	for (int i = 0; i < W; i++)
	{
		for (int j = 0; j < H; j++)
		{
			newVal[i + W * j] = false;
		}
	}
}

void GOL::getMouseInput()
{
	for (int i = 0; i < W; i++)
	{
		for (int j = 0; j < H; j++)
		{
			if (Rect[i][j].getGlobalBounds().contains(window.mapPixelToCoords(sf::Mouse::getPosition(window))))
			{
				if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
				{

					newVal[i + W * j] = !newVal[i + W * j];
				}
			}
		}
	}
}
