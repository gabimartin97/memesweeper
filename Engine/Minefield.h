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
		void FlagIt();
		void Reveal();
		
		void AddNeighbourBomb();
		
	private:
		bool hasBomb = false;
		int nBombsArround = 0;
		State state = State::Hidden;

	};

public:
	Minefield(const int nBombs);
	Tiles& TileAt(const Vei2& gridPosition);
	Vei2 GetFieldTopLeft()const;
	void Draw(Graphics& gfx);
	bool isInsideField(const Vei2& position);
	void ScanForBombs();

private:
	static constexpr int widthInTiles = 10;
	static constexpr int heightInTiles = 10;
	static constexpr int nTiles = widthInTiles*heightInTiles;
	const Vei2 fieldCenter = Vei2((Graphics::ScreenWidth / 2), (Graphics::ScreenHeight / 2));
	const Vei2 fieldTopLeft = fieldCenter - Vei2((widthInTiles / 2)*SpriteCodex::tileSize, ((heightInTiles / 2)*SpriteCodex::tileSize));
	const Vei2 fieldBottomRight = fieldCenter + Vei2((widthInTiles / 2)*SpriteCodex::tileSize, ((heightInTiles / 2)*SpriteCodex::tileSize));
		std::mt19937 myRNG;
	std::random_device dev; //seed?
	std::uniform_int_distribution<int> fieldDistX;
	std::uniform_int_distribution<int> fieldDistY;
	
	Tiles field[nTiles];


};