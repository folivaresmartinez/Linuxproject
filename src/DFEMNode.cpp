/*
 * DFEMNode.cpp
 *
 *  Created on: 12 nov. 2019
 *      Author: fernando.olivares
 */

#include "../Headers/DFEMNode.h"
#include "../Headers/Global.h"

CDFEMNode::CDFEMNode() {
	m_SYST 					= ZERO;
	m_x						= ZERO;
	m_y						= ZERO;
	m_z						= ZERO;
	m_Transf 				= ZERO;
	m_Elm_As_1 				= ZERO;
	m_ELSET_1				= STRING_EMPTY;
	m_G1_Elm_As_1 			= ZERO;
	m_G2_Elm_As_1 			= ZERO;
	m_G3_Elm_As_1 			= ZERO;
	m_G4_Elm_As_1 			= ZERO;
	m_Elm_As_2 				= ZERO;
	m_ELSET_2				= STRING_EMPTY;
	m_G1_Elm_As_2 			= ZERO;
	m_G2_Elm_As_2 			= ZERO;
	m_G3_Elm_As_2 			= ZERO;
	m_G4_Elm_As_2 			= ZERO;
	m_Elm_As_3 				= ZERO;
	m_ELSET_3				= STRING_EMPTY;
	m_G1_Elm_As_3 			= ZERO;
	m_G2_Elm_As_3 			= ZERO;
	m_G3_Elm_As_3 			= ZERO;
	m_G4_Elm_As_3 			= ZERO;
	m_Elm_As_4 				= ZERO;
	m_ELSET_4				= STRING_EMPTY;
	m_G1_Elm_As_4 			= ZERO;
	m_G2_Elm_As_4 			= ZERO;
	m_G3_Elm_As_4 			= ZERO;
	m_G4_Elm_As_4 			= ZERO;

	m_t1					= ZERO;
	m_t2					= ZERO;
	m_t3					= ZERO;
	m_t4					= ZERO;
	m_segment_1				= STRING_EMPTY;
	m_Syst_NODE_2_1 		= ZERO;
	m_X2_1					= ZERO;
	m_Y2_1					= ZERO;
	m_Z2_1					= ZERO;
	m_segment_2				= STRING_EMPTY;
	m_Syst_NODE_2 			= ZERO;
	m_X2_2					= ZERO;
	m_Y2_2					= ZERO;
	m_Z2_2					= ZERO;
	m_segment_3				= STRING_EMPTY;
	m_Syst_NODE_2_3 		= ZERO;
	m_X2_3					= ZERO;
	m_Y2_3					= ZERO;
	m_Z2_3					= ZERO;
	m_segment_4				= STRING_EMPTY;
	m_Syst_NODE_2_4 		= ZERO;
	m_X2_4					= ZERO;
	m_Y2_4					= ZERO;
	m_Z2_4					= ZERO;
	m_Segment_1_xG			= ZERO;
	m_segment_1_yG			= ZERO;
	m_segment_1_zG			= ZERO;
	m_segment_1_L			= ZERO;
	m_segment_1_A			= ZERO;
	m_segment_2_xG			= ZERO;
	m_segment_2_yG			= ZERO;
	m_segment_2_zG			= ZERO;
	m_segment_2_L			= ZERO;
	m_segment_2_A			= ZERO;
	m_Segment_3_xG			= ZERO;
	m_segment_3_yG			= ZERO;
	m_segment_3_zG			= ZERO;
	m_segment_3_L			= ZERO;
	m_segment_3_A			= ZERO;
	m_segment_4_xG			= ZERO;
	m_segment_4_yG			= ZERO;
	m_segment_4_zG			= ZERO;
	m_segment_4_L			= ZERO;
	m_segment_4_A			= ZERO;


}

CDFEMNode::~CDFEMNode() {
	// TODO Auto-generated destructor stub
}

