/*
 * SourfaceNodesDistanceStore.cpp
 *
 *  Created on: 25 nov. 2019
 *      Author: fernando.olivares
 */

#include "../Headers/GFEMNodesDistance.h"
#include "../Headers/Global.h"

CGFEMNodesDistance::CGFEMNodesDistance() {
	m_IdConnection = ZERO;
	m_idNodeGFEM = ZERO;
	m_idNodeDFEM = SZERO;

	m_Distance = ZERO;

}

CGFEMNodesDistance::~CGFEMNodesDistance() {
	// TODO Auto-generated destructor stub
}

