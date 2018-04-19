#include "Game.h"

GameInfo Game::getGameInfo() const
{
	return GameInfo(_field, getAgentMap());
}

std::map<TeamType, Array<Agent>> Game::getAgentMap() const
{
	std::map<TeamType, Array<Agent>> agents;
	agents[TeamType::A] = _teams[0]->GetAgents();
	agents[TeamType::B] = _teams[1]->GetAgents();

	return agents;
}

Array<Agent> Game::getAgents() const
{
	return _teams[0]->GetAgents().append(_teams[1]->GetAgents());
}

void Game::initAgents()
{
	Size size = _field.GetCells().size();

	initAgents(Point(Random((size.x - 2) / 2), Random((size.y - 2) / 2)));
}

void Game::initAgents(Point init_pos)
{
	Size size = _field.GetCells().size();

	size -= Point(1, 1);
	Point agent_pos[] =
	{
		init_pos,
		Point(size.x - init_pos.x, init_pos.y),
		Point(init_pos.x, size.y - init_pos.y),
		size - init_pos
	};

	_teams[0]->InitAgentsPos(agent_pos[0], agent_pos[1]);
	_teams[1]->InitAgentsPos(agent_pos[2], agent_pos[3]);
}

void Game::InitalizeFromJson(const String path)
{
	JSONReader json(path);

	_field = Field(path);

	if (json[U"InitPos"].isNull())
	{
		initAgents();
	}
	else
	{
		initAgents(json[U"InitPos"].get<Point>());
	}

	_turn = json[U"Turn"].get<int>();
}

int Game::GetTurn() const
{
	return _turn;
}

void Game::Update()
{
	if (_turn <= 0)
	{
		return;
	}
	
	GameInfo info = getGameInfo();
	auto agents_map = getAgentMap();
	auto agents = getAgents();

	_thinks[TeamType::A] = Think(_teams[0]->NextThink(info));
	_thinks[TeamType::B] = Think(_teams[1]->NextThink(info));

	// シミュレーション
	Array<std::pair<Point, std::pair<Direction, TeamType>>> move_point_arr;
	Array<Point> remove_points;
	for (TeamType team : {TeamType::A, TeamType::B})
	{
		for (int i = 0; i < 2; i++)
		{
			Direction dir = _thinks[team].steps[i].direction;
			// エージェントを動かしたい方向に動かした場合の座標
			Point pos = agents_map[team][i].GetPosition().movedBy(Transform::DirToDelta(dir));

			// エージェントが動作する座標を追加
			switch (_thinks[team].steps[i].action)
			{
			case Action::Move:
				move_point_arr.push_back(std::make_pair(pos, std::make_pair(dir, team)));
				break;
			case Action::RemoveTile:
				remove_points.push_back(pos);
				break;
			}
		}
	}

	// 衝突していないエージェントの行動のみ実行する
	for (auto & pos_map : move_point_arr)
	{
		auto pos = pos_map.first;

		// その座標に行くエージェントが一人、フィールド内
		// タイルが置かれていない、どのエージェントもいない
		if (move_point_arr.count_if([pos](std::pair<Point, std::pair<Direction, TeamType>> itr) {return itr.first == pos; }) == 1
			&& _field.IsInField(pos)
			&& _field.GetCells()[pos.y][pos.x].GetTile() == TileType::None
			&& agents.count_if([pos](Agent agent) { return agent.GetPosition() == pos; }) == 0)
		{
			auto dir = pos_map.second.first;
			auto team = pos_map.second.second;

			// 元の座標に戻す
			pos -= Transform::DirToDelta(dir);

			_teams[static_cast<int>(team)]->MoveAgent(pos, dir);
			_field.PaintCell(pos, team);
		}
	}

	// タイルを取る行動を実行
	for (auto & remove_point : remove_points)
	{
		if (remove_points.count_if(Equal(remove_point)) == 1 && _field.IsInField(remove_point))
		{
			_field.RemoveTile(remove_point);
		}
	}
	
	// ターンを進める
	_turn--;

	// チームの得点を更新
	_field.UpdatePoint();
}

void Game::Draw() const
{
	_drawer.DrawField(_field);
	_drawer.DrawAgents(getAgentMap());
	_drawer.DrawStatus(_thinks, _field, _turn);
}

Game::Game(std::shared_ptr<Team> team_a, std::shared_ptr<Team> team_b)
{
	_teams.append({ team_a, team_b });
}

Game::~Game()
{
}
