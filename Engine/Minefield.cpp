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
	
	for (Vei2 tileIndex(0, 0); tileIndex.y < widthInTiles; tileIndex.y++)
	{

		for (tileIndex.x = 0; tileIndex.x < widthInTiles; tileIndex.x++)
		{
			if (TileAt(tileIndex).HasBomb())
			{
				const int minX = std::max(0, tileIndex.x - 1);
				const int minY = std::max(0, tileIndex.y - 1);
				const int maxX = std::min(widthInTiles -1, tileIndex.x + 1);
				const int maxY = std::min(heightInTiles -1, tileIndex.y + 1);
				

				for (Vei2 neighbourTileIndex(minX, minY); neighbourTileIndex.y <= maxY; neighbourTileIndex.y++)
				{
					for (neighbourTileIndex.x = minX; neighbourTileIndex.x <= maxX; neighbourTileIndex.x++)
					{
						if (neighbourTileIndex == tileIndex) continue;
						TileAt(neighbourTileIndex).AddNeighbourBomb();
					}

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
		else  
		{
			SpriteCodex::DrawTileX(tileOrigin, gfx, nBombsArround);
		}
		break;
	default:
		break;
	}
}

void Minefield::Tiles::FlagIt()
{
	if (state == State::Flagged)
	{
		state = State::Hidden;
	}
	else
	{
		state = State::Flagged;
	}
}

void Minefield::Tiles::Reveal()
{
	if (! (state == State::Flagged))state = State::Revealed;
	
}



void Minefield::Tiles::AddNeighbourBomb()
{
	nBombsArround++;
	
}


