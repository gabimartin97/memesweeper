#pragma once
#include "Vei2.h"
#include <random>

class Minefield
{
private:


	class Tiles
	{
	public:
		enum class State
		{
			Hidden,
			Flagged,
			Revealed
		};
		Tiles() = default;
		void SetBomb();
		bool HasBomb()const;

	private:
		bool hasBomb = false;
		State state = State::Hidden;

	};

public:
	Minefield(const int nBombs);
	Tiles& TileAt(const Vei2& gridPosition);
	


private:
	static constexpr int widthInTiles = 25;
	static constexpr int heightInTiles = 25;
	std::mt19937 myRNG;
	std::random_device dev; //seed?
	std::uniform_int_distribution<int> fieldDistX;
	std::uniform_int_distribution<int> fieldDistY;
	
	Tiles field[widthInTiles*heightInTiles];


};