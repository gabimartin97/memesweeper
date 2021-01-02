#pragma once
#include "Vei2.h"
#include <random>
#include "Graphics.h"
#include "SpriteCodex.h"
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
		void Draw(const Vei2& tileOrigin, Graphics& gfx)const;

	private:
		bool hasBomb = false;
		State state = State::Hidden;

	};

public:
	Minefield(const int nBombs);
	Tiles& TileAt(const Vei2& gridPosition);
	void Draw(Graphics& gfx);


private:
	static constexpr int widthInTiles = 25;
	static constexpr int heightInTiles = 25;
	static constexpr int nTiles = widthInTiles*heightInTiles;
	std::mt19937 myRNG;
	std::random_device dev; //seed?
	std::uniform_int_distribution<int> fieldDistX;
	std::uniform_int_distribution<int> fieldDistY;
	
	Tiles field[nTiles];


};