#include "Piece.h"

//Constructor
Piece::Piece(Type type)
{
	//Create the shape depending on the type
	switch (type)
	{
		case LINE:
			shape =
			{
				{0,0,0,0},
				{2,2,2,2},
				{0,0,0,0},
				{0,0,0,0}
		    };
			break;

		case RL:
			shape =
			{
				{3,0,0},
				{3,3,3},
				{0,0,0}
			};
			break;

		case L:
			shape =
			{
				{0,0,4},
				{4,4,4},
				{0,0,0}
			};
			break;

		case SQUARE:
			shape =
			{
				{0,0,0,0},
				{0,5,5,0},
				{0,5,5,0},
				{0,0,0,0}
			};
			break;

		case T:
			shape =
			{
				{0,6,0},
				{6,6,6},
				{0,0,0}
			};
			break;

		case RZ:
			shape =
			{
				{7,7,0},
				{0,7,7},
				{0,0,0}
			};
			break;

		case Z:
			shape =
			{
				{0,8,8},
				{8,8,0},
				{0,0,0}
			};
			break;

		default:
			shape =
			{
				{0,0,0},
				{0,0,0},
				{0,0,0}
			};
			break;
	}

	//Get the block positions
	for (int j = 0; j < shape.size(); j++)
	{
		for (int i = 0; i < shape.size(); i++)
		{
			if (shape[j][i] > 0)
			{
				blockPositions.push_back(sf::Vector2f(i,j));
			}
		}
	}
};

//Rotate Piece
void Piece::rotate()
{
	std::vector<std::vector<int>> newShape;

	//Rotate Shape
	for (int j = 0; j < shape.size(); j++)
	{
		std::vector<int> newShapePart;
		for (int i = 0; i < shape.size(); i++)
		{
			newShapePart.push_back(shape[shape.size() - 1 - i][j]);
		}
		newShape.push_back(newShapePart);
	}
	shape = newShape;

	blockPositions.clear();

	//Get new block positions
	for (int j = 0; j < shape.size(); j++)
	{
		for (int i = 0; i < shape.size(); i++)
		{
			if (shape[j][i] > 0)
			{
				blockPositions.push_back(sf::Vector2f(i, j));
			}
		}
	}

}

//Check rotate Positions
std::vector<sf::Vector2f> Piece::checkRotatePositions()
{
	std::vector<std::vector<int>> newShape;

	//Rotate mock up shape
	for (int j = 0; j < shape.size(); j++)
	{
		std::vector<int> newShapePart;
		for (int i = 0; i < shape.size(); i++)
		{
			newShapePart.push_back(shape[shape.size() - 1 - i][j]);
		}
		newShape.push_back(newShapePart);
	}

	//Get new block positions
	std::vector<sf::Vector2f> newBlockPos;
	for (int j = 0; j < newShape.size(); j++)
	{
		for (int i = 0; i < newShape.size(); i++)
		{
			if (newShape[j][i] > 0)
			{
				newBlockPos.push_back(sf::Vector2f(i, j));
			}
		}
	}

	return newBlockPos;
}

//Get Shape
std::vector<std::vector<int>> Piece::getShape()
{
	return shape;
}

//Get Size
int Piece::getSize()
{
	return shape.size();
}
