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
		if (e.GetType() == Mouse::Event::Type::LPress) //Click Izquierdo --> Revelar casilla
		{
			const Vei2 mouseScreenPosition = Vei2(e.GetPosX(), e.GetPosY()); 
			 
			if (field.isInsideField(mouseScreenPosition))
			{
				const Vei2 mouseFieldPosition = ((mouseScreenPosition - field.GetFieldTopLeft()) / SpriteCodex::tileSize);
				field.RevealTile(mouseFieldPosition);
				if (field.TileAt(mouseFieldPosition).HasBomb())
				{
					gameState = GameState::Lost;
					field.RevealAllBombs(mouseFieldPosition);
				}
			}
		} else
			if (e.GetType() == Mouse::Event::Type::RPress) //Click Derecho --> Colocar Bandera
			{
				const Vei2 mouseScreenPosition = Vei2(e.GetPosX(), e.GetPosY());
				if (field.isInsideField(mouseScreenPosition))
				{
					const Vei2 mousefieldPosition = ((mouseScreenPosition - field.GetFieldTopLeft()) / SpriteCodex::tileSize);
					field.FlagTile(mousefieldPosition);
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
	
	switch (gameState)
	{
	case Game::GameState::Playing:
		field.Draw(gfx);
		break;
	case Game::GameState::Lost:
		field.Draw(gfx);
		SpriteCodex::DrawGameOver(Vei2(200, 0), gfx);
		break;
	case Game::GameState::Won:
		field.Draw(gfx);
		SpriteCodex::DrawGameWon(Vei2(200, 0), gfx);
		break;
	default:
		break;
	}
	

}
