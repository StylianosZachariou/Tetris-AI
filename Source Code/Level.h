#pragma once

#include <SFML/Graphics.hpp>
#include "Board.h"

//Level Class Responsible 
class Level {
public:

	Level(sf::RenderWindow* hwnd, int seed);

	//Functions for "Game Loop"
	int handleInput(MoveType move);
	bool update();
	void render();

	Board* getBoard();

	void end();

private:
	// Default functions for rendering to the screen.
	void beginDraw();
	void endDraw();

	// Default variables for level class.
	sf::RenderWindow* window;

	Board* board;
	float dropTimer=0;
};

