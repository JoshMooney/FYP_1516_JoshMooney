#ifndef _SAVE_SLOT_HPP
#define _SAVE_SLOT_HPP
#include "stdafx.h"

struct SaveSlot {
	SaveSlot(int id)  : m_id(id){
		m_LVL_DATA["LVL1"] = false;
		m_LVL_DATA["LVL2"] = true;
		m_LVL_DATA["LVL3"] = true;
		m_LVL_DATA["LVL4"] = true;
		m_LVL_DATA["LVL5"] = true;
		m_LVL_DATA["LVL6"] = true;
		m_LVL_DATA["LVL7"] = true;
		m_timePlayed = 0;
		m_currentGold = 0;
		m_levels_unlocked = 1;
	}
	SaveSlot(int id, int time, int gold, map<string, bool> data, int num_lvls_unlocked)
		: m_id(id), m_timePlayed(time), m_currentGold(gold), m_LVL_DATA(data), m_levels_unlocked(num_lvls_unlocked){		}
	int m_id;
	int m_NUM;
	int m_timePlayed;
	int m_currentGold;
	int m_levels_unlocked;
	map<string, bool> m_LVL_DATA;
};

#endif