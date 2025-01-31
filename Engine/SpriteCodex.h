#pragma once

#include "Graphics.h"
#include "Vei2.h"

class SpriteCodex
{
public:
	// width and height of all tiles
	static constexpr int tileSize = 16;
	Vei2 screenCenter= Vei2((Graphics::ScreenWidth / 2), (Graphics::ScreenHeight / 2));
	// base color for all tiles
	static constexpr Color baseColor = { 192,192,192 };
	// 16x16 tile sprites assume (192,192,192) background and top left origin
	static void DrawTile0( const Vei2& pos,Graphics& gfx );
	static void DrawTile1( const Vei2& pos,Graphics& gfx );
	static void DrawTile2( const Vei2& pos,Graphics& gfx );
	static void DrawTile3( const Vei2& pos,Graphics& gfx );
	static void DrawTile4( const Vei2& pos,Graphics& gfx );
	static void DrawTile5( const Vei2& pos,Graphics& gfx );
	static void DrawTile6( const Vei2& pos,Graphics& gfx );
	static void DrawTile7( const Vei2& pos,Graphics& gfx );
	static void DrawTile8( const Vei2& pos,Graphics& gfx );
	static void DrawTileX(const Vei2& pos, Graphics& gfx, const int X);

	static void DrawTileButton( const Vei2& pos,Graphics& gfx );
	static void DrawTileCross( const Vei2& pos,Graphics& gfx );
	static void DrawTileFlag( const Vei2& pos,Graphics& gfx );
	static void DrawTileBomb( const Vei2& pos,Graphics& gfx );
	static void DrawTileBombRed( const Vei2& pos,Graphics& gfx );
	static void DrawGameOver(const Vei2& topLeft, Graphics& gfx);
	static void DrawGameWon(const Vei2& topLeft, Graphics& gfx);
};