#pragma once
#include <vector>
#include "Piece.h"
#include "LevelInfo.h"
#include "AiMove.h"

//Tetris Game Board
class Board
{
public:
	//Constructor
	Board(int seed);

	//Update Board
	bool update();

	//Render Board
	void render(sf::RenderWindow* window);

	//Spawn new piece
	void spawn();

	//Rotate current piece
	void rotatePiece();

	//Drop current piece
	bool dropPiece(bool fast);

	//Complete Drop current piece
	void completeDrop();

	//Move current piece to the left 
	bool moveLeft();

	//Move current piece to the right
	bool moveRight();

	//Get all possible ending positions for ai move
	std::vector<Move*> allPossiblePositions();

	//Getters
	int getScore();
	LevelInfo getInfo();
	bool getChangedPiece();

	//Setters
	void setChangedPiece(bool state);

	//Game End
	void destruct();

private:
	//Update board visual
	void updateVisual();

	//Check how many lines are cleared
	int checkClearLine();

	//Clear Lines
	void clearLine(int line);

	//Calculate Score with lines cleared
	int calculateScore(int linesCleared);

	//Check Fail State
	bool checkFail();

	//Score
	int score=0;
	//Signal when their is a new current Piece
	bool changePiece = true;

	//Level Info
	LevelInfo info;
	//Frame Drop Counter
	int frameDropCounter;
	//Current Control Piece
	Piece* currentControlledPiece;
	//Next Piece
	Piece* nextPiece;
	//The Board
	std::vector<std::vector<int>> board_visual;

	//Text
	sf::Font font;
	sf::Text game;
	sf::Text stats;
	sf::Text scoreDisplay;
	sf::Text levelDisplay;
	sf::Text nextPieceTxt;
};

