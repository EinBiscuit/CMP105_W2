#include "Level.h"
#include <math.h>

Level::Level(sf::RenderWindow* hwnd, Input* in)
{
	window = hwnd;
	input = in;

	// initialise game objects
	font.loadFromFile("font/arial.ttf");
	text.setFont(font);
	text.setCharacterSize(12);
	text.setPosition(0, 0);
	text.setFillColor(sf::Color::Red);

	circle.setRadius(15);
	circle.setOrigin(15,15);
	circle.setOutlineColor(sf::Color::Red);

	line.setFillColor(sf::Color::Black);
}

Level::~Level()
{
	input = nullptr;
}

// handle user input
void Level::handleInput()
{		// dispaly to console on button press
	if (input->isKeyDown(sf::Keyboard::W))
	{
		input->setKeyUp(sf::Keyboard::W);
		std::cout << "W was pressed";
	}

	if (input->isKeyDown(sf::Keyboard::J) && input->isKeyDown(sf::Keyboard::K) && input->isKeyDown(sf::Keyboard::L))
	{
		input->setKeyUp(sf::Keyboard::J);
		input->setKeyUp(sf::Keyboard::K);
		input->setKeyUp(sf::Keyboard::L);
		std::cout << "JKL were pressed";
	}

	if (input->isKeyDown(sf::Keyboard::Escape))
	{
		input->setKeyUp(sf::Keyboard::Escape);
		window->close();
	}

	//display to windows on left button draged line;
	if (input->isMouseLDown())
	{
		if(!pressed)
		{
		 start = sf::Vector2i(input->getMouseX(), input->getMouseY());
		 pressed = true;
		}
		finish = sf::Vector2i(input->getMouseX(), input->getMouseY());
	}
	else
	{
		if(pressed)
		{
			finish = sf::Vector2i(input->getMouseX(), input->getMouseY());
			pressed = false;
		}
	}

	// render circle on r mouse click;
	if (input->isMouseRDown())
	{
		circle.setPosition(input->getMouseX(), input->getMouseY());
	}
	
}

// Update game objects
void Level::update()
{
	

	sf::Vector2f magn(finish.x - start.x,finish.y-start.y);

	float magnitude = sqrt(magn.x * magn.x + magn.y * magn.y);

	

	//draw a line on drag

	line.setPosition(start.x,start.y);
	line.setSize(sf::Vector2f(magnitude, 3));
	rotationGrad = acos(magn.x / magnitude) * 180 / 3.14;
	if (start.y < finish.y) line.setRotation(rotationGrad);
	else line.setRotation(-rotationGrad);
	
	
	/*notThickLine[0] = sf::Vertex(start);
	notThickLine[1] = sf::Vertex(finish);*/


	text.setString
	(
		"Mouse:" + std::to_string(input->getMouseX()) + "," + std::to_string(input->getMouseY()) + " Distance: " + std::to_string(magnitude) + "Angle:" + std::to_string(rotationGrad)
	);
}

// Render level
void Level::render()
{
	beginDraw();

	window->draw(text);
	window->draw(circle);

	window->draw(line);
	window->draw(notThickLine, 2, sf::Lines);

	endDraw();
}

// Begins rendering to the back buffer. Background colour set to light blue.
void Level::beginDraw()
{
	window->clear(sf::Color(100, 149, 237));
}

// Ends rendering to the back buffer, and swaps buffer to the screen.
void Level::endDraw()
{
	window->display();
}