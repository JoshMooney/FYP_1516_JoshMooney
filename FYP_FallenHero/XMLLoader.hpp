#ifndef _XML_LOADER_HPP
#define _XML_LOADER_HPP

#include "stdafx.h"
#include "tinyxml2.h"
#include "SaveSlot.hpp"
#include <vector>
#include <assert.h>

class XMLLoader {
private:
	tinyxml2::XMLDocument backupDoc;
	tinyxml2::XMLDocument xmlDoc;
	tinyxml2::XMLNode *pRoot;
	tinyxml2::XMLElement *saveGame;

	//Converting from XML to usable varables
	float string_to_float(string s){
		return atof(s.c_str());
	}
	int string_to_int(string s){
		return atoi(s.c_str());
	}
	bool string_to_bool(string s){
		if (string_to_int(s) == 1)
			return true;
		return false;
	}
public:
	vector<SaveSlot *> saved_data;

	XMLLoader(){
		//tinyxml2::XMLError eResult = xmlDoc.LoadFile("Assets/SaveData.xml");
		assert(xmlDoc.LoadFile("Assets/save_data.xml") != tinyxml2::XML_ERROR_FILE_NOT_FOUND);
		
		tinyxml2::XMLNode *pRoot = xmlDoc.FirstChild();
		//cout << string_to_int(s) << endl;
		
		saveGame = pRoot->FirstChildElement("SaveGame");
		if (saveGame == nullptr) throw tinyxml2::XML_ERROR_FILE_READ_ERROR;

		loadSaveSlots();
		/*
		tinyxml2::XMLElement * slot = saveGame->FirstChildElement("SaveSlot1");
		if (slot == nullptr) throw tinyxml2::XML_ERROR_FILE_READ_ERROR;

		tinyxml2::XMLElement * level = slot->FirstChildElement("Levels");
		if (level == nullptr) throw tinyxml2::XML_ERROR_FILE_READ_ERROR;

		tinyxml2::XMLElement * level_bool = level->FirstChildElement("LVL3");
		if (level_bool == nullptr) throw tinyxml2::XML_ERROR_FILE_READ_ERROR;
		string l_data = level_bool->GetText();
		cout << string_to_int(l_data) << endl;
		*/
		/*
		loadSaveSlots();
		*/
		/*
		const string image_ext = texture->Attribute("EXT");
		const string file_name = image_name + '.' + image_ext;*/
	}
	void loadSaveSlots(){
		string name = "SaveSlot";

		for (int i = 0; i < 3; i++){
			string slot_name = name + std::to_string(i + 1);
			//saveGame->FirstChildElement(slot_name);
			tinyxml2::XMLElement * slot = saveGame->FirstChildElement(slot_name.c_str());
			if (slot == nullptr) throw tinyxml2::XML_ERROR_FILE_READ_ERROR;

			tinyxml2::XMLElement * timeElement = slot->FirstChildElement("TimePlayed");
			if (timeElement == nullptr) throw tinyxml2::XML_ERROR_FILE_READ_ERROR;
			int time = string_to_int(timeElement->GetText());

			tinyxml2::XMLElement * goldElement = slot->FirstChildElement("CurrentGold");
			if (goldElement == nullptr) throw tinyxml2::XML_ERROR_FILE_READ_ERROR;
			int gold = string_to_int(goldElement->GetText());

			map<string, bool> map;
			tinyxml2::XMLElement * levelElement = slot->FirstChildElement("Levels");
			if (levelElement == nullptr) throw tinyxml2::XML_ERROR_FILE_READ_ERROR;
			//============================================================================================
			tinyxml2::XMLElement * ele = levelElement->FirstChildElement("LVL1");
			int text = string_to_int(ele->GetText());
			map["LVL1"] = text;

			ele = levelElement->FirstChildElement("LVL2");
			text = string_to_int(ele->GetText());
			map["LVL2"] = text;

			ele = levelElement->FirstChildElement("LVL3");
			text = string_to_int(ele->GetText());
			map["LVL3"] = text;

			ele = levelElement->FirstChildElement("LVL4");
			text = string_to_int(ele->GetText());
			map["LVL4"] = text;

			ele = levelElement->FirstChildElement("LVL5");
			text = string_to_int(ele->GetText());
			map["LVL5"] = text;

			ele = levelElement->FirstChildElement("LVL6");
			text = string_to_int(ele->GetText());
			map["LVL6"] = text;

			ele = levelElement->FirstChildElement("LVL7");
			text = string_to_int(ele->GetText());
			map["LVL7"] = text;
			//============================================================================================

			saved_data.push_back(new SaveSlot(i + 1, time, gold, map));
		}
	}
	void GenerateSaveFile(){
		//create and insert the root node of the .xml document
		tinyxml2::XMLNode *pRoot = xmlDoc.NewElement("Root");
		xmlDoc.InsertFirstChild(pRoot);

		tinyxml2::XMLElement *saveGame = xmlDoc.NewElement("SaveGame");
		for (int i = 0; i < 3; i++)
		{
			string d = "SaveSlot" + std::to_string(i + 1);
			const char * c = d.c_str();
			tinyxml2::XMLElement * saveSlot = xmlDoc.NewElement(c);

			//Inserts IntValue to the .xml file
			tinyxml2::XMLElement * pElement = xmlDoc.NewElement("TimePlayed");
			pElement->SetText(0);
			saveSlot->InsertEndChild(pElement);

			pElement = xmlDoc.NewElement("CurrentGold");
			pElement->SetText(0);
			saveSlot->InsertEndChild(pElement);

			pElement = xmlDoc.NewElement("Levels");
			for (int i = 0; i < 6; i++)
			{
				string d = "LVL" + std::to_string(i + 1);
				const char * c = d.c_str();
				tinyxml2::XMLElement * pListElement = xmlDoc.NewElement(c);
				pListElement->SetText(0);

				pElement->InsertEndChild(pListElement);
			}

			saveSlot->InsertEndChild(pElement);
			saveGame->InsertEndChild(saveSlot);
		}
		pRoot->InsertEndChild(saveGame);

		tinyxml2::XMLError eResult = xmlDoc.SaveFile("Assets/save_data.xml");

	}
	void initFile(){
		//xmlDoc = tinyxml2::XMLDocument();
		pRoot = xmlDoc.NewElement("Root");
		xmlDoc.InsertFirstChild(pRoot);

		saveGame = xmlDoc.NewElement("SaveGame");
	}
	void WriteSaveSlot(SaveSlot s){
		string d = "SaveSlot" + std::to_string(s.m_id);
		const char * c = d.c_str();
		tinyxml2::XMLElement * saveSlot = xmlDoc.NewElement(c);

		//Inserts Values to the .xml file
		tinyxml2::XMLElement * pElement = xmlDoc.NewElement("TimePlayed");
		pElement->SetText(s.m_timePlayed);
		saveSlot->InsertEndChild(pElement);

		pElement = xmlDoc.NewElement("CurrentGold");
		pElement->SetText(s.m_currentGold);
		saveSlot->InsertEndChild(pElement);

		pElement = xmlDoc.NewElement("Levels");

		for (int i = 0; i < 7; i++){
			string level = "LVL" + std::to_string(i + 1);
			const char * c = level.c_str();
			tinyxml2::XMLElement * pListElement = xmlDoc.NewElement(c);
			pListElement->SetText(s.m_LVL_DATA[level]);

			pElement->InsertEndChild(pListElement);

			saveSlot->InsertEndChild(pElement);
			saveGame->InsertEndChild(saveSlot);
		}
	}
	void save()	{
		xmlDoc.SaveFile("Backup_SavedData.xml");
		xmlDoc.Clear();
		initFile();

		WriteSaveSlot(*saved_data[0]);
		WriteSaveSlot(*saved_data[1]);
		WriteSaveSlot(*saved_data[2]);

		pRoot->InsertEndChild(saveGame);

		tinyxml2::XMLError eResult = xmlDoc.SaveFile("Assets/save_data.xml");
		if (eResult != NULL)
			perror("Error saving file a backup will be loaded on restart");
		if (remove("Backup_SavedData.xml") != 0)
			perror("Error deleting backup file");
	}
};
#endif