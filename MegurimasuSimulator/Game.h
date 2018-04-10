#pragma once
#include "FieldDrawer.h"
#include "Field.h"
#include "Team.h"

// TODO: 領域ポイントの処理
class Game
{
private:
	Field _field;
	FieldDrawer _field_drawer;
	Array<std::shared_ptr<Team>> _teams;

	GameInfo getGameInfo() const;
	std::map<TeamType, Array<Agent>> getAgentMap() const;
	Array<Agent> getAgents() const;

public:
	void Update();
	void Draw() const;

public:
	Game(const Field &field, std::shared_ptr<Team> team_a, std::shared_ptr<Team> team_b);
	virtual ~Game();
};
