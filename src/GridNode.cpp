/*
 * Grid.cpp
 *
 *  Created on: 15 nov. 2019
 *      Author: fernando.olivares
 */


#include "../Headers/GridNode.h"
#include "../Headers/Global.h"

CGridNode::CGridNode() {
	m_idNode 	= ZERO;
	m_CP 		= ZERO;
	m_CoordX1 	= ZERO;
	m_CoordX2 	= ZERO;
	m_CoordX3 	= ZERO;
	m_CD 		= ZERO;
}

CGridNode::~CGridNode() {
	// TODO Auto-generated destructor stub
}

/**
 *
 * @return
 */
CGridNode * CGridNode::LocalToGlobal() {

	CGridNode *oGrid = new CGridNode();

	oGrid->setCP(0);
	oGrid->setCoord_X1(this->getCoord_X1());
	oGrid->setCoord_X2(this->getCoord_X2());
	oGrid->setCoord_X3(this->getCoord_X3());
	oGrid->setCD(this->getCD());

	return oGrid;
}

