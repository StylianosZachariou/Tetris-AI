#include "Level.h"

//Constructor
Level::Level(sf::RenderWindow* hwnd,int seed)
{
	//Create a new Board
	board = new Board(seed);
	//Save the window
	window = hwnd;
}

// Handle user input
int Level::handleInput(MoveType move)
{
	//Move the piece depending on the ai's move
	switch (move)
	{
		case MoveType::LEFT:
			board->moveLeft();
			break;

		case MoveType::RIGHT:
			board->moveRight();
			break;

		case MoveType::ROTATE:
			board->rotatePiece();
			break;

		case MoveType::DROP:
			board->dropPiece(true);
			break;

		default:
			break;
	}
	
	return board->getInfo().getTotalLinesCleared();
}

//Update
bool Level::update()
{
	//Update the Board
	return board->update();
}

// Render level
void Level::render()
{
	//Render the board
	beginDraw();
	board->render(window);
	endDraw();
}

//Get the board
Board* Level::getBoard()
{
	return board;
}

//Level End
void Level::end()
{
	//Destruct board
	board->destruct();

	delete board;
	board = NULL;
}

// Begins rendering to the back buffer
void Level::beginDraw()
{
	window->clear(sf::Color::Black);
}

// Ends rendering to the back buffer.
void Level::endDraw()
{
	window->display();
}