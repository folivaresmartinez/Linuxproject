/*
 * Node.cpp
 *
 *  Created on: 12 nov. 2019
 *      Author: NG82748
 */


#include "../Headers/Global.h"
#include "../Headers/Node.h"

CNode::CNode() {
	m_idNode 	= ZERO;
	m_strIdNode = STRING_EMPTY;
	m_strName 	= STRING_EMPTY;
	m_TieArea 	= ZERO;
	m_NodeType 	= ZERO;
}

CNode::~CNode() {
	// TODO Auto-generated destructor stub
}

