#pragma once

//Level Info Class
class LevelInfo
{
public:

	//Constructor
	LevelInfo();

	//Getters
	int getLevel();
	int getTotalLinesCleared();
	int getSpeed();

	//Increment Clear Lines
	void incrementClearedLines(int lines);

private:

	//Curent Level
	int currentLevel = 0;
	//Lines Cleared for moving to next level
	int linesClearedForLevel = 0;
	//Total Lines Cleared
	int totalLinesCleared = 0;
	//Lines to move on to nest level chart
	int levelTolinesChart[30] = { 10,20,30,40,50,60,70,80,90,100,100,100,100,100,100,100,110,120,130,140,150,160,170,180,190,200,200,200,200,200 };
	//Level to peed Chart
	int levelToSpeedChart[30] = {250,225,200,175,150,125,125,125,100,100,100,75,75,75,50,50,50,50,50,50,50,50,50,50,25,25,25,25,25,25};
};

