#pragma once
#include <vector>
#include "SFML\Graphics.hpp"

//Piece Types
enum Type {LINE, L, RL, SQUARE, T, Z, RZ };

//Piece Class
class Piece
{
public:
	//Constructor
	Piece(Type type);

	//Rotate Piece
	void rotate();
	//Check Rotate Positions for Piece
	std::vector<sf::Vector2f> checkRotatePositions();

	//Get Piece Shape
	std::vector<std::vector<int>> getShape();

	//Piece Position
	sf::Vector2f position;
	//Piece's block positions
	std::vector<sf::Vector2f> blockPositions;

	//Get Piece Grid Size
	int getSize();
private:
	//Shape
	std::vector<std::vector<int>> shape;
};

