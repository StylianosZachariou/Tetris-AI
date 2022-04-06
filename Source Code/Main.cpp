#include <iostream>
#include "Level.h"
#include "openGA.hpp"
#include <Windows.h>

#define LINESTOCLEAR 1000

//Seed Variable
int randomSeed = 0;

float averageScore[25];
float bestScore[25];

//Chromosome Structure
struct Chromosome {

	//Genes
	float linesCleared;
	float holes;
	float roughness;
	float weightedHeight;
	float cumulativeHeight;
	float relativeHeight;
	float highestHole;
};

//Cost structure
struct Cost {
	//Sore
	float score;
};

typedef EA::Genetic<Chromosome, Cost> Genetic_Algorithm;
typedef EA::GenerationType<Chromosome, Cost> Generation_Type;

//Initialize Genes
void init_genes(Chromosome& s, const std::function<double(void)>& rnd01)
{
	//Fill genes with random values in range -0.5-0.5
	s.linesCleared = rnd01() - 0.5;
	s.holes = rnd01() - 0.5;
	s.roughness = rnd01() - 0.5;
	s.weightedHeight = rnd01() - 0.5;
	s.cumulativeHeight = rnd01() - 0.5;
	s.relativeHeight = rnd01() - 0.5;
	s.highestHole = rnd01() - 0.5;
}

//Calculate Fitness
double calculate_total_fitness(const Genetic_Algorithm::thisChromosomeType& X)
{
	
	//The more the score the less the cost
	return -X.middle_costs.score;
}

//Find the best move using genes
Move bestMove(std::vector<Move*> allMoves,const Chromosome& individual)
{

	Move currentBestMove;
	float currentBestMoveScore=-10000000;

	//For all the possible moves
	for (int i = 0; i < allMoves.size(); i++)
	{
		//Evaluate
		allMoves[i]->evaluate();

		//Calculate a score for the move
		float thisMoveScore = allMoves[i]->getLinesCleared() * individual.linesCleared +
			allMoves[i]->getHoles() * individual.holes +
			allMoves[i]->getRoughness() * individual.roughness +
			allMoves[i]->getWeightedHeight() * individual.weightedHeight +
			allMoves[i]->getCumulativeHeight() * individual.cumulativeHeight +
			allMoves[i]->getRelativeHeight() * individual.relativeHeight +
			allMoves[i]->getHighestHole() * individual.highestHole;

		//Find the move with the highest score
		if (thisMoveScore > currentBestMoveScore)
		{
			currentBestMoveScore = thisMoveScore;
			currentBestMove = *allMoves[i];
			delete allMoves[i];
			allMoves[i] = NULL;
		}
	}

	return currentBestMove;
}

//Processing The Window
void windowProcess(sf::RenderWindow* window)
{
	// Handle window events.
	sf::Event event;
	while (window->pollEvent(event))
	{
		switch (event.type)
		{
		case sf::Event::Closed:
			window->close();
			break;
		case sf::Event::Resized:
			window->setView(sf::View(sf::FloatRect(0.f, 0.f, (float)event.size.width, (float)event.size.height)));
			break;
		default:
			// don't handle other events
			break;
		}
	}
}

//Play the game
bool play(const Chromosome& individual, Cost& cost)
{
	// Initialise level
	Level* level = new Level(NULL, randomSeed);

	//Initialize Variables
	int linesCleared = 0;
	Move nextMove = bestMove(level->getBoard()->allPossiblePositions(), individual);
	int moveCounter = 0;
	bool alive=true;

	//"Game" Loop
	//Loop until the lines to cleared limit has been reached or the game is lost
	while (linesCleared < LINESTOCLEAR && alive)
	{
		//If the piece is changed
		if (level->getBoard()->getChangedPiece())
		{			
			//Find new best move
			nextMove = bestMove(level->getBoard()->allPossiblePositions(), individual);
			level->getBoard()->setChangedPiece(false);
			moveCounter = 0;
		}

		//Do the move
		if (moveCounter >= nextMove.moves.size())
		{
			linesCleared=level->handleInput(MoveType::DROP);
		}
		else
		{
			linesCleared=level->handleInput(nextMove.moves[moveCounter]);
			moveCounter++;
		}

		//Update level
		alive=level->update();
	}

	//Get the score for the calculating cost
	cost.score = level->getBoard()->getScore();
	
	//End the level
	level->end();

	delete level;
	level = NULL;

	return true;
}

//Play the game once
void singlePlay(const Chromosome& individual)
{
	//Create the window
	sf::RenderWindow* window = new sf::RenderWindow(sf::VideoMode(900, 650), "TetrisAI");

	// Initialise level
	Level* level = new Level(window, randomSeed);

	//Initialize Variables
	Move nextMove = bestMove(level->getBoard()->allPossiblePositions(), individual);
	int moveCounter = 0;
	bool alive = true;

	//"Game" Loop
	while (alive)
	{
		//If the piece is changed
		if (level->getBoard()->getChangedPiece())
		{
			//Find new best move
			nextMove = bestMove(level->getBoard()->allPossiblePositions(), individual);
			level->getBoard()->setChangedPiece(false);
			moveCounter = 0;
		}

		//Do the move
		if (moveCounter >= nextMove.moves.size())
		{
			level->handleInput(MoveType::DROP);
		}
		else
		{
			level->handleInput(nextMove.moves[moveCounter]);
			moveCounter++;
		}
		alive = level->update();
		level->render();
	}

	window->close();
	delete window;
	window = NULL;

	level->end();

	delete level;
	level = NULL;
}

//The Mutation Function
Chromosome mutationFunc(const Chromosome& xBase, const std::function<double(void)>& rnd01, double shrinkScale)
{

	//Create new chromosome from base chromosome
	Chromosome newChromosome = xBase;

	//Choose a random gene to change
	int randomNum = (int)rnd01() * 7;

	//Mutate the gene
	switch (randomNum)
	{
		case 0:
			newChromosome.linesCleared = (rnd01() - 0.5);
			break;

		case 1:
			newChromosome.holes = (rnd01() - 0.5) ;
			break;

		case 2:
			newChromosome.roughness = (rnd01() - 0.5) ;
			break;

		case 3:
			newChromosome.weightedHeight = (rnd01() - 0.5) ;
			break;

		case 4:
			newChromosome.cumulativeHeight = (rnd01() - 0.5) ;
			break;

		case 5:
			newChromosome.relativeHeight = (rnd01() - 0.5) ;
			break;

		case 6:
			newChromosome.highestHole = (rnd01() - 0.5) ;
			break;

		default:
			break;
	}
	return newChromosome;
}

//The crossover function
Chromosome crossoverFunc(const Chromosome& X1, const Chromosome& X2, const std::function<double(void)>& rnd01)
{
	//Make a chromosome identical to the first parent
	Chromosome newChromosome=X1;

	//Randomly get genes from the other parent
	if ((int)rnd01()*2 == 0)
	{
		newChromosome.linesCleared = X2.linesCleared;
	}

	if ((int)rnd01() * 2 == 0)
	{
		newChromosome.holes = X2.holes;
	}

	if ((int)rnd01() * 2 == 0)
	{
		newChromosome.roughness = X2.roughness;
	}

	if ((int)rnd01() * 2 == 0)
	{
		newChromosome.weightedHeight = X2.weightedHeight;
	}

	if ((int)rnd01() * 2 == 0)
	{
		newChromosome.cumulativeHeight = X2.cumulativeHeight;
	}

	if ((int)rnd01() * 2 == 0)
	{
		newChromosome.relativeHeight = X2.relativeHeight;
	}

	if ((int)rnd01() * 2 == 0)
	{
		newChromosome.highestHole = X2.highestHole;
	}

	return newChromosome;
}

//Report Generation
void reportGeneration(int genNumber, const Generation_Type& lastGen, const Chromosome& bestGenes)
{
	//Generation Report
	system("cls");

	std::cout << "Generation Number [ " << genNumber << " ]" << std::endl;
	std::cout << "Score Average: " << -lastGen.average_cost << std::endl;
	std::cout << "----------------------------------------" << std::endl;
	std::cout << "Best Genes: " << std::endl;
	std::cout << std::endl;
	std::cout << "Lines Cleared: " << bestGenes.linesCleared << std::endl;
	std::cout << "Holes: " << bestGenes.holes << std::endl;
	std::cout << "Roughness: " << bestGenes.roughness << std::endl;
	std::cout << "Weighted Height: " << bestGenes.weightedHeight << std::endl;
	std::cout << "Cumulative Height: " << bestGenes.cumulativeHeight << std::endl;
	std::cout << "Relative Height: " << bestGenes.relativeHeight << std::endl;
	std::cout << "Highest Hole: " << bestGenes.highestHole << std::endl;

	std::cout << std::endl;
	std::cout << "All Chromosome Costs: "<< std::endl;
	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 5; j++)
		{
			std::cout << -lastGen.chromosomes[(i * 5) + j].total_cost << "\t";
		}
		std::cout << std::endl;
	}

	singlePlay(bestGenes);

	//Make the best gene of the generation play a game
	std::cout << "Working on next Generation Please Wait" << std::endl;
}

//Main
int main()
{
	//Initialize Genetic Algorithm
	Genetic_Algorithm ga_obj;
	ga_obj.problem_mode = EA::GA_MODE::SOGA;
	ga_obj.population = 50;
	ga_obj.generation_max = 25;
	ga_obj.init_genes = init_genes;
	ga_obj.calculate_SO_total_fitness = calculate_total_fitness;
	ga_obj.eval_solution = play;
	ga_obj.mutate = mutationFunc;
	ga_obj.crossover = crossoverFunc;
	ga_obj.crossover_fraction = 1;
	ga_obj.mutation_rate =0.5;
	ga_obj.best_stall_max = 50;
	ga_obj.average_stall_max = 50;
	ga_obj.SO_report_generation = reportGeneration;
	ga_obj.solve();
}