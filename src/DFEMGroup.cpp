/*
 * DFEMGroup.cpp
 *
 *  Created on: 10 dic. 2019
 *      Author: fernando.olivares
 */

#include "../Headers/DFEMGroup.h"
#include "../Headers/ELEMENTSection.h"
#include "../Headers/ELSETSection.h"
#include "../Headers/SHELLSection.h"

CDFEMGroup::CDFEMGroup() {

	m_PartName = STRING_EMPTY;

	m_MapDFEMData = new MapDFEMData();
	m_MapDFEMObjects = new MapDFEMObjects();
    m_MapSHELLSections = new MapSHELLSections();
	m_MapELSETSections = new MapELSETSections();

	m_MapELEMENTSections = new MapELEMENTSections();
}

CDFEMGroup::~CDFEMGroup() {
	for (MapDFEMObjects::iterator it = m_MapDFEMObjects->begin(); it != m_MapDFEMObjects->end(); it++)  {
		delete (*it).second;
		it = m_MapDFEMObjects->erase(it);
	}
	delete m_MapDFEMObjects;
	m_MapDFEMObjects = NULL;

	for (MapSHELLSections::iterator it = m_MapSHELLSections->begin(); it != m_MapSHELLSections->end(); it++)  {
		delete (*it).second;
		it = m_MapSHELLSections->erase(it);
	}
	delete m_MapSHELLSections;
	m_MapSHELLSections = NULL;

	for (MapELSETSections::iterator it = m_MapELSETSections->begin(); it != m_MapELSETSections->end(); it++)  {
		delete (*it).second;
		it = m_MapELSETSections->erase(it);
	}
	delete m_MapELSETSections;
	m_MapELSETSections = NULL;

	for (MapELEMENTSections::iterator it = m_MapELEMENTSections->begin(); it != m_MapELEMENTSections->end(); it++)  {
		delete (*it).second;
		it = m_MapELEMENTSections->erase(it);
	}
	delete m_MapELEMENTSections;
	m_MapELEMENTSections = NULL;


	m_MapDFEMData->clear();
	delete m_MapDFEMData;
	m_MapDFEMData = NULL;


}

