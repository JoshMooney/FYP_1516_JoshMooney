#ifndef WORLD_MAP_HPP
#define WORLD_MAP_HPP
#include "stdafx.h"

#include <map>
#include <vector>
#include "WorldNode.hpp"
#include "ResourceManager.hpp"
#include "vCamera.hpp"

/**
*	@class WorldMap
*	@brief Is responsable for storing a vector of WorldNodes as well as generating the arcs and 
*	drawing both the arcs and nodes. This class must be held by the WorldScene class for moving
*	the player icon around and chooseing a level
*	@see WorldNode
*	@see WorldScene
*/
class WorldMap{
private:
	vector<WorldNode> m_map;
	string s_horz_arc, s_vert_arc;
	vector<sf::Sprite> m_arcs;
	float m_arc_height;
	sf::Vector2f m_map_origin;
	sf::Texture t_player_icon;
	sf::Sprite s_player_icon;
	float m_seperator;
	vCamera m_camera;
	WorldNode m_test_node = WorldNode("TEST", sf::Vector2f(500, 500), false);
	sf::Sprite m_test_arc;
	sf::FloatRect m_bounds;
public:
	//!for storing the number of levels and the name to identify them by.
	enum LEVEL { 
	LVL_1,		//!<Enum state for level 1  
	LVL_2,      //!<Enum state for level 2
	LVL_3A,     //!<Enum state for level 3a 
	LVL_3B,     //!<Enum state for level 3b
	LVL_4,      //!<Enum state for level 4 
	LVL_5,      //!<Enum state for level 5 
	LVL_6       //!<Enum state for level 6 
	};
	/**
	*	@brief Default constructor for the map this method should be deprecated and no longer used as 
	*	far as i know.
	*/
	WorldMap();
	/**
	*	@brief Overloaded Contructor allowing for the origin of the plotted map to to be set.
	*	@param sf::Vecotr2f The origin to begin creating the map.
	*/
	WorldMap(sf::Vector2f origin_pos);

	/**
	*	@brief Calculates the center of the map taking each of the nodes and arcs into account.
	*	@return sf::Vecotr2f Center point of the map.
	*/
	sf::Vector2f getCenter();
	/**
	*	@brief Creates the m_bound Float Rect here for the bounds of the map.
	*/
	void generateBounds();
	/**
	*	@brief Loads the required assets for the Arcs needed for between nodes
	*/
	void loadMedia();
	/**
	*	@brief This Function generates the hard coded map of nodes for the world map.
	*/
	void createMap();
	/**
	*	@brief This funciton generates the map using the data passed in, in the map_data
	*	@param map<string, bool> strings to bools representing the levels and weather or not
	*	they are unlocked.
	*/
	void createMap(map<string, bool> map_data);
	/**
	*	@brief Calls the Plot arcs on the Nodes to connect each of them up to one another.
	*/
	void addArcs();
	/**
	*	@brief This method checks the center of each node and determines which side of l2 is in
	*	regards to l1 then a arc can be created and returned. This method also sets the neighbouring
	*	node field in the nodes to one another traversing between them.
	*	@param l1 The first level to begin the arc at
	*	@param l2 The second level is to calculate where the end needs to be.
	*	@return sf::Sprite This is the Arc itself being returned.
	*/
	sf::Sprite PlotArc(LEVEL l1, LEVEL l2);
	/**
	*	@brief Gets the map of nodes and returns a pointer to the first element in the map.
	*	@return vector<WorldNode>* Pointer to the world map.
	*/
	vector<WorldNode>* getNodes();

	/**
	*	@brief Render the WorldMap which includes all the nodes and the arcs connecting those nodes.
	*	@param sf::RenderWindow The SFML window to render to.
	*/
	void render(sf::RenderWindow &w);
	/**
	*	@brief Gets a node in the map with the enum of the passed in LEVEL 
	*	@param LEVEL The level to get from the map.
	*	@return WorldNode* The node with the stte passed in.
	*/
	WorldNode* getNode(LEVEL l)	{	return &m_map[l];	}
	/**
	*	@brief Gets a node in the map with the enum state name assocated with the string passed in by calling the strtolvl()
	*	funtciton.
	*	@param string The string of the Node to fetch.
	*	@return WorldNode* The node with the Id of the parameter.
	*/
	WorldNode* getNode(string l)	{ return &m_map[strtolvl(l)]; }
		/**
	*	@brief Converts the string passed in into the approprate LEVEL state for loading a saving the file correctly.
	*	This method is the mirror of the lvltostr() function.
	*	@parma string The string to be translated.
	*	@return LEVEL The translated state.
	*/
	LEVEL strtolvl(string s)	{
		if (s == "LVL_1"){
			return LVL_1;
		}
		else if (s == "LVL_2"){
			return LVL_2;
		}
		else if (s == "LVL_3A"){
			return LVL_3A;
		}
		else if (s == "LVL_3B"){
			return LVL_3B;
		}
		else if (s == "LVL_4"){
			return LVL_4;
		}
		else if (s == "LVL_5"){
			return LVL_5;
		}
		else if (s == "LVL_6"){
			return LVL_6;
		}
		else{
			cLog::inst()->print(2, "WorldMap", "Invaild string to LEVEL conversion, default to LVL_1");
			return LVL_1;
		}
	}
	/**
	*	@brief Converts the LEVEL state passed in into the approprate string for loading a level correctly.
	*	This method is the mirror of the strtolvl() function.
	*	@parma LEVEL The state to be translated.
	*	@return string The translated string.
	*/
	string lvltostr(LEVEL l)	{
		switch (l){
		case LVL_1:
			return "LVL_1";
		case LVL_2:
			return "LVL_2";
		case LVL_3A:
			return "LVL_3A";
		case LVL_3B:
			return "LVL_3B";
		case LVL_4:
			return "LVL_4";
		case LVL_5:
			return "LVL_5";
		case LVL_6:
			return "LVL_6";
		}
	}
};

#endif