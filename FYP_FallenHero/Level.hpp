#ifndef LEVEL_HPP
#define LEVEL_HPP
#include "stdafx.h"

#include <vector>
#include <map>
using std::string;
//using namespace std;

#define vector<map<string, int>> LEVEL_DATA
class Level{
private:
	/*
	LEVEL_DATA m_enemy_data;
	LEVEL_DATA m_checkpoint_data;
	LEVEL_DATA m_platform_data;
	map<string, int> m_spawn_data;
	map<string, int> m_exit_data;
	vector<vector<string>> m_tile_data;*/
public:
	Level();
	~Level();

	void loadLevel(string lvl_name);
};

#endif