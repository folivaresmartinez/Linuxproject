/*
 * GFEMNode.cpp
 *
 *  Created on: 12 nov. 2019
 *      Author: fernando.olivares
 */

#include "../Headers/GFEMNode.h"
#include "../Headers/Global.h"
#include "../Headers/Logger.h"

CGFEMNode::CGFEMNode() {
	m_GridNode 						= new CGridNode();
	m_EID_1 						= ZERO;
	m_ZOFFS_1						= ZERO;
	m_G1_1							= ZERO;
	m_G2_1							= ZERO;
	m_G3_1							= ZERO;
	m_G4_1							= ZERO;
	m_EID_2							= ZERO;
	m_ZOFFS_2 						= ZERO;
	m_G1_2 							= ZERO;
	m_G2_2 							= ZERO;
	m_G3_2 							= ZERO;
	m_G4_2 							= ZERO;
	m_ZOFFS							= ZERO;
	m_G1_1_CP 						= ZERO;
	m_G1_1_X1 						= ZERO;
	m_G1_1_X2 						= ZERO;
	m_G1_1_X3 						= ZERO;
	m_G2_1_CP 						= ZERO;
	m_G2_1_X1 						= ZERO;
	m_G2_1_X2 						= ZERO;
	m_G2_1_X3 						= ZERO;
	m_G3_1_CP 						= ZERO;
	m_G3_1_X1 						= ZERO;
	m_G3_1_X2 						= ZERO;
	m_G3_1_X3 						= ZERO;
	m_G1_2_CP 						= ZERO;
	m_G1_2_X1 						= ZERO;
	m_G1_2_X2 						= ZERO;
	m_G1_2_X3 						= ZERO;
	m_G2_2_CP 						= ZERO;
	m_G2_2_X1 						= ZERO;
	m_G2_2_X2 						= ZERO;
	m_G2_2_X3 						= ZERO;
	m_G3_2_CP 						= ZERO;
	m_G3_2_X1 						= ZERO;
	m_G3_2_X2 						= ZERO;
	m_G3_2_X3 						= ZERO;
	m_V3_X1_NORM 					= ZERO;
	m_V3_X2_NORM 					= ZERO;
	m_V3_X3_NORM 					= ZERO;
	m_NODE_2_ID 					= ZERO;
	m_NODE_2_CP 					= ZERO;
	m_NODE_2_X1 					= ZERO;
	m_NODE_2_X2 					= ZERO;
	m_NODE_2_X3 					= ZERO;
	m_NODE_2_CD 					= ZERO;
	m_X0 							= ZERO;
	m_Y0 							= ZERO;
	m_Z0 							= ZERO;
	m_d 							= ZERO;
	m_NODE_3_ID 					= ZERO;
	m_NODE_3_CP 					= ZERO;
	m_NODE_3_X1 					= ZERO;
	m_NODE_3_X2 					= ZERO;
	m_NODE_3_X3 					= ZERO;
	m_NODE_3_CD 					= ZERO;

	m_Nodes_Adyacent_1 				= STRING_EMPTY;
	m_Nodes_Adyacent_2 				= STRING_EMPTY;

	m_KINEMATIC_COUPLING_1_2_CARD 	= STRING_EMPTY;
	m_NODE_1_CARD 					= STRING_EMPTY;
	m_NODE_2_CARD 					= STRING_EMPTY;
	m_NODE_3_CARD 					= STRING_EMPTY;
	m_EQUATION_CARD 				= STRING_EMPTY;

	m_1D_Elm_Asoc_Type 				= STRING_EMPTY;
	m_CoG_NODE 						= ZERO;
	m_CoG_NODE_CP 					= ZERO;
	m_CoG_NODE_X1 					= ZERO;
	m_CoG_NODE_X2 					= ZERO;
	m_CoG_NODE_X3 					= ZERO;
	m_CoG_NODE_CD 					= ZERO;

	m_CoG_NODE_Card 				= STRING_EMPTY;

	m_KINEMATIC_COUPLING_CoG_DFEM_CARD 	= STRING_EMPTY;
	m_EQUATION_CARD_CoG_DFEM			= STRING_EMPTY;

}

CGFEMNode::~CGFEMNode() {
	// TODO Auto-generated destructor stub
}

std::string CGFEMNode::getNODE_1_CARD() {

	std::string strReturn = STRING_EMPTY;

	try {
		std::string strIdNode = to_string(this->getIdNode());
		std::string strGrid_X1 = std::to_string(this->getGridNode()->getCoord_X1());
		std::string strGrid_X2 = std::to_string(this->getGridNode()->getCoord_X2());
		std::string strGrid_X3 = std::to_string(this->getGridNode()->getCoord_X3());

		strReturn = strIdNode + "," + strGrid_X1 + "," + strGrid_X2 + "," + strGrid_X3;

	}
	catch(std::exception &exc) {

		CLogger::GetLogger()->Log(" <EXCEPTION>: CGFEMNode::getNODE_1_CARD " + std::string(exc.what()));
	}


	return strReturn;
}


