#include "Minefield.h"

Minefield::Minefield(const int nBombs)
	:
	fieldDistX(0, widthInTiles - 1),
	fieldDistY(0, heightInTiles - 1),
	myRNG(dev())
{
	for (int i = 0; i < nBombs; i++)
	{
		Vei2 randomPosition;
		do
		{
			randomPosition = Vei2(fieldDistX(myRNG), fieldDistY(myRNG));
		} while (TileAt(randomPosition).HasBomb());
		TileAt(randomPosition).SetBomb();
	}
}

Minefield::Tiles& Minefield::TileAt(const Vei2 & gridPosition)
{
	return field[gridPosition.y * widthInTiles + gridPosition.x];
}

void Minefield::Draw(Graphics & gfx) 
{
	gfx.DrawRect(RectI(Vei2(0, 0), widthInTiles * SpriteCodex::tileSize, heightInTiles * SpriteCodex::tileSize), SpriteCodex::baseColor);
	for (Vei2 tileIndex(0,0) ; tileIndex.y < widthInTiles; tileIndex.y++)
	{

		for (tileIndex.x = 0; tileIndex.x < widthInTiles; tileIndex.x++)
		{
			Vei2& tileOrigin = Vei2(tileIndex.x * SpriteCodex::tileSize, tileIndex.y * SpriteCodex::tileSize);
			TileAt(tileIndex).Draw(tileOrigin,gfx);
		}
	}
}


void Minefield::Tiles::SetBomb()
{
	hasBomb = true;
}

bool Minefield::Tiles::HasBomb() const
{
	return hasBomb;
}

void Minefield::Tiles::Draw(const Vei2& tileOrigin, Graphics & gfx) const
{
	switch (state)
	{
	case Minefield::Tiles::State::Hidden:
		SpriteCodex::DrawTileButton(tileOrigin, gfx);
		break;
	case Minefield::Tiles::State::Flagged:
		break;
	case Minefield::Tiles::State::Revealed:
		break;
	default:
		break;
	}
}
