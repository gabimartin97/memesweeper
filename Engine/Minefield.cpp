#include "Minefield.h"
#include <algorithm>

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
	ScanForBombs();
}

Minefield::Tiles& Minefield::TileAt(const Vei2 & gridPosition)
{
	return field[gridPosition.y * widthInTiles + gridPosition.x];
}

Vei2 Minefield::GetFieldTopLeft() const
{
	return fieldTopLeft;
}

void Minefield::Draw(Graphics & gfx) 
{
	gfx.DrawRect(RectI(fieldTopLeft, fieldBottomRight), SpriteCodex::baseColor);
	for (Vei2 tileIndex(0,0) ; tileIndex.y < widthInTiles; tileIndex.y++)
	{

		for (tileIndex.x = 0; tileIndex.x < widthInTiles; tileIndex.x++)
		{
			Vei2& tileOrigin = Vei2(fieldTopLeft.x + tileIndex.x * SpriteCodex::tileSize, fieldTopLeft.y + tileIndex.y * SpriteCodex::tileSize);
			TileAt(tileIndex).Draw(tileOrigin,gfx);
		}
	}
}

bool Minefield::isInsideField(const Vei2 & position)
{
	
	return (position.x > fieldTopLeft.x && position.x < fieldBottomRight.x && position.y > fieldTopLeft.y && position.y < fieldBottomRight.y);
}

void Minefield::ScanForBombs()
{
	int nBombs = 0;
	for (Vei2 tileIndex(0, 0); tileIndex.y < widthInTiles; tileIndex.y++)
	{

		for (tileIndex.x = 0; tileIndex.x < widthInTiles; tileIndex.x++)
		{
			if (TileAt(tileIndex).HasBomb())
			{
				if (tileIndex.x > 0)
				{
					Vei2 topLeft = tileIndex - Vei2(1, 1);
					TileAt(topLeft).AddNeighbourBomb();

					Vei2 Left = tileIndex - Vei2(1, 0);
					TileAt(Left).AddNeighbourBomb();

					Vei2 bottomLeft = tileIndex - Vei2(1, -1);
					TileAt(bottomLeft).AddNeighbourBomb();

				}
				if (tileIndex.x < widthInTiles - 1)
				{
					Vei2 topRight = tileIndex + Vei2(1, -1);
					TileAt(topRight).AddNeighbourBomb();

					Vei2 Right = tileIndex + Vei2(1, 0);
					TileAt(Right).AddNeighbourBomb();

					Vei2 bottomRight = tileIndex - Vei2(-1, -1);
					TileAt(bottomRight).AddNeighbourBomb();

				}

				if (tileIndex.y > 0)
				{
					Vei2 top= tileIndex - Vei2(0, 1);
					TileAt(top).AddNeighbourBomb();
				}

				if (tileIndex.y < heightInTiles - 1)
				{
					Vei2 bottom = tileIndex + Vei2(0,1);
					TileAt(bottom).AddNeighbourBomb();
				}


				
			}
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
		SpriteCodex::DrawTileButton(tileOrigin, gfx);
		SpriteCodex::DrawTileFlag(tileOrigin, gfx);
		break;

	case Minefield::Tiles::State::Revealed:
		SpriteCodex::DrawTile0(tileOrigin, gfx);
		if(hasBomb) SpriteCodex::DrawTileBomb(tileOrigin, gfx);
		break;
	default:
		break;
	}
}

void Minefield::Tiles::FlagIt()
{
	state = State::Flagged;
}

void Minefield::Tiles::Reveal()
{
	state = State::Revealed;
}

void Minefield::Tiles::AddNeighbourBomb()
{
	nBombsArround++;
	
}


