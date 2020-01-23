/*
 * ELEMTSSection.cpp
 *
 *  Created on: 28 nov. 2019
 *      Author: fernando.olivares
 */

#include "../Headers/ELEMENTSection.h"
#include "../Headers/Global.h"

CELEMENTSection::CELEMENTSection() {
	m_ElementName = STRING_EMPTY;
	m_InstanceName = STRING_EMPTY;

	m_lstNodes = new ListStringData();

}

CELEMENTSection::~CELEMENTSection() {

	m_lstNodes->clear();

	delete m_lstNodes;
	m_lstNodes = NULL;
}

