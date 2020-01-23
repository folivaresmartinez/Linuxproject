/*
 * AssociativityFile.cpp
 *
 *  Created on: 12 nov. 2019
 *      Author: fernando.olivares
 */

#include "../Headers/AssociativityFile.h"
#include "../Headers/Connection.h"
#include "../Headers/Global.h"

/**
 * Default contructor
 */
CAssociativityFile::CAssociativityFile() {
	m_lstConnections1D2D = new ListConnections();
	m_lstConnections2D2D = new ListConnections();
}

/**
 * Default destructor
 */
CAssociativityFile::~CAssociativityFile() {

	for (ListConnections::iterator it=m_lstConnections1D2D->begin(); it != m_lstConnections1D2D->end(); it++)  {
		delete (*it);
		it = m_lstConnections1D2D->erase(it);
	}
	delete m_lstConnections1D2D;
	m_lstConnections1D2D = NULL;

	for (ListConnections::iterator it=m_lstConnections2D2D->begin(); it != m_lstConnections2D2D->end(); it++)  {
		delete (*it);
		it = m_lstConnections2D2D->erase(it);
	}
	delete m_lstConnections2D2D;
	m_lstConnections2D2D = NULL;

}

