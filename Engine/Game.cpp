/****************************************************************************************** 
 *	Chili DirectX Framework Version 16.07.20											  *	
 *	Game.cpp																			  *
 *	Copyright 2016 PlanetChili.net <http://www.planetchili.net>							  *
 *																						  *
 *	This file is part of The Chili DirectX Framework.									  *
 *																						  *
 *	The Chili DirectX Framework is free software: you can redistribute it and/or modify	  *
 *	it under the terms of the GNU General Public License as published by				  *
 *	the Free Software Foundation, either version 3 of the License, or					  *
 *	(at your option) any later version.													  *
 *																						  *
 *	The Chili DirectX Framework is distributed in the hope that it will be useful,		  *
 *	but WITHOUT ANY WARRANTY; without even the implied warranty of						  *
 *	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the						  *
 *	GNU General Public License for more details.										  *
 *																						  *
 *	You should have received a copy of the GNU General Public License					  *
 *	along with The Chili DirectX Framework.  If not, see <http://www.gnu.org/licenses/>.  *
 ******************************************************************************************/
#include "MainWindow.h"
#include "Game.h"

Game::Game(MainWindow& wnd)
	:
	wnd(wnd),
	gfx(wnd),
	gameState(GameState::Playing),
	field(nBombs)
{
}

void Game::Go()
{
	gfx.BeginFrame();	
	UpdateModel();
	ComposeFrame();
	gfx.EndFrame();
}

void Game::UpdateModel()
{
	while (!wnd.mouse.IsEmpty() && (gameState == GameState::Playing))
	{
		const Mouse::Event e = wnd.mouse.Read();
		if (e.GetType() == Mouse::Event::Type::LPress)
		{
			const Vei2 mouseScreenPosition = Vei2(e.GetPosX(), e.GetPosY()); 
			if (field.isInsideField(mouseScreenPosition))
			{
				const Vei2 mousefieldPosition = ((mouseScreenPosition - field.GetFieldTopLeft()) / SpriteCodex::tileSize);
				field.TileAt(mousefieldPosition).Reveal();
				if (field.TileAt(mousefieldPosition).HasBomb()) gameState = GameState::Lost;
			}
		} else
			if (e.GetType() == Mouse::Event::Type::RPress)
			{
				const Vei2 mouseScreenPosition = Vei2(e.GetPosX(), e.GetPosY());
				if (field.isInsideField(mouseScreenPosition))
				{
					const Vei2 mousefieldPosition = ((mouseScreenPosition - field.GetFieldTopLeft()) / SpriteCodex::tileSize);
					field.TileAt(mousefieldPosition).FlagIt();
					
				}

			}
		if (field.CheckWinCondition(nBombs))
		{
			gameState = GameState::Won;
		}
	}


}

void Game::ComposeFrame()
{
	field.Draw(gfx);
	if (gameState == GameState::Lost)SpriteCodex::DrawGameOver(Vei2(200, 150), gfx);
	else if(gameState == GameState::Won)SpriteCodex::DrawGameWon(Vei2(200, 150), gfx);

}
