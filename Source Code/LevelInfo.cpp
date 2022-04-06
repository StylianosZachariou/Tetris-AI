#include "LevelInfo.h"

//Constructor
LevelInfo::LevelInfo()
{
   
}

//Get Level
int LevelInfo::getLevel()
{
    return currentLevel;
}

//Increment Cleared Lines
void LevelInfo::incrementClearedLines(int lines)
{
    linesClearedForLevel += lines;
    totalLinesCleared += lines;

    //Check if the level is done
    if (linesClearedForLevel >= levelTolinesChart[currentLevel])
    {
        linesClearedForLevel -= levelTolinesChart[currentLevel];
        currentLevel++;
    }
}

//Get Total Lines Cleared
int LevelInfo::getTotalLinesCleared()
{
    return totalLinesCleared;
}

//Get speed
int LevelInfo::getSpeed()
{
    //Return Speed Depending on level
    if (currentLevel < 30)
    {
        return levelToSpeedChart[currentLevel];
    }
    else
    {
        return levelToSpeedChart[29];
    }
}
