/*
 * ELSETSection.cpp
 *
 *  Created on: 28 nov. 2019
 *      Author: fernando.olivares
 */

#include "../Headers/ELSETSection.h"
#include "../Headers/Global.h"

CELSETSection::CELSETSection() {

	m_ElsetName = STRING_EMPTY;
	m_InstanceName = STRING_EMPTY;

	m_lstNodes = new ListStringData();
}

CELSETSection::~CELSETSection() {

	m_lstNodes->clear();

	delete m_lstNodes;
	m_lstNodes = NULL;
}

