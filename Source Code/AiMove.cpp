#include "AiMove.h"

//Constructor
Move::Move()
{

}

//Evaluate Move
void Move::evaluate()
{
	//Lines Cleared
	checkLinesCleared();
	//Holes
	checkHoles();
	//Roughness
	checkRoughness();
	//WeightedHeight
	checkWeightedHeight();
	//Cumulative Height
	checkCumulativeHeight();
	//Relative Height
	checkRelativeHeight();
	//Highest Hole
	checkHighestHole();
}

//Lines Clear Getter
int Move::getLinesCleared()
{
	return linesCleared;
}

//Holes Getter
int Move::getHoles()
{
	return holes;
}

//Roughness Getter
int Move::getRoughness()
{
	return roughness;
}

//Weighted Height Getter
int Move::getWeightedHeight()
{
	return weightedHeight;
}

//Cumulative Height Getter
int Move::getCumulativeHeight()
{
	return cumulativeHeight;
}

//Relative Height Getter
int Move::getRelativeHeight()
{
	return relativeHeight;
}

//Highest Hole Getter
int Move::getHighestHole()
{
	return highestHole;
}

//Check Lines Cleared from Board
void Move::checkLinesCleared()
{
	//Itarate through the board's y-axis
	for (int y = 0; y < board.size(); y++)
	{
		//Counts How many blocks in a row
		int blockCounter = 0;
		
		//Iterate through the board's x-axis
		for (int x = 0; x < (board.size() / 2) + 4; x++)
		{
			//if there is a block there
			if (board[y][x] > 11)
			{
				blockCounter++;
			}
		}

		//If the whole row is filles
		if (blockCounter >= 10)
		{
			//Line is cleared
			linesCleared++;
		}
	}
}

//Check Holes on Board
void Move::checkHoles()
{
	//Iterate through board's y-axis
	for (int y = 0; y < board.size()-2; y++)
	{
		//Iterate through board's x-axis
		for (int x = 0; x < (board.size() / 2) + 4; x++)
		{
			//If their is a row above this one
			if (y > 0)
			{
				//if this block is empty and  their is a block above it
				if (board[y][x] == 0 && !(board[(y - 1)][x] == 0))
				{
					//There is a hole
					holes++;
				}
			}
		}
	}
}

//Check Board's roughness
void Move::checkRoughness()
{
	//Iterate through the boards x-axis
	for (int x = 0; x < (board.size() / 2) + 4; x++)
	{
		//Iterate through the boards y-axis
		for (int y = 0; y < board.size() - 2; y++)
		{
			//if there is a rough above this one
			if (y > 0)
			{
				//If there is a block with nothing on top. 
				if (board[y][x] > 10 && board[(y - 1)][x] == 0)
				{
					//This is the height of the column
					heights.push_back(20 - y);
				}
			}
		}
	}

	//Loop for all the heights
	for (int i = 0; i < heights.size()-1; i++)
	{
		//The roughness is the difference between neighbouring heights
		roughness += abs(heights[i] - heights[(i + 1)]);
	}
}

//Check Board's Weighted Height
void Move::checkWeightedHeight()
{
	//Loop through all the heights
	for (int i = 0; i < heights.size(); i++)
	{
		//If this height is higher than the weighted height
		if (heights[i] > weightedHeight)
		{
			//This becomes the weighted height
			weightedHeight = heights[i];
		}
	}
}

//Check Board's Cumulative Heigt
void Move::checkCumulativeHeight()
{
	//Loop for all the heights
	for (int i = 0; i < heights.size(); i++)
	{
		//Add this height to cumulative height
		cumulativeHeight += heights[i];
	}
}

//Check Board's Relative Height
void Move::checkRelativeHeight()
{
	//Variabes for highest and lowest Height
	int highest=0, lowest=0;

	//Loop for all the heights
	for (int i = 0; i < heights.size(); i++)
	{
		//If this height is higher than the highest
		if (heights[i] > highest)
		{
			//this becomes the highest
			highest = heights[i];
		}

		//If the height is lower than the lowest
		if (heights[i] < lowest)
		{
			//this becomes the lowest
			lowest = heights[i];
		}
	}

	//Subtract the lowest from the highest to get relative height
	relativeHeight = highest - lowest;
}

//Check Board's Highest Hole
void Move::checkHighestHole()
{
	//Iterate through the board's y-axis
	for (int y = 0; y < board.size() - 2; y++)
	{
		//Iterate through the board's x-axis
		for (int x = 0; x < (board.size() / 2) + 4; x++)
		{
			//Check for a hole
			if (board[y][x] = 0 && board[y - 1][x] != 0)
			{
				//Get the height and break since this is the highest one
				highestHole = 20-y;
				break;
			}
		}
	}
}
