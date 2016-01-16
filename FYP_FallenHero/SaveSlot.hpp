#ifndef _SAVE_SLOT_HPP
#define _SAVE_SLOT_HPP
#include "stdafx.h"

struct SaveSlot {
	SaveSlot(int id, int time, int gold, map<string, bool> data)
		: m_id(id), m_timePlayed(time), m_currentGold(gold), m_LVL_DATA(data)	{	}
	int m_id;
	int m_NUM;
	int m_timePlayed;
	int m_currentGold;
	map<string, bool> m_LVL_DATA;
};

#endif