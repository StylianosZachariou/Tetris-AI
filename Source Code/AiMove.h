#pragma once
#include <vector>

//All Possible Moves
enum MoveType { ROTATE, LEFT, RIGHT, DROP };

//This class simbolizes a combination of moves for the ai
class Move
{
public:

	//Constructor
	Move();

	//Move Combination
	std::vector<MoveType> moves;
	//Board after moves
	std::vector<std::vector<int>> board;

	//Evaluate Move
	void evaluate();

	//Getters
	int getLinesCleared();
	int getHoles();
	int getRoughness();
	int getWeightedHeight();
	int getCumulativeHeight();
	int getRelativeHeight();
	int getHighestHole();

private:

	//Checks lines Cleared by Move
	void checkLinesCleared();
	//Checks Holes after Move
	void checkHoles();
	//Checks Roughness after Move
	void checkRoughness();
	//Checks Weighted Height after Move
	void checkWeightedHeight();
	//Checks Cumulative Height after Move
	void checkCumulativeHeight();
	//Checks Relative Height after Move
	void checkRelativeHeight();
	//Checks Highest Hole after Move
	void checkHighestHole();

	//Variables
	int linesCleared = 0;
	int holes = 0;
	int roughness = 0;
	int weightedHeight = 0;
	int cumulativeHeight = 0;
	int relativeHeight = 0;
	int highestHole = 0;

	//Heights of all columns
	std::vector<int> heights;
};
