/*
 * Segments.cpp
 *
 *  Created on: 27 nov. 2019
 *      Author: fernando.olivares
 */


#include "../Headers/Segment.h"
#include "../Headers/Global.h"

/**
 * To don't show the warnings of the unused variables.
 */
#pragma GCC diagnostic ignored "-Wunused-variable"

CSegment::CSegment() {
	m_IdSegment 	= SZERO;
	m_G1 			= SZERO;
	m_xG1 			= ZERO;
	m_yG1 			= ZERO;
	m_zG1 			= ZERO;
	m_G2 			= SZERO;
	m_xG2 			= ZERO;
	m_yG2 			= ZERO;
	m_zG2 			= ZERO;
	m_ELSET_NAME 	= STRING_EMPTY;
	m_t 			= ZERO;
	m_L 			= ZERO;
	m_Ai 			= ZERO;
	m_xGi 			= ZERO;
	m_yGi 			= ZERO;
	m_zGi 			= ZERO;
	m_Ai_xGi 		= ZERO;
	m_Ai_yGi 		= ZERO;
	m_Ai_zGi 		= ZERO;


}

CSegment::~CSegment() {
	// TODO Auto-generated destructor stub
}

