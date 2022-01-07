#pragma once
#include <SFML/Graphics.hpp>
#include <vector>


class GOL
{
public:
	GOL();
	void run();
	static const int W = 400;
	static const int H = 225;
	bool oldVal[W * H];
	bool newVal[W * H];

private:	
	void virtual calculateGol() = 0;
	void fillColor();
	void draw();
	void initializeRects();
	virtual void initialize() {};
	void processEvents();
	void update();
	void render();
	void randomizeRects();
	void resetRects();
	void getMouseInput();

	const unsigned int width = 1600;
	const unsigned int height = 900;
	std::vector<std::vector<sf::RectangleShape>> Rect;
	std::vector <sf::Color> colorList = { sf::Color::Black , sf::Color::Blue, sf::Color::Green, sf::Color::Cyan, sf::Color::Red, sf::Color::Yellow, sf::Color::Magenta };
	sf::RenderWindow window;
	std::map<bool, sf::Color> colorMap;
	bool isPaused = false;
	float blockSize = ((float)height / H) - 2.0f;
};