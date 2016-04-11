#ifndef _SAVE_SLOT_HPP
#define _SAVE_SLOT_HPP
#include "stdafx.h"

/**
*	\struct SaveSlot
*	\brief This is all of the loaded game data from the saveData.xml file parsed and made available to the 
*	programmer in simple to use std format.
*/
struct SaveSlot {
	/**
	*	@brief The default constructor used for creating a SaveSlot. This will initalise the m_LVL_DATA data to
	*	a default state. Currently the code initalises all the varibles required by the struct
	*	@param id - This is the id tag given to each of the save slots which determine wheather the save slot is
	*	1, 2 or 3. 
	*/
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
	/**
	*	@brief The overloaded constructor used for creating a loaded SaveSlot. This will initalise the m_LVL_DATA data to
	*	its counterpart in the .xml. Currently the code initalises all the varibles required by the struct
	*	@param id - This is the id tag given to each of the save slots which determine wheather the save slot is 1, 2 or 3. 
	*	@param time - This is loaded in from .xml to the m_timePlayed varible
	*	@param gold - This is loaded in from .xml to the m_currentGold varible
	*	@param data - This is loaded in from .xml to the m_LVL_DATA varible
	*	@param num_lvls_unlocked - This is calculted using the data gathered from the .xml and stored in m_levels_unlocked
	*/
	SaveSlot(int id, int time, int gold, map<string, bool> data, int num_lvls_unlocked, map<string, bool> ach, int num_ach_unlocked, map<string, int> stat)
		: m_id(id), m_timePlayed(time), m_currentGold(gold), m_LVL_DATA(data), m_levels_unlocked(num_lvls_unlocked), m_ACH_DATA(ach), m_achieve_unlocked(num_ach_unlocked), m_STAT_DATA(stat){		}
	int m_id;						//!<This value is used for storing the current id of the save slot as the game only allows for 3 saveslots at a time
	int m_timePlayed;               //!<This is the value for total time played it will be stored in seconds for now but later when that begins to become obsolete can be changed to Minutes or minutes and seconds
	int m_currentGold;              //!<This value represents the total amount of gold on the players character at that time
	int m_levels_unlocked;          //!<This number represents the number of levels unlocked this kind of information can be used on the main screen or save select.
	int m_achieve_unlocked;          //!<
	
	/**
	*	@brief This represents the Level information in raw data once it has been parsed from the xml file
	*	@param string - The Level name
	*	@param bool - Whether the level is unlocked or not
	*/
	map<string, bool> m_LVL_DATA; 
	/**
	*	@brief 
	*	@param string - The Level name
	*	@param bool - Whether the level is unlocked or not
	*/
	map<string, bool> m_ACH_DATA;
	/**
	*	@brief
	*	@param string - The Level name
	*	@param bool - Whether the level is unlocked or not
	*/
	map<string, int> m_STAT_DATA;
};

#endif