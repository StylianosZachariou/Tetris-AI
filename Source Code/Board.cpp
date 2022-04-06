#include "Board.h"
#include <stdlib.h>
#include <time.h>
#include <Windows.h>

//Constructor
Board::Board(int seed)
{
	//Set random seed
	srand(seed);

	//Initialize Board
	board_visual =
	{
		{0,0,11,0,0,0,0,0,0,0,0,0,0,11,0,0},
		{0,0,11,0,0,0,0,0,0,0,0,0,0,11,0,0},
		{0,0,11,0,0,0,0,0,0,0,0,0,0,11,0,0},
		{0,0,11,0,0,0,0,0,0,0,0,0,0,11,0,0},
		{0,0,11,0,0,0,0,0,0,0,0,0,0,11,0,0},
		{0,0,11,0,0,0,0,0,0,0,0,0,0,11,0,0},
		{0,0,11,0,0,0,0,0,0,0,0,0,0,11,0,0},
		{0,0,11,0,0,0,0,0,0,0,0,0,0,11,0,0},
		{0,0,11,0,0,0,0,0,0,0,0,0,0,11,0,0},
		{0,0,11,0,0,0,0,0,0,0,0,0,0,11,0,0},
		{0,0,11,0,0,0,0,0,0,0,0,0,0,11,0,0},
		{0,0,11,0,0,0,0,0,0,0,0,0,0,11,0,0},
		{0,0,11,0,0,0,0,0,0,0,0,0,0,11,0,0},
		{0,0,11,0,0,0,0,0,0,0,0,0,0,11,0,0},
		{0,0,11,0,0,0,0,0,0,0,0,0,0,11,0,0},
		{0,0,11,0,0,0,0,0,0,0,0,0,0,11,0,0},
		{0,0,11,0,0,0,0,0,0,0,0,0,0,11,0,0},
		{0,0,11,0,0,0,0,0,0,0,0,0,0,11,0,0},
		{0,0,11,0,0,0,0,0,0,0,0,0,0,11,0,0},
		{0,0,11,0,0,0,0,0,0,0,0,0,0,11,0,0},
		{0,0,11,11,11,11,11,11,11,11,11,11,11,11,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}
	};

	//Create new current piece
	currentControlledPiece = new Piece(Type(rand() % 7));
	//Create new next piece
	nextPiece = new Piece(Type(rand() % 7));
	//Set the current control piece's position
	currentControlledPiece->position = { 6,1 };

	//Set Text
	game.setString("Tetris");
	game.setFillColor(sf::Color::White);
	game.setCharacterSize(75);
	game.setPosition(0, 0);
	stats.setFillColor(sf::Color::White);
	stats.setCharacterSize(50);
	scoreDisplay.setFillColor(sf::Color::White);
	scoreDisplay.setCharacterSize(50);
	levelDisplay.setFillColor(sf::Color::White);
	levelDisplay.setCharacterSize(50);
	nextPieceTxt.setFillColor(sf::Color::White);
	nextPieceTxt.setCharacterSize(50);
	nextPieceTxt.setString("Next:");
	sf::Vector2f textPosition;
	textPosition.x = (board_visual.size()/2 + 2)* 30;
	textPosition.y = 0;
	game.setPosition(textPosition);
	textPosition.y += 100;
	nextPieceTxt.setPosition(textPosition);
	textPosition.y += 300;
	stats.setPosition(textPosition);
	textPosition.x += 300;
	scoreDisplay.setPosition(textPosition);
	textPosition.y += 45;
	levelDisplay.setPosition(textPosition);
}

//Spawn New Piece
void Board::spawn()
{
	delete currentControlledPiece;
	//The Current Controlled Piece becomes the next piece
	currentControlledPiece = nextPiece;
	//Create a new next piece
	nextPiece = new Piece(Type(rand() % 7));

	//Set Current piece's position
	currentControlledPiece->position = { 6,1 };

}

//Rotate Piece
void Board::rotatePiece()
{
	//New Block Positions after rotation
	std::vector<sf::Vector2f> newBlockPositions = currentControlledPiece->checkRotatePositions();

	//Iterate through all block positions
	bool collision = false;
	for (int j = 0; j < newBlockPositions.size(); j++)
	{
		//If their is a collision between another block
		sf::Vector2f positions = {newBlockPositions[j].x+currentControlledPiece->position.x ,newBlockPositions[j].y + currentControlledPiece->position.y };
		if (board_visual[positions.y][positions.x] >10)
		{
			collision = true;
		}
	}		

	//If there are no collisions, rotate the piece
	if (!collision)
	{
		currentControlledPiece->rotate();
	}
	

}

//Drop Piece
bool Board::dropPiece(bool fast)
{
	//If fast drop or the frame counter has run out of time
	if ((fast && frameDropCounter >= 1) || (!fast && frameDropCounter >= info.getSpeed()))
	{
		//Variable showing if the piece can drop further
		bool canDrop = true;

		//Iterate through all block Positions
		for (int i = 0; i < currentControlledPiece->blockPositions.size(); i++)
		{
			//The next position for this block
			sf::Vector2f nextBlockPos;
			nextBlockPos.y = currentControlledPiece->blockPositions[i].y + currentControlledPiece->position.y + 1;
			nextBlockPos.x = currentControlledPiece->blockPositions[i].x + currentControlledPiece->position.x;
			//The value of that position
			int nextValue = board_visual[nextBlockPos.y][nextBlockPos.x];

			//If this is not the edge of the piece
			if (currentControlledPiece->blockPositions[i].y + 1 < currentControlledPiece->getSize())
			{
				//Check for blank spots in the shape
				if (nextValue > 0 && currentControlledPiece->getShape()[currentControlledPiece->blockPositions[i].y + 1][currentControlledPiece->blockPositions[i].x] == 0)
				{
					//Cant drop
					canDrop = false;

				}
			}
			else
			{
				//If next value is another block
				if (nextValue > 10)
				{
					canDrop = false;
				}
			}
		}

		//If piece can drop
		if (canDrop)
		{
			//move it down
			currentControlledPiece->position.y++;
		}
		else
		{
			//Freeze the piece in place
			for (int y = 0; y < currentControlledPiece->getSize(); y++)
			{
				for (int x = 0; x < currentControlledPiece->getSize(); x++)
				{
					if (currentControlledPiece->getShape()[y][x] > 0)
					{
						board_visual[currentControlledPiece->position.y + y][currentControlledPiece->position.x + x] = currentControlledPiece->getShape()[y][x] + 10;
					}
				}
			}
			//Spawn a new piece
			spawn();
			//Toggle change piece
			changePiece = true;					

		}
		//Reset frame Drop Counter
		frameDropCounter = 0;

		//Update Info
		int linesCleared = checkClearLine();
		score += calculateScore(linesCleared);
		info.incrementClearedLines(linesCleared);

		
	}
	
	//Check for a fail
	if (checkFail())
	{
	
		return false;
	}
	return true;
}

//Complete Drop the piece
void Board::completeDrop()
{
	bool canDrop = true;

	//While the piece can be dropped
	while (canDrop)
	{
		//Iterate through all block Positions
		for (int i = 0; i < currentControlledPiece->blockPositions.size(); i++)
		{
			//The next position for this block
			sf::Vector2f nextBlockPos;
			nextBlockPos.y = currentControlledPiece->blockPositions[i].y + currentControlledPiece->position.y + 1;
			nextBlockPos.x = currentControlledPiece->blockPositions[i].x + currentControlledPiece->position.x;
			//The value of that position
			int nextValue = board_visual[nextBlockPos.y][nextBlockPos.x];

			//If this is not the edge of the piece
			if (currentControlledPiece->blockPositions[i].y + 1 < currentControlledPiece->getSize())
			{
				//Check for blank spots in the shape
				if (nextValue > 0 && currentControlledPiece->getShape()[currentControlledPiece->blockPositions[i].y + 1][currentControlledPiece->blockPositions[i].x] == 0)
				{
					//Cant drop
					canDrop = false;

				}
			}
			else
			{
				//If next value is another block
				if (nextValue > 10)
				{
					canDrop = false;
				}
			}
		}

		//If the piece can drop
		if (canDrop)
		{
			//Move it down
			currentControlledPiece->position.y++;
		}
		else
		{
			//Freeze the piece in place
			for (int y = 0; y < currentControlledPiece->getSize(); y++)
			{
				for (int x = 0; x < currentControlledPiece->getSize(); x++)
				{
					if (currentControlledPiece->getShape()[y][x] > 0)
					{
						board_visual[currentControlledPiece->position.y + y][currentControlledPiece->position.x + x] = currentControlledPiece->getShape()[y][x] + 10;
					}
				}
			}
		}
	}
}

//Move the piece to the left
bool Board::moveLeft()
{
	bool canMove = true;
	//For all the block positions
	for (int i = 0; i < currentControlledPiece->blockPositions.size(); i++)
	{
		//Check next block's position
		sf::Vector2f nextBlockPos;
		nextBlockPos.y = currentControlledPiece->blockPositions[i].y + currentControlledPiece->position.y;
		nextBlockPos.x = currentControlledPiece->blockPositions[i].x + currentControlledPiece->position.x - 1;
		

		//If its in board bounds
		if (nextBlockPos.x > 0)
		{
			int nextValue = board_visual[nextBlockPos.y][nextBlockPos.x];
			//If their is another block there
			if (nextValue > 10)
			{
				//Cant move
				canMove = false;
			}
		}

	}

	//If this piece can move
	if (canMove)
	{
		//Move to the left
		currentControlledPiece->position.x--;
		return true;
	}
	return false;
}

//Move the piece to the right
bool Board::moveRight()
{
	bool canMove = true;

	//For all the block positions
	for (int i = 0; i < currentControlledPiece->blockPositions.size(); i++)
	{
		//Get next block's position
		sf::Vector2f nextBlockPos;
		nextBlockPos.y = currentControlledPiece->blockPositions[i].y + currentControlledPiece->position.y;
		nextBlockPos.x = currentControlledPiece->blockPositions[i].x + currentControlledPiece->position.x + 1; 

		//If its in board bounds
		if (nextBlockPos.x < board_visual.size())
		{
			//Get next value
			int nextValue = board_visual[nextBlockPos.y][nextBlockPos.x];

			//If there is a block there
			if (nextValue > 10)
			{
				canMove = false;
			}
		}
	}

	//If the piece can move
	if (canMove)
	{
		//Move to the right
		currentControlledPiece->position.x++;
		return true;
	}
	return false;
}

//Get all possible positions
std::vector<Move*> Board::allPossiblePositions()
{
	//For Returning
	std::vector<Move*> possibleMoves;

	//Get the pieces initial positions
	sf::Vector2f initialPosition = currentControlledPiece->position;

	//For all possible rotations
	for (int i = 0; i < 4; i++)
	{
		//Rotate the piece
		currentControlledPiece->rotate();

		//Move to complete left
		int leftCounter = 0;
		while (moveLeft())
		{
			leftCounter++;
		};


		//Start Moving Right
		int rightCounter=-1;
		do
		{
			//Move Right
			rightCounter++;

			//Create new Move
			Move* newMove = new Move();
			//Get a copy of the board
			Board newBoard = *this;
			
			//Complete Drop the piece
			newBoard.completeDrop();

			//Get the new Visual
			newMove->board = newBoard.board_visual;

			//For all the moves done, write them down in the moves vector
			for (int a = 0; a < i+1; a++)
			{
				newMove->moves.push_back(MoveType::ROTATE);
			}

			for (int b = 0; b < leftCounter; b++)
			{
				newMove->moves.push_back(MoveType::LEFT);
			}

			for (int c = 0; c < rightCounter; c++)
			{
				newMove->moves.push_back(MoveType::RIGHT);
			}

			newMove->moves.push_back(MoveType::DROP);

			possibleMoves.push_back(newMove);
			//Move piece back up
			currentControlledPiece->position.y = initialPosition.y;

		} while (moveRight());

	}

	//Move piece to original posiiton
	currentControlledPiece->position = initialPosition;

	//Return all moves
	return possibleMoves;
}

//Get board info
LevelInfo Board::getInfo()
{
	return info;
}

//Get Score
int Board::getScore()
{
	return score;
}

//Get Changed Piece
bool Board::getChangedPiece()
{
	return changePiece;
}

//Set Changed Piece
void Board::setChangedPiece(bool state)
{
	changePiece = state;
}

//End Game
void Board::destruct()
{
	delete currentControlledPiece;
	currentControlledPiece = NULL;

	delete  nextPiece;
	nextPiece = NULL;
}

//Update the board
void Board::updateVisual()
{
	//Reset the whole board except the frozen pieces
	for (int y = 0; y < board_visual.size(); y++)
	{
		for (int x = 0; x < (board_visual.size() / 2) +4; x++)
		{
			if (board_visual[y][x] < 10)
			{
				board_visual[y][x] = 0;
			}
		}
	}

	//Print the piece
	for (int j = 0; j < currentControlledPiece->getSize(); j++)
	{
		for (int i = 0; i < currentControlledPiece->getSize(); i++)
		{
			if (currentControlledPiece->getShape()[j][i] > 0)
			{
				board_visual[currentControlledPiece->position.y + j][currentControlledPiece->position.x + i] = currentControlledPiece->getShape()[j][i];
			}
		}
	}
}

//Check cleared lines
int Board::checkClearLine()
{
	int linesCleared = 0;

	//Iterate through the board's y-axis
	for (int y = 0; y < board_visual.size(); y++)
	{
		int blockCounter=0;

		//Iterate through the board's x-axis
		for (int x = 0; x < (board_visual.size() / 2) + 4; x++)
		{
			//If there is a block here
			if (board_visual[y][x] > 11)
			{
				blockCounter++;
			}
		}

		//If the row is filled
		if (blockCounter >= 10)
		{
			//Clear this line
			clearLine(y);
			linesCleared++;
		}
	}
	return linesCleared;
}

//Clear Line
void Board::clearLine(int line)
{
	//Delete the line
	board_visual.erase(board_visual.begin()+line);
	//Create a new one at the top
	board_visual.insert(board_visual.begin(), { 0,0,11,0,0,0,0,0,0,0,0,0,0,11,0,0 });
	
}

//Calculate the score
int Board::calculateScore(int linesCleared)
{
	//Return score depending on how many lines are cleared
	if (linesCleared == 1)
	{
		return 40 * (info.getLevel()+1);
	}
	else if (linesCleared == 2)
	{
		return 100 * (info.getLevel() + 1);
	}
	else if (linesCleared == 3)
	{
		return 300 * (info.getLevel() + 1);
	}
	else if (linesCleared == 4)
	{
		return 1200 * (info.getLevel() + 1);
	}
	else
	{
		return 0;
	}

}

//Check Fail
bool Board::checkFail()
{
	//Go through the hole 1st row
	for (int x = 0; x < (board_visual.size() / 2) + 4; x++)
	{
		//If their is a block there
		if (board_visual[2][x] > 11)
		{
			//Fail
			return true;
		}
	}
	return false;
}

//Update the board
bool Board::update()
{
	//Incremetn frame drop counter
	frameDropCounter++;
	//Drop piece and get alive state
	bool alive =dropPiece(false);
	//Update the board
	updateVisual();
	//Return alive state
	return alive;
}

//Render Board
void Board::render(sf::RenderWindow* window)
{
	//Iterate through the boeard's y-axis
	for (int y = 0; y < board_visual.size(); y++)
	{
		//Iterate through board's x-axis
		for (int x = 2; x < (board_visual.size() / 2)+3; x++)
		{
			//create a new block
			sf::RectangleShape block;
			block.setSize({ 30,30 });
			block.setPosition(sf::Vector2f( (x-2) * 30,y * 30 ));

			//Fill block with color depending on the positions value
			switch (board_visual[y][x])
			{
				case 1:
				case 11:
					block.setFillColor(sf::Color::White);
					break;

				case 2:
				case 12:
					block.setFillColor(sf::Color::Cyan);
					break;

				case 3:
				case 13:
					block.setFillColor(sf::Color::Blue);
					break;

				case 4:
				case 14:
					block.setFillColor(sf::Color(255,127,0));
					break;

				case 5:
				case 15:
					block.setFillColor(sf::Color::Yellow);
					break;

				case 6:
				case 16:
					block.setFillColor(sf::Color::Magenta);
					break;

				case 7:
				case 17:
					block.setFillColor(sf::Color::Green);
					break;

				case 8:
				case 18:
					block.setFillColor(sf::Color::Red);
					break;

				default:
					block.setFillColor(sf::Color::Transparent);
					break;
			}
			//Draw Block
			window->draw(block);
		}
	}

	//Same rendering with the next piece
	for (int j = 0;j < nextPiece->getSize(); j++)
	{
		for (int i = 0; i < nextPiece->getSize(); i++)
		{
			sf::RectangleShape nextBlock;
			nextBlock.setSize({ 30,30 });
			nextBlock.setPosition(sf::Vector2f( i  * 30 +460, j * 30+200));

			switch (nextPiece->getShape()[j][i])
			{
			case 1:
				nextBlock.setFillColor(sf::Color::White);
				break;

			case 2:
				nextBlock.setFillColor(sf::Color::Cyan);
				break;

			case 3:
				nextBlock.setFillColor(sf::Color::Blue);
				break;

			case 4:
				nextBlock.setFillColor(sf::Color(255, 127, 0));
				break;

			case 5:
				nextBlock.setFillColor(sf::Color::Yellow);
				break;

			case 6:
				nextBlock.setFillColor(sf::Color::Magenta);
				break;

			case 7:
				nextBlock.setFillColor(sf::Color::Green);
				break;

			case 8:
				nextBlock.setFillColor(sf::Color::Red);
				break;

			default:
				nextBlock.setFillColor(sf::Color::Black);
				break;
			}

			window->draw(nextBlock);

		}
	}
	
	//Render Text
	font.loadFromFile("font/pixel.ttf");
	game.setFont(font);
	stats.setFont(font);
	scoreDisplay.setFont(font);
	levelDisplay.setFont(font);
	nextPieceTxt.setFont(font);
	window->draw(game);
	window->draw(nextPieceTxt);
	stats.setString("High Score: \nLevel: ");
	scoreDisplay.setString(std::to_string(score)),
	window->draw(stats);
	window->draw(scoreDisplay);
	levelDisplay.setString(std::to_string(info.getLevel()));
	window->draw(levelDisplay);
	
}