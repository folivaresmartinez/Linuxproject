/*
 * Connection2D2D.cpp
 *
 *  Created on: 12 nov. 2019
 *      Author: fernando.olivares
 */

#include "../Headers/Connection.h"
#include "../Headers/Global.h"

/**
 * Default Class Constructor
 */
CConnection::CConnection() {

	m_IdConnection = ZERO;
	m_TieArea = ZERO;
	m_IdCoGNode = ZERO;

	m_mapGFEMNodes = new MapGFEMNodes();
	m_mapDFEMNodes = new MapDFEMNodes();
	m_mapSegments = new MapSegments();

	m_MatrixData = new DataMatrixDFEM1D2D();
}

/**
  Default Class Destructor
 */
CConnection::~CConnection() {

	for (std::map<int, CGFEMNode *>::iterator it=m_mapGFEMNodes->begin(); it != m_mapGFEMNodes->end(); it++)  {
		delete (*it).second;
		it = m_mapGFEMNodes->erase(it);
	}
	delete m_mapGFEMNodes;
	m_mapGFEMNodes = NULL;

	for (MapDFEMNodes::iterator it=m_mapDFEMNodes->begin(); it != m_mapDFEMNodes->end(); it++)  {
		delete (*it).second;
		it = m_mapDFEMNodes->erase(it);
	}
	delete m_mapDFEMNodes;
	m_mapDFEMNodes = NULL;

	for (MapSegments::iterator it=m_mapSegments->begin(); it != m_mapSegments->end(); it++)  {
		delete (*it).second;
		it = m_mapSegments->erase(it);
	}
	delete m_mapSegments;
	m_mapSegments = NULL;

	for (DataMatrixDFEM1D2D::iterator it=m_MatrixData->begin(); it != m_MatrixData->end(); it++)  {
		ListStringData * lst = (*it);
		delete lst;

		it = m_MatrixData->erase(it);
	}
	delete m_MatrixData;
	m_MatrixData = NULL;

}

