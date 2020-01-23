/*
 * QUAD4Node.cpp
 *
 *  Created on: 18 nov. 2019
 *      Author: fernando.olivares
 */

#include "../Headers/CQUAD4Node.h"
#include "../Headers/Global.h"

#pragma GCC diagnostic ignored "-Wunused-variable"

CCQUAD4Node::CCQUAD4Node() {
	m_EID 			= ZERO;
	m_PID 			= ZERO;
	m_G1 			= ZERO;
	m_G2 			= ZERO;
	m_G3 			= ZERO;
	m_G4 			= ZERO;
	m_THETA_MCID 	= ZERO;
	m_ZOOFS 		= ZERO;
}

CCQUAD4Node::~CCQUAD4Node() {
	// TODO Auto-generated destructor stub
}

