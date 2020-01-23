/*
 * Instance.cpp
 *
 *  Created on: 11 dic. 2019
 *      Author: fernando.olivares
 */

#include "../Headers/Instance.h"
#include "../Headers/Global.h"

CInstance::CInstance() {

	m_InstanceName = STRING_EMPTY;
	m_PartName = STRING_EMPTY;

	m_Value1 = ZERO;
	m_Value2 = ZERO;
	m_Value3 = ZERO;
}

CInstance::~CInstance() {
	// TODO Auto-generated destructor stub
}

