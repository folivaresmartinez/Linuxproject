/*
 * DFEMLine.cpp
 *
 *  Created on: 22 nov. 2019
 *      Author: fernando.olivares
 */

#include "../Headers/DFEMObject.h"
#include "../Headers/Global.h"

CDFEMObject::CDFEMObject() {
	m_IdNode = SZERO;

	m_Coord_X = ZERO;
	m_Coord_Y = ZERO;
	m_Coord_Z = ZERO;
}

CDFEMObject::~CDFEMObject() {
	// TODO Auto-generated destructor stub
}

