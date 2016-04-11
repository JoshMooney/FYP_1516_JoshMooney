#ifndef _XBOX_CONNECTOR_HPP
#define _XBOX_CONNECTOR_HPP
#include "stdafx.h"

class xboxConnector {
private:
	static xboxConnector* mInstance;		//!<This is the instance of the resourceManager and is required as part of the singleton pattern if confused: https://en.wikipedia.org/wiki/Singleton_pattern
	xboxConnector();						//!<Template default constructor for the class

	bool m_connected;
public:
	~xboxConnector();
	static xboxConnector* inst();      //!<Fetches the current instance of the Manager is required to achieve the singleton pattern

	bool isConnected();
	void connect(bool b);
};

#endif