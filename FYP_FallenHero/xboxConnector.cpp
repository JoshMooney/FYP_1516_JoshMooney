#include "stdafx.h"
#include "xboxConnector.hpp"

xboxConnector* xboxConnector::mInstance = nullptr;

xboxConnector::xboxConnector() {	}

xboxConnector::~xboxConnector() {	
	delete mInstance;
}

xboxConnector * xboxConnector::inst() {
	if (!mInstance) {
		mInstance = new xboxConnector();
	}
	return mInstance;
}

bool xboxConnector::isConnected() {
	return m_connected;
}

void xboxConnector::connect(bool b) {
	m_connected = b;
}
