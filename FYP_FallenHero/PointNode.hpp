#ifndef _POINT_NODE_HPP
#define _POINT_NODE_HPP
#include "stdafx.h"
#include "SFML\System\Vector2.hpp"

class PointNode {
private:
	string m_id;
	sf::Vector2f m_position;

	string m_next;
	string m_previous;
	bool isRoot;
public:
	PointNode(sf::Vector2f pos, std::pair<string, string> links) : m_position(pos) {
		m_next = links.first;
		m_previous = links.second;
	}
	PointNode(sf::Vector2f pos, string links) : m_position(pos) {
		m_next = links;

	}
	~PointNode()	{	}

	//! Sets the next node to the node passed in
	void setNext(string n) { m_next = n; }
	//! Sets the previous node to the node passed in
	void setPrevious(string n) { m_previous = n; }

	//! Returns the next node in the link.
	string& getNextID() { return m_next; }
	//! Returns the next node in the link.
	string& getNext() { return m_next; }

	//! Returns the positon of the point node.
	sf::Vector2f position() const { return m_position; }

	string getID() { return m_id; }
};

#endif