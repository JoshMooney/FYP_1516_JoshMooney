#ifndef _POINT_MAP_HPP
#define _POINT_MAP_HPP
#include "stdafx.h"
#include "PointNode.hpp"
#include <vector>
#include <map>

/**
*	@class 
*	@brief
*/
class PointMap {
private:
	map<string, shared_ptr<PointNode>> m_map;
public:
	PointMap() {

	}
	~PointMap() {

	}

	void append(string id, shared_ptr<PointNode> node) {
		m_map.insert(std::pair<string, shared_ptr<PointNode>>(id, node));
	}
	void clear() {
		m_map.clear();
	}
	bool has(string s) {
		return (m_map.count(s) > 0);
	}
	shared_ptr<PointNode> get(string s) {
		if (has(s))
			return m_map[s];
		else
			return nullptr;
	}
};

#endif