#pragma once

#include <SFML/Graphics.hpp>
#include "Framework/Input.h"
#include <string.h>
#include <iostream>


class Level{
public:
	Level(sf::RenderWindow* hwnd, Input* in);
	~Level();

	void handleInput();
	void update();
	void render();

private:
	// Default functions for rendering to the screen.
	void beginDraw();
	void endDraw();

	// Default variables for level class.
	sf::RenderWindow* window;
	Input* input;

	// Add your object here
	sf::Text text;
	sf::Font font;

	bool pressed = false;
	bool held = false;
	
	sf::Vector2i start = { 0,0 };
	sf::Vector2i finish = { 0,0 };
	float rotationGrad = 0;

	sf::CircleShape circle;

	sf::RectangleShape line;

	sf::Vertex notThickLine[2];
};