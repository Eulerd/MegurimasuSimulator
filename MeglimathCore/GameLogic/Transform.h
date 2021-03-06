﻿#pragma once
#include "Types.h"
#include "Think.h"


namespace Transform
{
	
	/// <summary>
	/// 方向から移動方向に変換する
	/// </summary>
	/// <param name="dir">変換元の方向</param>
	/// <returns>方向を変換した移動方向</returns>
	constexpr _Point<int> DirToDelta(Direction dir)
	{
		switch (dir)
		{
		case Direction::Right:
			return _Point<int>(1, 0);
			
		case Direction::RightUp:
			return _Point<int>(1, -1);
			
		case Direction::Up:
			return _Point<int>(0, -1);
			
		case Direction::LeftUp:
			return _Point<int>(-1, -1);
			
		case Direction::Left:
			return _Point<int>(-1, 0);

		case Direction::LeftDown:
			return _Point<int>(-1, 1);
			
		case Direction::Down:
			return _Point<int>(0, 1);
			
		case Direction::RightDown:
			return _Point<int>(1, 1);
			
		}
		return _Point<int>(0, 0);
	}

	constexpr Direction DeltaToDir(_Point<int> p)
	{
		if (p == _Point<int>(1, 0)) {
			return Direction::Right;
		}
		else if (p == _Point<int>(1, -1)) {
			return Direction::RightUp;
		}
		else if (p == _Point<int>(0, -1)) {
			return Direction::Up;
		}
		else if (p == _Point<int>(-1, -1)) {
			return Direction::LeftUp;
		}
		else if (p == _Point<int>(-1, 0)) {
			return Direction::Left;
		}
		else if (p == _Point<int>(-1, 1)) {
			return Direction::LeftDown;
		}
		else if (p == _Point<int>(0, 1)) {
			return Direction::Down;
		}
		else if (p == _Point<int>(1, 1)) {
			return Direction::RightDown;
		}
		else {
			return Direction::Stop;
		}
	}

	constexpr TileType ToTile(TeamType team)
	{
		switch (team)
		{
		case TeamType::Blue:
			return TileType::Blue;

		case TeamType::Red:
			return TileType::Red;
		}

		return TileType::None;
	}

	constexpr int ToNumPad(TeamType team, Direction dir)
	{
		int table[2][9] = { { 4,1,2,3,6,9,8,7,5 }, { 4,1,2,3,6,9,8,7,5 } };

		if (team == TeamType::Red) 
		{
			return table[0][(int)dir];
		}
		else
		{
			return table[1][(int)dir];
		}
	}

	constexpr TileType GetInverseTile(TileType tile)
	{
		switch (tile)
		{
		case TileType::Blue:
			return TileType::Red;
		case TileType::Red:
			return TileType::Blue;
		}

		return TileType::None;
	}

	constexpr TeamType GetInverseTeam(TeamType team)
	{
		switch (team)
		{
		case TeamType::Blue:
			return TeamType::Red;
		case TeamType::Red:
			return TeamType::Blue;
		}
	}

	const std::u32string ToString(Action action);

	const std::u32string ToString(Direction dir);

	const std::u32string ToString(Step step);

	const std::u32string ToString(TeamType team);

	const char ToChar(TileType tile);
}