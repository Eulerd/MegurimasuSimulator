﻿#pragma once
#include "Client.h"
#include "../MeglimathCore/Utility.h"
#include "../MeglimathCore/GameLogic/Think.h"

class NextBestClient :
	public Client
{
public:
	NextBestClient();
	NextBestClient(TeamType type);

	String Name() override
	{
		return U"NextBest";
	}

	void Initialize(const GameInfo& info) override
	{
		_is_ready = false;
	}

	void Update(const GameInfo& info) override
	{
		auto agents = info.GetAgents(_type);		
		auto field = info.GetField();
		auto other_team = Transform::GetInverseTeam(_type);
		
		int best_point = -1000;
		Reseed(info.GetTurn());
		Think next_think =
		{
			Step{ Action(Random(0, 1)), Direction(Random(0, 7)) },
			Step{ Action(Random(0,1)),Direction(Random(0,7)) }
		};

		auto all_step = Utility::AllStep();
		for(int i = 0;i < all_step.size();i++)
		{
			auto next_field1 = field.MakeFieldFromStep(_type, agents[0], all_step[i]);

			for(int k = 0;k < all_step.size();k++)
			{
				auto next_field2 = next_field1.MakeFieldFromStep(_type, agents[1], all_step[k]);

				auto next_points = next_field2.GetTotalPoints();

				auto point_diff = next_points[_type] - next_points[other_team];

				if (best_point < point_diff)
				{
					best_point = point_diff;
					next_think = { all_step[i], all_step[k] };
				}
			}
		}	

		_think = next_think;
		_is_ready = true;
	}
};

