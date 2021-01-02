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


void Minefield::Tiles::SetBomb()
{
	hasBomb = true;
}

bool Minefield::Tiles::HasBomb() const
{
	return hasBomb;
}
