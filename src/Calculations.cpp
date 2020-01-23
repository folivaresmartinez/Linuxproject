/*
 * Calculations.cpp
 *
 *  Created on: 19 nov. 2019
 *      Author: fernando.olivares
 */

#include "../Headers/Calculations.h"

#include <string>
#include <stdlib.h>
#include <math.h>

#include "../Headers/AssociativityFile.h"
#include "../Headers/CSVReader.h"
#include "../Headers/GFEMReader.h"
#include "../Headers/DFEMReader.h"
#include "../Headers/Global.h"
#include "../Headers/Logger.h"
#include "../Headers/GridNode.h"

#include "../Headers/Vector3D.h"
#include "../Headers/Coordinate3D.h"
#include "../Headers/GFEMNodesDistance.h"
#include "../Headers/ELSETSection.h"
#include "../Headers/ELEMENTSection.h"
#include "../Headers/SHELLSection.h"
#include "../Headers/GlobalDFEMReader.h"

/**
 * We initialize the this object
 */
CCalculations* CCalculations::m_pThis = NULL;

/**
 * To don't show the warnings of the unused variables.
 */
#pragma GCC diagnostic ignored "-Wunused-variable"

/**
 * Default constructor
 */
CCalculations::CCalculations() {
	// TODO Auto-generated constructor stub

	m_T3D2OFFSET = std::stoi(CGlobal::GetGlobal()->getIniFile().get("T3D2_ABAQUS").get("offset"));

	m_mapGFEMNodes = new MapGFEMNodes();
}

/**
 *
 */
CCalculations::~CCalculations() {

	for (std::map<int, CGFEMNode *>::iterator it=m_mapGFEMNodes->begin(); it != m_mapGFEMNodes->end(); it++)  {
		delete (*it).second;
		it = m_mapGFEMNodes->erase(it);
	}
	delete m_mapGFEMNodes;
	m_mapGFEMNodes = NULL;

	delete m_pThis;
	m_pThis = NULL;
}

/**
 * Methos that return the singleton object of the CCalculation class
 * @return: CCalculation object instance
 */
CCalculations* CCalculations::GetCalculations()
{
    if (m_pThis == NULL)
    {
    	m_pThis = new CCalculations();
    }
    return m_pThis;
}

/**
 * Method to return the GFEM Associated Data to 1D2D/2D2D Connections. The method use the data stored in the input files
 * @return: Result of the operation. OK or KO result
 */
bool CCalculations::Get1D2D_2D2D_GFEM_AssociatedData() {

	bool bReturn = RESULT_KO;

	try {
		//We process all the 2D2D connections to generate the data associated to the GFEM nodes of the connections.
		ListConnections *lstConnections2D2D = CCSVReader::GetCSVReader()->GetAssociativityFile()->GetConnections2D2D();

		if(lstConnections2D2D != NULL && lstConnections2D2D->size() > 0 ) {
			m_pThis->GetGFEMAssociatedData(lstConnections2D2D, TYPE_2D2D);
		}

		//We process all the 1D2D connections to generate the data associated to the GFEM nodes of the connections.
		ListConnections *lstConnections1D2D = CCSVReader::GetCSVReader()->GetAssociativityFile()->GetConnections1D2D();

		if(lstConnections1D2D != NULL && lstConnections1D2D->size() > 0 ) {
			m_pThis->GetGFEMAssociatedData(lstConnections1D2D, TYPE_1D2D);
		}

		bReturn = RESULT_OK;
	}
	catch(std::exception &exc) {
		CLogger::GetLogger()->Log(" <EXCEPTION>: CCalculations::Get1D2D_2D2D_GFEM_AssociatedData " + std::string(exc.what()));
	}

	return bReturn;
}

/**
 * Method to return the GFEM Associated Data. The method use the data stored in the input files
 * @return: Result of the operation. OK or KO result
 */
bool CCalculations::GetGFEMAssociatedData(ListConnections *lstConnections, int dTypeConnection) {

	bool bReturn = RESULT_KO;

	ListIntegerData lstNodesProcessed;

	try {

		if(lstConnections == NULL ||
		  (lstConnections != NULL && lstConnections->size() <= 0)) return bReturn;

		MapGRIDData *mapGridData = CGFEMReader::GetGFEMReader()->getMapGRIDData();

		for(ListConnections::iterator itConn = lstConnections->begin(); itConn != lstConnections->end(); itConn++) {

			if((*itConn)->GetGFEMNodes()->size() <= 0) continue;

			MapGFEMNodes *mapNodes = (*itConn)->GetGFEMNodes();

			for(MapGFEMNodes::iterator itGFEM = mapNodes->begin(); itGFEM != mapNodes->end(); itGFEM++) {

				if((*itGFEM).second->getIdNode() == 33216) {
					int kk = 0;
				}

				if(dTypeConnection == TYPE_1D2D) {

					MapGFEMNodes::iterator itMapGFEMProcessed = m_pThis->GetMapGFEMNodes()->find((*itGFEM).second->getIdNode());

					if(itMapGFEMProcessed != m_pThis->GetMapGFEMNodes()->end()) {
						itGFEM->second = itMapGFEMProcessed->second	;

						continue;
					}
				}

				//We store the processed nodes
				lstNodesProcessed.clear();

				if(CGFEMReader::GetGFEMReader()->getMapCQUAD4Data()->size() > 0) {
					CCQUAD4Node *oNodeQuad4 = CGlobal::FindAssociatedNodeToGFEM((*itGFEM).second->getIdNode(), CGFEMReader::GetGFEMReader()->getMapCQUAD4Data(), lstNodesProcessed);

					while(oNodeQuad4 != NULL && lstNodesProcessed.size() < 2) {

						switch(lstNodesProcessed.size()) {
							case ZERO:
								//We store the data
								(*itGFEM).second->setEid_1(oNodeQuad4->getEID());
								(*itGFEM).second->setZOFFS_1(oNodeQuad4->getZOFFS());
								(*itGFEM).second->setG1_1(oNodeQuad4->getG1());
								(*itGFEM).second->setG2_1(oNodeQuad4->getG2());
								(*itGFEM).second->setG3_1(oNodeQuad4->getG3());
								(*itGFEM).second->setG4_1(oNodeQuad4->getG4());

								break;

							case ONE:
								//Almacenar datos
								(*itGFEM).second->setEid_2(oNodeQuad4->getEID());
								(*itGFEM).second->setZOFFS_2(oNodeQuad4->getZOFFS());
								(*itGFEM).second->setG1_2(oNodeQuad4->getG1());
								(*itGFEM).second->setG2_2(oNodeQuad4->getG2());
								(*itGFEM).second->setG3_2(oNodeQuad4->getG3());
								(*itGFEM).second->setG4_2(oNodeQuad4->getG4());

								break;
							default:
								break;
						}

						lstNodesProcessed.push_back(oNodeQuad4->getEID());

						if(lstNodesProcessed.size() == 2) break;

						oNodeQuad4 = CGlobal::FindAssociatedNodeToGFEM((*itGFEM).second->getIdNode(), CGFEMReader::GetGFEMReader()->getMapCQUAD4Data(), lstNodesProcessed);
					}

					CGlobal::ShowNodeData("Node Processed: ", (*itGFEM).second);
				}

				if(lstNodesProcessed.size() < 2 && CGFEMReader::GetGFEMReader()->getMapCTRIA3Data()->size() > 0) {
					CCTRIA3Node *oNodeTria3 = CGlobal::FindAssociatedNodeToGFEM((*itGFEM).second->getIdNode(), CGFEMReader::GetGFEMReader()->getMapCTRIA3Data(), lstNodesProcessed);

					while(oNodeTria3 != NULL && lstNodesProcessed.size() < 2) {

						switch(lstNodesProcessed.size()) {
							case ZERO:
								//Almacenar datos
								(*itGFEM).second->setEid_1(oNodeTria3->getEID());
								(*itGFEM).second->setZOFFS_1(oNodeTria3->getZOFFS());
								(*itGFEM).second->setG1_1(oNodeTria3->getG1());
								(*itGFEM).second->setG2_1(oNodeTria3->getG2());
								(*itGFEM).second->setG3_1(oNodeTria3->getG3());

								break;
							case ONE:
								//Almacenar datos
								(*itGFEM).second->setEid_2(oNodeTria3->getEID());
								(*itGFEM).second->setZOFFS_2(oNodeTria3->getZOFFS());
								(*itGFEM).second->setG1_2(oNodeTria3->getG1());
								(*itGFEM).second->setG2_2(oNodeTria3->getG2());
								(*itGFEM).second->setG3_2(oNodeTria3->getG3());

								break;
							default:
								break;
						}

						lstNodesProcessed.push_back(oNodeTria3->getEID());

						if(lstNodesProcessed.size() == 2) break;

						oNodeTria3 = CGlobal::FindAssociatedNodeToGFEM((*itGFEM).second->getIdNode(), CGFEMReader::GetGFEMReader()->getMapCTRIA3Data(), lstNodesProcessed);
					}

					CGlobal::ShowNodeData("Node Processed: ", (*itGFEM).second);
				}

				float fZOFFS = 0;

				switch(lstNodesProcessed.size()) {
				case ONE:
					fZOFFS = ((*itGFEM).second->getZOFFS_1() + (*itGFEM).second->getZOFFS_2());
					(*itGFEM).second->setZOFFS(fZOFFS);
					break;
				case TWO:
					fZOFFS = ((*itGFEM).second->getZOFFS_1() + (*itGFEM).second->getZOFFS_2())/2;
					(*itGFEM).second->setZOFFS(fZOFFS);
					break;
				}

				CGlobal::ShowNodeData("Node Processed: ", (*itGFEM).second);

				CGFEMNode *oNodeCalculated = GetGFEMNodeCoordAssociatedData((*itGFEM).second, mapGridData);

				CGlobal::ShowNodeData("Node Processed: ", oNodeCalculated);

				CVector3D *oVectorNormalizedMed = GenetareNormalVector((*itGFEM).second);


				if(oVectorNormalizedMed == NULL) continue;

				(*itGFEM).second->setV3_X1_Norm(oVectorNormalizedMed->getV_X1());
				(*itGFEM).second->setV3_X2_Norm(oVectorNormalizedMed->getV_X2());
				(*itGFEM).second->setV3_X3_Norm(oVectorNormalizedMed->getV_X3());

				CGlobal::ShowNodeData("Node Processed: ", (*itGFEM).second);

				CreateNewNode1((*itGFEM).second, NULL);
				CreateNewNode2((*itGFEM).second, oVectorNormalizedMed);

				CGlobal::ShowNodeData("Node Processed: ", (*itGFEM).second);

				CreateKinematicCoupling((*itGFEM).second);

				CGlobal::ShowNodeData("Node Processed: ", (*itGFEM).second);

				CreateNewNode3(*(*itGFEM).second, (*itConn));

				CGlobal::ShowNodeData("Node Processed: ", (*itGFEM).second);

				CreaterEQuationCard((*itGFEM).second);

				CGlobal::ShowNodeData("Node Processed: ", (*itGFEM).second);

				if(dTypeConnection == TYPE_2D2D) {
					MapGFEMNodes::iterator itMapGFEMProcessed = m_pThis->GetMapGFEMNodes()->begin();

					m_pThis->GetMapGFEMNodes()->insert(itMapGFEMProcessed, std::pair<int, CGFEMNode *>((*itGFEM).second->getIdNode(),(*itGFEM).second));
				}

				CGlobal::ShowNodeData("Node Processed: ", (*itGFEM).second);
			}

			m_pThis->CreateT3D2ABAQUSData((*itConn));
		}

		bReturn = RESULT_OK;
	}

	catch(std::exception &exc) {
		CLogger::GetLogger()->Log(" <EXCEPTION>: CCalculations::Get2D2DAssociatedData " + std::string(exc.what()));
	}

	return bReturn;
}


/**
 * Method that implement the operation to generate the GFEM Node Coordinates Associated Data
 * @param: oGFEMNode: Node to process
 * @param: mapGridData: Map with GRID data stored in the GFEN files
 * @return: GFEM Node with the Node Coord. Associated Data modified
 */
CGFEMNode * CCalculations::GetGFEMNodeCoordAssociatedData(CGFEMNode *nodeGFEM, MapGRIDData *mapGridData) {

	CGFEMNode *oNodeReturn = NULL;
	MapGRIDData::iterator itGridData;

	if(nodeGFEM == NULL || mapGridData == NULL)  return oNodeReturn;

	try {
		if(nodeGFEM->getG1_1() != 0 && nodeGFEM->getG2_1() != 0 && nodeGFEM->getG3_1() != 0 )
		{
			//We process G1_1 Node Data
			itGridData = mapGridData->find(nodeGFEM->getG1_1());
			if(itGridData != mapGridData->end()) {

				nodeGFEM->setG1_1_CP(itGridData->second->getCP());
				nodeGFEM->setG1_1_X1(itGridData->second->getCoord_X1());
				nodeGFEM->setG1_1_X2(itGridData->second->getCoord_X2());
				nodeGFEM->setG1_1_X3(itGridData->second->getCoord_X3());
			}

			//We process G2_1 Node Data
			itGridData = mapGridData->find(nodeGFEM->getG2_1());
			if(itGridData != mapGridData->end()) {

				nodeGFEM->setG2_1_CP(itGridData->second->getCP());
				nodeGFEM->setG2_1_X1(itGridData->second->getCoord_X1());
				nodeGFEM->setG2_1_X2(itGridData->second->getCoord_X2());
				nodeGFEM->setG2_1_X3(itGridData->second->getCoord_X3());
			}

			//We process G3_1 Node Data
			itGridData = mapGridData->find(nodeGFEM->getG3_1());
			if(itGridData != mapGridData->end()) {

				nodeGFEM->setG3_1_CP(itGridData->second->getCP());
				nodeGFEM->setG3_1_X1(itGridData->second->getCoord_X1());
				nodeGFEM->setG3_1_X2(itGridData->second->getCoord_X2());
				nodeGFEM->setG3_1_X3(itGridData->second->getCoord_X3());
			}
		}

		if(nodeGFEM->getG1_2() != 0 && nodeGFEM->getG2_2() != 0 && nodeGFEM->getG3_2() != 0 ) {

			itGridData = mapGridData->find(nodeGFEM->getG1_2());

			//We process G1_2 Node Data
			if(itGridData != mapGridData->end()) {

				nodeGFEM->setG1_2_CP(itGridData->second->getCP());
				nodeGFEM->setG1_2_X1(itGridData->second->getCoord_X1());
				nodeGFEM->setG1_2_X2(itGridData->second->getCoord_X2());
				nodeGFEM->setG1_2_X3(itGridData->second->getCoord_X3());
			}

			itGridData = mapGridData->find(nodeGFEM->getG2_2());

			//We process G2_2 Node Data
			if(itGridData != mapGridData->end()) {

				nodeGFEM->setG2_2_CP(itGridData->second->getCP());
				nodeGFEM->setG2_2_X1(itGridData->second->getCoord_X1());
				nodeGFEM->setG2_2_X2(itGridData->second->getCoord_X2());
				nodeGFEM->setG2_2_X3(itGridData->second->getCoord_X3());
			}

			itGridData = mapGridData->find(nodeGFEM->getG3_2());

			//We process G3_2 Node Data
			if(itGridData != mapGridData->end()) {

				nodeGFEM->setG3_2_CP(itGridData->second->getCP());
				nodeGFEM->setG3_2_X1(itGridData->second->getCoord_X1());
				nodeGFEM->setG3_2_X2(itGridData->second->getCoord_X2());
				nodeGFEM->setG3_2_X3(itGridData->second->getCoord_X3());
			}
		}

		oNodeReturn = nodeGFEM;
	}
	catch(std::exception &exc) {
		CLogger::GetLogger()->Log(" <EXCEPTION>: CCalculations::GetGFEMNodeCoordAssociatedData " + std::string(exc.what()));
	}

	return oNodeReturn;
}

/**
 * Method that implement the operation to generate the normal plain vector
 * @param: oGFEMNode: Node to process
 * @param: IdVector: IdVector to generate
 * @return: Vector 3D normalized generated in this method
 */
CVector3D * CCalculations::GenetareNormalPlainVector(CGFEMNode *nodeGFEM, int IdVector) {

	CVector3D *vect3DReturn = NULL;

	if(nodeGFEM == NULL) return vect3DReturn;

	try {

		vect3DReturn = new CVector3D();

		switch(IdVector) {
			case ONE:
				vect3DReturn->setV_X1(nodeGFEM->getG2_1_X1() - nodeGFEM->getG1_1_X1());
				vect3DReturn->setV_X2(nodeGFEM->getG2_1_X2() - nodeGFEM->getG1_1_X2());
				vect3DReturn->setV_X3(nodeGFEM->getG2_1_X3() - nodeGFEM->getG1_1_X3());
				break;
			case TWO:
				vect3DReturn->setV_X1(nodeGFEM->getG3_1_X1() - nodeGFEM->getG1_1_X1());
				vect3DReturn->setV_X2(nodeGFEM->getG3_1_X2() - nodeGFEM->getG1_1_X2());
				vect3DReturn->setV_X3(nodeGFEM->getG3_1_X3() - nodeGFEM->getG1_1_X3());
				break;
			case THREE:
				vect3DReturn->setV_X1(nodeGFEM->getG2_2_X1() - nodeGFEM->getG1_2_X1());
				vect3DReturn->setV_X2(nodeGFEM->getG2_2_X2() - nodeGFEM->getG1_2_X2());
				vect3DReturn->setV_X3(nodeGFEM->getG2_2_X3() - nodeGFEM->getG1_2_X3());
				break;
			case FOUR:
				vect3DReturn->setV_X1(nodeGFEM->getG3_2_X1() - nodeGFEM->getG1_2_X1());
				vect3DReturn->setV_X2(nodeGFEM->getG3_2_X2() - nodeGFEM->getG1_2_X2());
				vect3DReturn->setV_X3(nodeGFEM->getG3_2_X3() - nodeGFEM->getG1_2_X3());
				break;
			default:
				break;
		}

		vect3DReturn->Normalize();
	}
	catch(std::exception &exc) {

		vect3DReturn = NULL;
		CLogger::GetLogger()->Log(" <EXCEPTION>: CCalculations::GenetareNormalPlainVector " + std::string(exc.what()));
	}

	return vect3DReturn;
}

/**
 * Method that return the vector product of two vectors passed as parameter
 * @param: oVector1: Vector One
 * @param: oVector2: Vector Two
 * @return: Result of the vector product
 */
CVector3D * CCalculations::GenerateVectorProduct(CVector3D *oVector1, CVector3D *oVector2) {

	CVector3D *oVector3DReturn = NULL;

	if(oVector1 == NULL || oVector2 == NULL) return oVector3DReturn;

	try {

		oVector3DReturn = new CVector3D();

		float Coord_X1 = (oVector1->getV_X2() * oVector2->getV_X3()) - (oVector1->getV_X3() * oVector2->getV_X2());
		float Coord_X2=  (oVector1->getV_X3() * oVector2->getV_X1()) - (oVector1->getV_X1() * oVector2->getV_X3());
		float Coord_X3 = (oVector1->getV_X1() * oVector2->getV_X2()) - (oVector1->getV_X2() * oVector2->getV_X1());

		oVector3DReturn->setV_X1(Coord_X1);
		oVector3DReturn->setV_X2(Coord_X2);
		oVector3DReturn->setV_X3(Coord_X3);

		oVector3DReturn->Normalize();
	}
	catch(std::exception &exc) {
		oVector3DReturn = NULL;
		CLogger::GetLogger()->Log(" <EXCEPTION>: CCalculations::GenerateVectorProduct " + std::string(exc.what()));
	}

	return oVector3DReturn;
}

/**
 * Method that return the normal vector product the vector passed as parameter
 * @param: oVector: Vector to normalize
 * @return: Vector normalized
 */
CVector3D * CCalculations::GenetareNormalVector(CGFEMNode *nodeGFEM) {

	if(nodeGFEM == NULL) return NULL;

	CVector3D *oNormalVectorMed = new CVector3D();

	CVector3D *oNormalVector1_1 = NULL;
	CVector3D *oNormalVector2_1 = NULL;
	CVector3D *oVectorProductE_1 = NULL;

	CVector3D *oNormalVector1_2 = NULL;
	CVector3D *oNormalVector2_2 = NULL;
	CVector3D *oVectorProductE_2 = NULL;

	try {

		bool bProcessNodes = !(((nodeGFEM->getG1_1_X1() == 0 && nodeGFEM->getG1_1_X2() == 0 && nodeGFEM->getG1_1_X3() == 0) &&
				   	    	    (nodeGFEM->getG2_1_X1() == 0 && nodeGFEM->getG2_1_X2() == 0 && nodeGFEM->getG2_1_X3() == 0)));

		if(bProcessNodes) {

			oNormalVector1_1 = GenetareNormalPlainVector(nodeGFEM, ONE);
			oNormalVector2_1 = GenetareNormalPlainVector(nodeGFEM, TWO);
			oVectorProductE_1 = GenerateVectorProduct(oNormalVector1_1, oNormalVector2_1);
		}

		bProcessNodes = !(((nodeGFEM->getG1_2_X1() == 0 && nodeGFEM->getG1_2_X2() == 0 && nodeGFEM->getG1_2_X3() == 0) &&
				   	       (nodeGFEM->getG2_2_X1() == 0 && nodeGFEM->getG2_2_X2() == 0 && nodeGFEM->getG2_2_X3() == 0)));

		if(bProcessNodes) {

			oNormalVector1_2 = GenetareNormalPlainVector(nodeGFEM, THREE);
			oNormalVector2_2 = GenetareNormalPlainVector(nodeGFEM, FOUR);
			oVectorProductE_2 = GenerateVectorProduct(oNormalVector1_2, oNormalVector2_2);
		}

		if(oVectorProductE_1 == NULL && oVectorProductE_2 == NULL) {
			return NULL;
		}

		if(oVectorProductE_1 != NULL && oVectorProductE_2 != NULL) {

			oNormalVectorMed->setV_X1((oVectorProductE_1->getV_X1() + oVectorProductE_2->getV_X1())/2);
			oNormalVectorMed->setV_X2((oVectorProductE_1->getV_X2() + oVectorProductE_2->getV_X2())/2);
			oNormalVectorMed->setV_X3((oVectorProductE_1->getV_X3() + oVectorProductE_2->getV_X3())/2);
			oNormalVectorMed->Normalize();
		}
		else {

			oVectorProductE_1->Normalize();
			oNormalVectorMed = oVectorProductE_1;
		}
	}
	catch(std::exception &exc) {
		oNormalVectorMed = NULL;
		CLogger::GetLogger()->Log(" <EXCEPTION>: CCalculations::GenetareNormalVector " + std::string(exc.what()));
	}

	return oNormalVectorMed;
}

/**
 * Method that perform the operation to generate a new NODE1 data
 * @param: nodeGFEM: GEFM Node to process
 * @param: oVector3D: Vector3D associated
 * @return: GRID data generated
 */
CGridNode * CCalculations::CreateNewNode1(CGFEMNode *nodeGFEM, CVector3D *oVector3D) {

	CGridNode *oGridReturn = NULL;

	try {

		if(nodeGFEM->getGridNode() == NULL || oVector3D == NULL) return oGridReturn;

		oGridReturn = nodeGFEM->getGridNode();
		oGridReturn =  nodeGFEM->getGridNode()->LocalToGlobal();
		oGridReturn->setCD(oGridReturn->getCD());

		nodeGFEM->setNode_2_ID(oGridReturn->getIdNode());
		nodeGFEM->setNode_2_CP(oGridReturn->getCP());
		nodeGFEM->setNode_2_X1(oGridReturn->getCoord_X1());
		nodeGFEM->setNode_2_X2(oGridReturn->getCoord_X2());
		nodeGFEM->setNode_2_X3(oGridReturn->getCoord_X3());
		nodeGFEM->setNode_2_CD(oGridReturn->getCD());

		std::string strNode_1_Card = std::to_string(oGridReturn->getIdNode()) 	+ "," +
									 std::to_string(oGridReturn->getCoord_X1()) + "," +
									 std::to_string(oGridReturn->getCoord_X2()) + "," +
									 std::to_string(oGridReturn->getCoord_X3());

		nodeGFEM->setNODE_1_CARD(strNode_1_Card);
	}
	catch(std::exception &exc) {
		oGridReturn = NULL;

		CLogger::GetLogger()->Log(" <EXCEPTION>: CCalculations::CreateNewNode1 " + std::string(exc.what()));
	}

	return oGridReturn;
}

/**
 * Method that perform the operation to generate a new NODE2 data
 * @param: nodeGFEM: GEFM Node to process
 * @param: oVector3D: Vector3D associated
 * @return: GRID data generated
 */
CGridNode * CCalculations::CreateNewNode2(CGFEMNode *nodeGFEM, CVector3D *oVector3D) {

	CGridNode *oGridReturn = NULL;

	try {

		if(nodeGFEM->getGridNode() == NULL || oVector3D == NULL)  return oGridReturn;

		oGridReturn = new CGridNode();

		oGridReturn->setIdNode(nodeGFEM->getIdNode() + CGlobal::GetGlobal()->getOFFSET_NODE2_ID_GFEM());
		oGridReturn->setCP(ZERO);

		CGridNode *oGridGlobal =  nodeGFEM->getGridNode()->LocalToGlobal();

		float fValueX1 = oGridGlobal->getCoord_X1() + (nodeGFEM->getZOFFS() * oVector3D->getV_X1());
		oGridReturn->setCoord_X1(fValueX1);

		float fValueX2 = oGridGlobal->getCoord_X2() + (nodeGFEM->getZOFFS() * oVector3D->getV_X2());
		oGridReturn->setCoord_X2(fValueX2);

		float fValueX3 = oGridGlobal->getCoord_X3() + (nodeGFEM->getZOFFS() * oVector3D->getV_X3());
		oGridReturn->setCoord_X3(fValueX3);

		oGridReturn->setCD(nodeGFEM->getGridNode()->getCD());

		nodeGFEM->setNode_2_ID(oGridReturn->getIdNode());
		nodeGFEM->setNode_2_CP(oGridReturn->getCP());
		nodeGFEM->setNode_2_X1(oGridReturn->getCoord_X1());
		nodeGFEM->setNode_2_X2(oGridReturn->getCoord_X2());
		nodeGFEM->setNode_2_X3(oGridReturn->getCoord_X3());
		nodeGFEM->setNode_2_CD(oGridReturn->getCD());

		std::string strNode_2_Card = std::to_string(oGridReturn->getIdNode()) 	+ "," +
									 std::to_string(oGridReturn->getCoord_X1()) + "," +
									 std::to_string(oGridReturn->getCoord_X2()) + "," +
									 std::to_string(oGridReturn->getCoord_X3());
		nodeGFEM->setNODE_2_CARD(strNode_2_Card);

	}
	catch(std::exception &exc) {

		oGridReturn = NULL;
		CLogger::GetLogger()->Log(" <EXCEPTION>: CCalculations::CreateNewNode2 " + std::string(exc.what()));
	}

	return oGridReturn;
}

/**
 * Method that perform the operation to generate the KINEMATIC_COUPLING_1_2 data associated to the node passed as parameter
 * @param: nodeGFEM: GEFM Node to process
 * @return: KINEMATIC_COUPLING_1_2 data generated
 */
bool CCalculations::CreateKinematicCoupling(CGFEMNode *nodeGFEM) {

	bool bReturn = RESULT_KO;

	if(nodeGFEM == NULL) return bReturn;

	try {
		std::string strKinematicCoupling_1_2_CARD = "*KINEMATIC COUPLING,REF NODE="+std::to_string(nodeGFEM->getIdNode()) +"\n" +
													CGlobal::PadLeft(std::to_string(nodeGFEM->getNode_2_ID()), 10, ' ') + ",1,6";

		nodeGFEM->setKINEMATIC_COUPLING_1_2_CARD(strKinematicCoupling_1_2_CARD);

		bReturn = RESULT_OK;

	}
	catch(std::exception &exc) {
		CLogger::GetLogger()->Log(" <EXCEPTION>: CCalculations::CreateKinematicCoupling " + std::string(exc.what()));
	}

	return bReturn;
}

/**
 * Method that perform the operation to Create the Node3 values
 * @param: connection CConnection object with the set nodes to process
 * @return: Result of the operation
 */
bool CCalculations::CreateNewNode3(CGFEMNode &oNodeGFEM, CConnection *connection) {

	bool bReturn = RESULT_KO;

	float fDistance = INFINITE;
	float fDistanceAux = ZERO;

	std::string strKey = STRING_EMPTY;
	CDFEMObject *oDFEMNodeTo = NULL;
	CDFEMObject *oDFEMNodeMinor = NULL;

	//Calculate The distance between two nodes oNodeGFEM and oNodeDFEM

	try {

		MapDFEMObjects *mapDFEMObjects = NULL;

		if(CGlobal::GetGlobal()->getFormatData() == FORMAT_1) {
			mapDFEMObjects = CDFEMReader::GetDFEMReader()->getMapDFEMObjects();
		}
		else {
			mapDFEMObjects = CGlobalDFEMReader::GetCGlobalDFEMReader()->getMapGlobalDFEMObjects();
		}

		fDistance = INFINITE;
		fDistanceAux = ZERO;

		for(MapDFEMNodes::iterator itMapSecond = connection->GetDFEMNodes()->begin();
								   itMapSecond != connection->GetDFEMNodes()->end();
								   itMapSecond++) {

			CDFEMNode *oNodeDFEM =(*itMapSecond).second;

			MapDFEMObjects::iterator itDFEMObject = mapDFEMObjects->find(oNodeDFEM->getStrIdNode());

			if(itDFEMObject != mapDFEMObjects->end()) {

				oDFEMNodeTo = (*itDFEMObject).second;

				std::string strKey = (*itDFEMObject).first;

				if(oNodeGFEM.getGridNode() != NULL &&(oDFEMNodeTo != NULL)) {

					CCoordinate3D *oCoordFrom = new  CCoordinate3D();
					oCoordFrom->setX(oNodeGFEM.getGridNode()->getCoord_X1());
					oCoordFrom->setY(oNodeGFEM.getGridNode()->getCoord_X2());
					oCoordFrom->setZ(oNodeGFEM.getGridNode()->getCoord_X3());

					CCoordinate3D *oCoordTo = new  CCoordinate3D();
					oCoordTo->setX(oDFEMNodeTo->getCoord_X());
					oCoordTo->setY(oDFEMNodeTo->getCoord_Y());
					oCoordTo->setZ(oDFEMNodeTo->getCoord_Z());

					fDistanceAux = CGlobal::GetDistance(oCoordFrom, oCoordTo);

					if(fDistanceAux < fDistance) {
						fDistance = fDistanceAux;

						oDFEMNodeMinor = oDFEMNodeTo;
					}
				}
			}
		}


		float fDistanceNodeToProject = CalculateDistanceNodeProjectToDFEMPlain(&oNodeGFEM, oDFEMNodeMinor);
		oNodeGFEM.setD(fDistanceNodeToProject);

		long lNODE3_ID = oNodeGFEM.getIdNode() + CGlobal::GetGlobal()->getOFFSET_NODE3_ID_GFEM();
		oNodeGFEM.setNode_3_ID(lNODE3_ID);

		oNodeGFEM.setNode_3_CP(ZERO);
		float fNode3_X1 = oNodeGFEM.getNode_2_X1() + (fDistanceNodeToProject * oNodeGFEM.getV3_X1_Norm());
		oNodeGFEM.setNode_3_X1(fNode3_X1);

		float fNode3_X2 = oNodeGFEM.getNode_2_X2() + (fDistanceNodeToProject * oNodeGFEM.getV3_X2_Norm());
		oNodeGFEM.setNode_3_X2(fNode3_X2);

		float fNode3_X3 = oNodeGFEM.getNode_2_X3() + (fDistanceNodeToProject * oNodeGFEM.getV3_X3_Norm());
		oNodeGFEM.setNode_3_X3(fNode3_X3);

		oNodeGFEM.setNode_3_CD(oNodeGFEM.getGridNode()->getCD());

		std::string strNode_3_Card = std::to_string(lNODE3_ID) 	+ "," +
									 std::to_string(fNode3_X1) + "," +
									 std::to_string(fNode3_X2) + "," +
									 std::to_string(fNode3_X3);

		oNodeGFEM.setNODE_3_CARD(strNode_3_Card);

		bReturn = RESULT_OK;
	}
	catch(std::exception &exc) {
		CLogger::GetLogger()->Log(" <EXCEPTION>: CCalculations::ProcessNodes2D2DConnections " + std::string(exc.what()));
	}

	return bReturn;
}

/**
 * Method that perform the operation to Calculate the Distance between the Node Project and the DFEM Plain
 * @param: oNodeGFEM : Begin Node
 * @param: nodeDFEM: End Node
 * @return: Distance value
 */
float CCalculations::CalculateDistanceNodeProjectToDFEMPlain(CGFEMNode *nodeGFEM, CDFEMObject *nodeDFEM) {

	float fDistanceNodeToProject = ZERO;

	try {

		float a = nodeGFEM->getV3_X1_Norm();
		float X1 = nodeGFEM->getNode_2_X1();
		float X0 = nodeDFEM->getCoord_X();
		float factorOne = a  * (X1 - X0);

		float b = nodeGFEM->getV3_X2_Norm();
		float Y1 = nodeGFEM->getNode_2_X2();
		float Y0 = nodeDFEM->getCoord_Y();
		float factorTwo = b  * (Y1 - Y0);

		float c = nodeGFEM->getV3_X3_Norm();
		float Z1 = nodeGFEM->getNode_2_X3();
		float Z0 = nodeDFEM->getCoord_Z();
		float factorThree = c  * (Z1 - Z0);

		float fNumerator = std::abs(factorOne + factorTwo + factorThree);
	    float fDenominator = sqrt(pow(a, 2) + pow(b, 2) + pow(c, 2)) ;

		fDistanceNodeToProject = (fNumerator /  fDenominator);
	}

	catch(std::exception &exc) {
		CLogger::GetLogger()->Log(" <EXCEPTION>: CCalculations::CalculateDistanceNodeProjectToDFEMPlain " + std::string(exc.what()));
	}

	return fDistanceNodeToProject;
}

/**
 * Method that perform the operation to create an equation card data
 * @param: nodeGFEM: node GFEN used for the equation generation
 * @return: Result of de operation
 */
bool CCalculations::CreaterEQuationCard(CGFEMNode *nodeGFEM) {

	bool bReturn = RESULT_KO;

	try {
		std::string str_EQUATIONCARD = "*EQUATION\n"
									   "2\n"+
									   std::to_string(nodeGFEM->getNode_3_ID()) + ",1,-1.0," + 	std::to_string(nodeGFEM->getNode_2_ID()) + ",1,1.0" + "\n" +
									   "2\n"+
									   std::to_string(nodeGFEM->getNode_3_ID()) + ",2,-1.0," + 	std::to_string(nodeGFEM->getNode_2_ID()) + ",2,1.0" + "\n" +
									   "2\n"+
	   								   std::to_string(nodeGFEM->getNode_3_ID()) + ",3,-1.0," + 	std::to_string(nodeGFEM->getNode_2_ID()) + ",3,1.0" + "\n" +
									   "2\n"+
									   std::to_string(nodeGFEM->getNode_3_ID()) + ",4,-1.0," + 	std::to_string(nodeGFEM->getNode_2_ID()) + ",4,1.0" + "\n" +
									   "2\n"+
									   std::to_string(nodeGFEM->getNode_3_ID()) + ",5,-1.0," + 	std::to_string(nodeGFEM->getNode_2_ID()) + ",5,1.0" + "\n" +
									   "2\n"+
									   std::to_string(nodeGFEM->getNode_3_ID()) + ",6,-1.0," + 	std::to_string(nodeGFEM->getNode_2_ID()) + ",6,1.0";

		nodeGFEM->setEQUATION_CARD(str_EQUATIONCARD);

		bReturn = RESULT_OK;
	}
	catch(std::exception &exc) {
		CLogger::GetLogger()->Log(" <EXCEPTION>: CCalculations::CreaterEQuationCard " + std::string(exc.what()));
	}

	return bReturn;
}

/**
 * Method that perform the operation to Write T3D2 Element Between GFEM Projected Nodes
 * @param: strPathFile: Path of the output file
 * @return: Result of de operation
 */
std::string CCalculations::GetT3D2ElementBetweenGFEMProjectedNodes() {
	bool bReturn =  RESULT_KO;
	std::string strResult = STRING_EMPTY;

	try {

		strResult = CGlobal::GetGlobal()->LoadT3D2ElementBetweenGFEMProjectedNodes();
	}
	catch(std::exception &exc) {
		CLogger::GetLogger()->Log(" <EXCEPTION>: CCalculations::GetT3D2ElementBetweenGFEMProjectedNodes " + std::string(exc.what()));
	}

	return strResult;
}

/**
 * Method that perform the operation to Write Write SOLID SECTION Cards
 * @param: strPathFile: Path of the output file
 * @return: Result of the operation
 */
std::string CCalculations::GetSOLIDSECTION_Cards() {

	std::string strReturn = STRING_EMPTY;

	try {
		ListConnections *lstConnections2D2D = CCSVReader::GetCSVReader()->GetAssociativityFile()->GetConnections2D2D();

		if((lstConnections2D2D ) != NULL && lstConnections2D2D->size() > 0 ) {

			for(ListConnections::iterator itConn = lstConnections2D2D->begin(); itConn != lstConnections2D2D->end(); itConn++) {

				if((*itConn)->getTieArea() == 0) continue;

				strReturn += CGlobal::GetGlobal()->Create_SOLIDSECTION_Card((*itConn)->getTieArea()) + "\n**\n**\n";
			}
		}
	}
	catch(std::exception &exc) {
		CLogger::GetLogger()->Log(" <EXCEPTION>: CCalculations::GetSOLIDSECTION_Cards " + std::string(exc.what()));
	}

	return strReturn;
}

/**
 * Method that perform the operation to Create T3D2 ABAQUS Data
 * @param: oConnection: Path of the output file
 * @return: Result of the operation
 */
bool CCalculations::CreateT3D2ABAQUSData(CConnection *oConnection) {

	bool bReturn =  RESULT_KO;
	ListPairNodes *lstPairNodes = new ListPairNodes();

	try {

		if((oConnection == NULL) ||
		   (oConnection != NULL && oConnection->GetGFEMNodes()->size() <= 0)) return bReturn;

		MapGFEMNodes *mapNodes = oConnection->GetGFEMNodes();

		for(MapGFEMNodes::iterator itGFEM = mapNodes->begin(); itGFEM != mapNodes->end(); itGFEM++) {

			PairNodes *pairNode1 = NULL;
			PairNodes *pairNode2 = NULL;

			pairNode1 = ProcessAssociatedData(mapNodes,
											  itGFEM->second->getG1_1(),
											  itGFEM->second->getG2_1(),
											  itGFEM->second->getG3_1(),
											  itGFEM->second->getG4_1());

			if(pairNode1 != NULL) {
				if(!CGlobal::GetGlobal()->ExistInList(lstPairNodes, pairNode1)) {

					lstPairNodes->push_back(pairNode1);
				}
			}

			if(itGFEM->second->getG1_2() == 0 &&
			   itGFEM->second->getG2_2() == 0 &&
			   itGFEM->second->getG3_2() == 0 &&
			   itGFEM->second->getG4_2() == 0) {

				;
			}
			else {
				pairNode2 = ProcessAssociatedData(mapNodes,
												  itGFEM->second->getG1_2(),
												  itGFEM->second->getG2_2(),
												  itGFEM->second->getG3_2(),
												  itGFEM->second->getG4_2());
			}

			if(pairNode2 != NULL) {

				if(!CGlobal::GetGlobal()->ExistInList(lstPairNodes, pairNode2)) {

					lstPairNodes->push_back(pairNode2);
				}
			}
		}

		std::string strResult = "*ELEMENT,TYPE=T3D2,ELSET=Integr_elms_truss_Tie_Area_" + std::to_string(oConnection->getTieArea()) + "\n";
		std::string strAux = STRING_EMPTY;

		for(ListPairNodes::iterator itPairs = lstPairNodes->begin(); itPairs != lstPairNodes->end(); itPairs++) {

			int dIDNode3_1 = UNDEFINED;
			MapGFEMNodes::iterator itGFem = mapNodes->find((*itPairs)->first);

			if(itGFem != mapNodes->end()) {
				dIDNode3_1 = itGFem->second->getNode_3_ID();
			}

			itGFem = mapNodes->find((*itPairs)->second);

			int dIDNode3_2 = UNDEFINED;
			if(itGFem != mapNodes->end()) {
				dIDNode3_2 = itGFem->second->getNode_3_ID();
			}

			int dOFFSETValue = m_pThis->getT3D2OFFSET();
			strAux = strAux + std::to_string(dOFFSETValue++) + ", " + std::to_string(dIDNode3_1) + ", " + std::to_string(dIDNode3_2) + "\n";
			m_pThis->setT3D2OFFSET(dOFFSETValue);
		}

		oConnection->setStrT3D2Abaqus(strResult + strAux);

		CGlobal::GetGlobal()->FreeMemory(lstPairNodes);
		delete lstPairNodes;
		lstPairNodes = NULL;

		bReturn =  RESULT_OK;
	}
	catch(std::exception &exc) {
		CLogger::GetLogger()->Log(" <EXCEPTION>: CCalculations::CreateT3D2ABAQUSData " + std::string(exc.what()));
	}

	return bReturn;
}

/**
 * Method that process the associated data to calculate the pairs nodes adjacents
 * @param: mapNodes: map with the nodes to process
 * @param: dValueG1: Value of the G1 Node
 * @param: dValueG2: Value of the G2 Node
 * @param: dValueG3: Value of the G3 Node
 * @param: dValueG4: Value of the G4 Node
 * @return: PairNodes adjacent
 */
PairNodes * CCalculations::ProcessAssociatedData(MapGFEMNodes *mapNodes, int dValueG1, int dValueG2, int dValueG3, int dValueG4) {

	bool bReturn = RESULT_KO;
	int dNode1 = UNDEFINED;
	int dNode2 = UNDEFINED;
	bool bLocated = false;

	PairNodes *pairNodes = NULL;
	MapGFEMNodes::iterator itMapNodes;

	if(dValueG1 == ZERO && dValueG2 == ZERO && dValueG3 == ZERO && dValueG4 == ZERO) return pairNodes;


	try {

		if(dValueG1 != 0) {
			itMapNodes = mapNodes->find(dValueG1);
			if(itMapNodes != mapNodes->end()) {
				dNode1 = dValueG1;
			}
		}

		if(dValueG2 != 0) {
			itMapNodes = mapNodes->find(dValueG2);

			if(itMapNodes != mapNodes->end()) {
				if(dNode1 == UNDEFINED) {
					dNode1 = dValueG2;
				}
				else {
					dNode2 = dValueG2;
					bLocated = true;
				}
			}
		}

		if(dValueG3 != 0 && !bLocated) {
			itMapNodes = mapNodes->find(dValueG3);
			if(itMapNodes != mapNodes->end()) {
				if(dNode1 == UNDEFINED) {
					dNode1 = dValueG3;
				}
				else {
					dNode2 = dValueG3;
					bLocated = true;
				}
			}
		}

		if(dValueG4 != 0 && !bLocated) {
			itMapNodes = mapNodes->find(dValueG4);
			if(itMapNodes != mapNodes->end()) {
				if(dNode1 == UNDEFINED) {
					dNode1 = dValueG4;
				}
				else {
					dNode2 = dValueG4;
					bLocated = true;
				}
			}
		}

		if(dNode1 != UNDEFINED && dNode2 != UNDEFINED) {

			pairNodes = new PairNodes();

			CGlobal::GetGlobal()->Swap(dNode1, dNode2);

			pairNodes->first = dNode1;
			pairNodes->second = dNode2;
		}
	}
	catch(std::exception &exc) {
		pairNodes = NULL;
		CLogger::GetLogger()->Log(" <EXCEPTION>: CCalculations::ProcessAssociatedData " + std::string(exc.what()));
	}

	return pairNodes;
}

/**
 * Method that make the surface With T3D2 Elements
 * @param: strPathFile: Path of the output file
 * @return: Return the string data generated (for test)
 */
std::string CCalculations::GetSurfaceWithT3D2Elements() {
	std::string strReturn = STRING_EMPTY;

	try {
		ListConnections *lstConnections2D2D = CCSVReader::GetCSVReader()->GetAssociativityFile()->GetConnections2D2D();

		if((lstConnections2D2D ) != NULL && lstConnections2D2D->size() > 0 ) {

			for(ListConnections::iterator itConn = lstConnections2D2D->begin(); itConn != lstConnections2D2D->end(); itConn++) {

				if((*itConn)->getTieArea() == 0) continue;

				strReturn += CGlobal::GetGlobal()->Create_Surface_T3D2((*itConn)->getTieArea()) + "\n**\n**\n";
			}
		}
	}
	catch(std::exception &exc) {

		CLogger::GetLogger()->Log(" <EXCEPTION>: CCalculations::GetSurfaceWithT3D2Elements " + std::string(exc.what()));
	}

	return strReturn;
}

/**
 * Method that perform the operation to Write Surface NSET
 * @param: strPathFile: Path of the output file
 * @return: Result of the operation
 */
std::string CCalculations::GetSurfaceNSET() {
	std::string strReturn = STRING_EMPTY;

	try {
		ListConnections *lstConnections2D2D = CCSVReader::GetCSVReader()->GetAssociativityFile()->GetConnections2D2D();

		if((lstConnections2D2D ) != NULL && lstConnections2D2D->size() > 0 ) {

			for(ListConnections::iterator itConn = lstConnections2D2D->begin(); itConn != lstConnections2D2D->end(); itConn++) {

				if((*itConn)->getTieArea() == 0) continue;

				strReturn += CGlobal::GetGlobal()->Create_Surface_NSET((*itConn)) + "\n";
			}
		}
	}
	catch(std::exception &exc) {

		CLogger::GetLogger()->Log(" <EXCEPTION>: CCalculations::GetSurfaceNSET " + std::string(exc.what()));
	}

	return strReturn;
}


/**
 * Method that perform the operation to Write TIE Card
 * @param: strPathFile: Path of the output file
 * @return: Result of the operation
 */
std::string CCalculations::GetTIECard() {

	std::string strReturn = STRING_EMPTY;

	try {
		ListConnections *lstConnections2D2D = CCSVReader::GetCSVReader()->GetAssociativityFile()->GetConnections2D2D();

		if((lstConnections2D2D ) != NULL && lstConnections2D2D->size() > 0 ) {

			for(ListConnections::iterator itConn = lstConnections2D2D->begin(); itConn != lstConnections2D2D->end(); itConn++) {

				if((*itConn)->getTieArea() == 0) continue;

				strReturn += CGlobal::GetGlobal()->Create_TIE((*itConn)) + "\n";
			}
		}
	}
	catch(std::exception &exc) {

		CLogger::GetLogger()->Log(" <EXCEPTION>: CCalculations::GetTIECard " + std::string(exc.what()));
	}

	return strReturn;
}


/**
 * Method to return the Associated Data to the segments of the 1D2D connections. The method use the data stored in the input files
 * @return: Result of the operation. OK or KO result
 */
bool CCalculations::Get1D2DAssociatedData() {
	bool bReturn = RESULT_KO;

	try {

		ListConnections *lstConnections1D2D = CCSVReader::GetCSVReader()->GetAssociativityFile()->GetConnections1D2D();

		//We process all the 1D2D connections to generate the data associated to the DFEM nodes of the connections.
		if((lstConnections1D2D ) != NULL && lstConnections1D2D->size() > 0 ) {

			for(ListConnections::iterator itConn = lstConnections1D2D->begin(); itConn != lstConnections1D2D->end(); itConn++) {

				float Sum_Ai 		= 0;
				float Sum_Ai_xGi  	= 0;
				float Sum_Ai_yGi 	= 0;
				float Sum_Ai_zGi 	= 0;

				if((*itConn)->GetMapSegments()->size() <= 0) continue;

				MapSegments *mapSegments = (*itConn)->GetMapSegments();

				if((*itConn)->getIdConnection() == 8) {
					int kk = 0;
				}

				for(MapSegments::iterator itSegment = mapSegments->begin(); itSegment != mapSegments->end(); itSegment++) {

					CSegment *oSegment = (*itSegment).second;

					//Revisar esto y sacar trazas
					m_pThis->ProcessSegment1D2DConnection((*itConn), oSegment);

					Sum_Ai += oSegment->getAi();
					Sum_Ai_xGi += oSegment->getAi_XGi();
					Sum_Ai_yGi += oSegment->getAi_YGi();
					Sum_Ai_zGi += oSegment->getAi_ZGi();
				}

				cout << "Sum_Ai " << Sum_Ai << endl;
				cout << "Sum_Ai_xGi " << Sum_Ai_xGi << endl;
				cout << "Sum_Ai_yGi " << Sum_Ai_yGi << endl;
				cout << "Sum_Ai_zGi " << Sum_Ai_zGi << endl;

				//Here we calculate the totals
				(*itConn)->setXCoG(Sum_Ai_xGi/Sum_Ai);
				(*itConn)->setYCoG(Sum_Ai_yGi/Sum_Ai);
				(*itConn)->setZCoG(Sum_Ai_zGi/Sum_Ai);

				cout << "Sum_Ai_xGi/Sum_Ai " << Sum_Ai_xGi/Sum_Ai << endl;
				cout << "Sum_Ai_yGi/Sum_Ai " << Sum_Ai_yGi/Sum_Ai << endl;
				cout << "Sum_Ai_zGi/Sum_Ai " << Sum_Ai_zGi/Sum_Ai << endl;


				int COGOFFSET_Node = std::stoi(CGlobal::GetGlobal()->getIniFile().get("DFEM_PARSER").get("offset_CoG_node"));

				(*itConn)->setIdCoGNode(COGOFFSET_Node + (*itConn)->getIdConnection());

				MapGFEMNodes::iterator itGFEMNode = (*itConn)->GetGFEMNodes()->begin();

				if(itGFEMNode != (*itConn)->GetGFEMNodes()->end()) {

					(*itGFEMNode).second->setCoG_NODE(COGOFFSET_Node + (*itConn)->getIdConnection());
					(*itGFEMNode).second->setCoG_NODE_CP(ZERO);
					(*itGFEMNode).second->setCoG_NODE_X1((*itConn)->getXCoG());
					(*itGFEMNode).second->setCoG_NODE_X2((*itConn)->getYCoG());
					(*itGFEMNode).second->setCoG_NODE_X3((*itConn)->getZCoG());
					(*itGFEMNode).second->setCoG_NODE_CD((*itGFEMNode).second->getGridNode()->getCD());
				}
			}
		}

		bReturn = RESULT_OK;
	}
	catch(std::exception &exc) {
		CLogger::GetLogger()->Log(" <EXCEPTION>: CCalculations::Get1D2DAssociatedData " + std::string(exc.what()));
	}

	return bReturn;
}

/**
 * Method to return the type of a node (CBEAM/CROD)
 * @param: nodeGFEM: GEFM Node to process*
 * @param: dType: Node Type (CBEAM, CROD)
 * @return: Result of the operation. Ostring data to print into output file
 */
std::string CCalculations::CreateConnTwoNodesProjGFEM1D2DToCoG(CGFEMNode *nodeGFEM, int dType) {

	std::string strReturn = STRING_EMPTY;
	std::string strAux = STRING_EMPTY;

	std::string strLine1 = STRING_EMPTY;
	std::string strLine2 = STRING_EMPTY;

	try {

		if(nodeGFEM == NULL) return strReturn;

		switch(dType) {
			case TYPE_CROD:
				strAux = CGlobal::GetGlobal()->getIniFile().get("kINEMATIC_COUPLING_COG_DFEM_1D2D").get("line_3") +  "\n2\n";

				strAux+= std::to_string(nodeGFEM->getCoG_NODE()) + ",1,-1.0," + std::to_string(nodeGFEM->getNode_3_ID()) + ",1,1.0\n" + "2\n";
				strAux+= std::to_string(nodeGFEM->getCoG_NODE()) + ",2,-1.0," + std::to_string(nodeGFEM->getNode_3_ID()) + ",2,1.0\n" + "2\n";
				strAux+= std::to_string(nodeGFEM->getCoG_NODE()) + ",3,-1.0," + std::to_string(nodeGFEM->getNode_3_ID()) + ",3,1.0\n" + "2\n";
				strAux+= std::to_string(nodeGFEM->getCoG_NODE()) + ",4,-1.0," + std::to_string(nodeGFEM->getNode_3_ID()) + ",4,1.0\n" + "2\n";
				strAux+= std::to_string(nodeGFEM->getCoG_NODE()) + ",5,-1.0," + std::to_string(nodeGFEM->getNode_3_ID()) + ",5,1.0\n" + "2\n";
				strAux+= std::to_string(nodeGFEM->getCoG_NODE()) + ",6,-1.0," + std::to_string(nodeGFEM->getNode_3_ID()) + ",6,1.0\n";

				break;
			case TYPE_CBEAM:
				strLine1 = CGlobal::GetGlobal()->getIniFile().get("kINEMATIC_COUPLING_COG_DFEM_1D2D").get("line_4");
				strLine2 = CGlobal::GetGlobal()->getIniFile().get("kINEMATIC_COUPLING_COG_DFEM_1D2D").get("line_5");

				CGlobal::GetGlobal()->Replace(strLine1, "%NODE3%", std::to_string(nodeGFEM->getNode_3_ID()));
				CGlobal::GetGlobal()->Replace(strLine2, "%COG_NODE%", std::to_string(nodeGFEM->getCoG_NODE()));

				strAux = strLine1 + "\n" + strLine2;

				break;
			default:
				break;

		}

		strReturn = strAux;
	}
	catch(std::exception &exc) {
		CLogger::GetLogger()->Log(" <EXCEPTION>: CCalculations::CreateConnTwoNodesProjGFEm1D2DToCoG " + std::string(exc.what()));
	}


	return strReturn;
}

/**
 * Method to return the Associated Data to the segments of the 1D2D connections. The method use the data stored in the input files
 * @return: Result of the operation. Ostring data to print into output file
 */
int  CCalculations::GetAssociated_1D_ElementType(CGFEMNode *nodeGFEM) {

	int dTypeReturn = UNDEFINED;

	try {

		if(nodeGFEM == NULL) return dTypeReturn;

		if(CGlobal::GetGlobal()->NodeInList(nodeGFEM->getIdNode(), *CGFEMReader::GetGFEMReader()->getListCBEAM_Data())) {
			dTypeReturn = TYPE_CBEAM;
		}
		else if(CGlobal::GetGlobal()->NodeInList(nodeGFEM->getIdNode(), *CGFEMReader::GetGFEMReader()->getListCROD_Data())) {
			dTypeReturn = TYPE_CROD;
		}
	}
	catch(std::exception &exc) {
		CLogger::GetLogger()->Log(" <EXCEPTION>: CCalculations::GetAssociated_1D_ElementType " + std::string(exc.what()));
	}


	return dTypeReturn;
}

/**
 * Method to return the Associated Data to the segments of the 1D2D connections. The method use the data stored in the input files
 * @param: *connection
 * @param: *segment
 * @return: Result of the operation. OK or KO result
 */
bool CCalculations::ProcessSegment1D2DConnection(CConnection *connection, CSegment *segment) {

	bool bReturn = RESULT_KO;

	std::string strNodeG1 = STRING_EMPTY;
	std::string strNodeG2 = STRING_EMPTY;

	CDFEMObject *oDFEMPoint1 = NULL;
	CDFEMObject *oDFEMPoint2 = NULL;
	MapDFEMObjects *oMapDFEMObjects = NULL;

	try {

		if(connection == NULL || segment == NULL) return bReturn;

		std::string IdSegment = segment->getIdSegment();

		CGlobal::GetGlobal()->FindSegmentDFEMNodes(IdSegment, connection->GetMatrixData(), strNodeG1, strNodeG2);

		if(strNodeG1 != STRING_EMPTY) {

			if(CGlobal::GetGlobal()->getFormatData() == FORMAT_1) {
				oMapDFEMObjects = CDFEMReader::GetDFEMReader()->getMapDFEMObjects();
			}
			else {
				oMapDFEMObjects = CGlobalDFEMReader::GetCGlobalDFEMReader()->getMapGlobalDFEMObjects();
			}

			MapDFEMObjects::iterator itMap = oMapDFEMObjects->find(strNodeG1);

			if(itMap != oMapDFEMObjects->end()) {

				oDFEMPoint1 = oMapDFEMObjects->find(strNodeG1)->second;

				if(oDFEMPoint1 != NULL) {

					cout << "IdSegment " << IdSegment << " G1:" << strNodeG1 << "  xG1: " << oDFEMPoint1->getCoord_X()
																			 << "  yG1: " << oDFEMPoint1->getCoord_Y()
																			 << "  zG1: " << oDFEMPoint1->getCoord_Z();


					segment->setG1(strNodeG1);
					segment->setX_G1(oDFEMPoint1->getCoord_X());
					segment->setY_G1(oDFEMPoint1->getCoord_Y());
					segment->setZ_G1(oDFEMPoint1->getCoord_Z());
					segment->setT(4);
				}
			}
			else {
				cout << "IdNode: " << strNodeG1 << endl;
			}
		}

		//Getting X,Y,Z of node G2 if exists
		if(strNodeG2 != STRING_EMPTY) {

			MapDFEMObjects::iterator itMap = oMapDFEMObjects->find(strNodeG2);

			if(itMap != oMapDFEMObjects->end()) {

				oDFEMPoint2 = oMapDFEMObjects->find(strNodeG2)->second;

				if(oDFEMPoint2 != NULL) {

					cout  << IdSegment << " G2:" << strNodeG2 << "  xG2: " << oDFEMPoint2->getCoord_X()
															  << "  yG2: " << oDFEMPoint2->getCoord_Y()
															  << "  zG2: " << oDFEMPoint2->getCoord_Z();

					segment->setG1(strNodeG2);
					segment->setX_G2(oDFEMPoint2->getCoord_X());
					segment->setY_G2(oDFEMPoint2->getCoord_Y());
					segment->setZ_G2(oDFEMPoint2->getCoord_Z());
				}
			}
			else {
				cout << "IdNode: " << strNodeG2 << endl;
			}
		}

		//Calculate t value
		m_pThis->GetSegment_T_ELSETNAME(*segment);

		//Calculate L value
		if(oDFEMPoint1 != NULL && oDFEMPoint2 != NULL) {

			CCoordinate3D *coordG1 = new CCoordinate3D();
			coordG1->setX(segment->getX_G1());
			coordG1->setY(segment->getY_G1());
			coordG1->setZ(segment->getZ_G1());

			CCoordinate3D *coordG2 = new CCoordinate3D();
			coordG2->setX(segment->getX_G2());
			coordG2->setY(segment->getY_G2());
			coordG2->setZ(segment->getZ_G2());

			float fDistance = CGlobal::GetGlobal()->GetDistance(coordG1, coordG2);

			delete coordG1;
			coordG1 = NULL;

			delete coordG2;
			coordG2 = NULL;

			segment->setL(fDistance);
		}

		//Calculate Ai value
		segment->setAi(segment->getT() * segment->getL());

		//Calculate xGi value
		segment->setX_Gi((segment->getX_G1() + segment->getX_G2())/2);

		//Calculate yGi value
		segment->setY_Gi((segment->getY_G1() + segment->getY_G2())/2);

		//Calculate zGi value
		segment->setZ_Gi((segment->getZ_G1() + segment->getZ_G2())/2);

		//Calculate Ai_XGi value
		segment->setAi_XGi( segment->getAi() * segment->getX_Gi());

		//Calculate Ai_YGi value
		segment->setAi_YGi( segment->getAi() * segment->getY_Gi());

		//Calculate Ai_ZGi value
		segment->setAi_ZGi( segment->getAi() * segment->getZ_Gi());


		bReturn = RESULT_OK;
	}
	catch(std::exception &exc) {
		CLogger::GetLogger()->Log(" <EXCEPTION>: CCalculations::ProcessSegment " + std::string(exc.what()));
	}

	return bReturn;
}

/**
 * Method to return the get T and ELSET_NAME value of a segment.
 * @param: *connection
  * @return: Result of the operation. OK or KO result
 */
bool CCalculations::GetSegment_T_ELSETNAME(CSegment &segment) {
	bool bReturn = RESULT_KO;

	bool bLocated = false;
	std::string strELSET_NAME;
	std::string strELSET_NAME_Aux;
	float fTValue = ZERO;
	std::string strInstanceName = STRING_EMPTY;
	std::string strNodeId = STRING_EMPTY;

	MapSHELLSections *mapSHELLSections = NULL;
	MapELSETSections *mapELSETSections = NULL;
	MapELEMENTSections *mapELEMENTSections = NULL;

	try {

		std::string	IdSegment = segment.getIdSegment();

		if(CGlobal::GetGlobal()->getFormatData() == FORMAT_1) {
			mapSHELLSections = CDFEMReader::GetDFEMReader()->getMapShellSections();
		}
		else {

			mapSHELLSections = CGlobalDFEMReader::GetCGlobalDFEMReader()->getMapGlobalShellSections();

			CGlobal::GetGlobal()->GetTwoParts(IdSegment, ".", strInstanceName, strNodeId);
		}

		if(mapSHELLSections != NULL && mapSHELLSections->size() > 0) {

			MapSHELLSections::iterator itSHELLSection = mapSHELLSections->begin();

			if(CGlobal::GetGlobal()->getFormatData() == FORMAT_1) {
				mapELSETSections = CDFEMReader::GetDFEMReader()->getMapElsetSections();
			}
			else {
				mapELSETSections = CGlobalDFEMReader::GetCGlobalDFEMReader()->getMapGlobalElsetSections();
			}

			if(mapELSETSections != NULL && mapELSETSections->size() > 0) {

				MapELSETSections::iterator itELSETSection = mapELSETSections->begin();

				while(itELSETSection != mapELSETSections->end() && ! bLocated) {

					CELSETSection *elsetSection = (*itELSETSection).second;

					bool bNodeExist = false;

					if(CGlobal::GetGlobal()->getFormatData() == FORMAT_1) {
						bNodeExist = CGlobal::GetGlobal()->NodeInList(IdSegment, *elsetSection->getListNodes());
					}
					else {

						if(elsetSection->getInstanceName() == strInstanceName) {

							bNodeExist = CGlobal::GetGlobal()->NodeInList(strNodeId, *elsetSection->getListNodes());
						}
					}

					if(bNodeExist) {

						string strELSETName = (*itELSETSection).first;
						itSHELLSection = mapSHELLSections->find(strELSETName);

						if(itSHELLSection != mapSHELLSections->end()) {

							strELSET_NAME = (*itSHELLSection).second->getShellName();
							fTValue = (*itSHELLSection).second->getShellValue();
							bLocated = true;
							break;
						}
					}

					++itELSETSection;
				}
			}

			if(!bLocated) {

				if(CGlobal::GetGlobal()->getFormatData() == FORMAT_1) {
					mapELEMENTSections = CDFEMReader::GetDFEMReader()->getMapElementSections();
				}
				else {
					mapELEMENTSections = CGlobalDFEMReader::GetCGlobalDFEMReader()->getMapGlobalElementSections();
				}

				if(mapELEMENTSections != NULL && mapELEMENTSections->size() > 0) {

					MapELEMENTSections::iterator itELEMENTSection = mapELEMENTSections->begin();

					while(itELEMENTSection != mapELEMENTSections->end() && ! bLocated) {

						CELEMENTSection *elementSection = (*itELEMENTSection).second;

						bool bNodeExist = false;

						if(CGlobal::GetGlobal()->getFormatData() == FORMAT_1) {
							bNodeExist = CGlobal::GetGlobal()->NodeInList(IdSegment, *elementSection->getListNodes());
						}
						else {
							if(elementSection->getInstanceName() == strInstanceName) {

								bNodeExist = CGlobal::GetGlobal()->NodeInList(strNodeId, *elementSection->getListNodes());
							}
						}

						if(bNodeExist) {

							string strELSETName = (*itELEMENTSection).first;
							itSHELLSection = mapSHELLSections->find(strELSETName);

							if(itSHELLSection != mapSHELLSections->end()) {

								strELSET_NAME = (*itSHELLSection).second->getShellName();
								fTValue = (*itSHELLSection).second->getShellValue();
								bLocated = true;
								break;
							}
						}

						++itELEMENTSection;
					}
				}
			}
		}

		segment.setElsetName(strELSET_NAME);
		segment.setT(fTValue);

		cout << "  ELSET NAME = " << strELSET_NAME << " T: " << fTValue << endl;

		bReturn = RESULT_OK;

	}
	catch(std::exception &exc) {
		CLogger::GetLogger()->Log(" <EXCEPTION>: CCalculations::GetSegment_T_ELSETNAME " + std::string(exc.what()));
	}

	return bReturn;
}

/**
 * Method to
 * @param: oNode
 * @param: lstNodesProcessed
  * @return: Result of the operation. OK or KO result
 */
bool CCalculations::StoreCQUADData(CGFEMNode &oNode, ListIntegerData &lstNodesProcessed) {

	bool bReturn = RESULT_KO;

	try {
		if(CGFEMReader::GetGFEMReader()->getMapCQUAD4Data()->size() > 0) {
			CCQUAD4Node *oNodeQuad4 = CGlobal::FindAssociatedNodeToGFEM(oNode.getIdNode(), CGFEMReader::GetGFEMReader()->getMapCQUAD4Data(), lstNodesProcessed);

			while(oNodeQuad4 != NULL && lstNodesProcessed.size() < 2) {

				switch(lstNodesProcessed.size()) {
					case ZERO:
						//We store the data
						oNode.setEid_1(oNodeQuad4->getEID());
						oNode.setZOFFS_1(oNodeQuad4->getZOFFS());
						oNode.setG1_1(oNodeQuad4->getG1());
						oNode.setG2_1(oNodeQuad4->getG2());
						oNode.setG3_1(oNodeQuad4->getG3());
						oNode.setG4_1(oNodeQuad4->getG4());

						break;

					case ONE:
						//Almacenar datos
						oNode.setEid_2(oNodeQuad4->getEID());
						oNode.setZOFFS_2(oNodeQuad4->getZOFFS());
						oNode.setG1_2(oNodeQuad4->getG1());
						oNode.setG2_2(oNodeQuad4->getG2());
						oNode.setG3_2(oNodeQuad4->getG3());
						oNode.setG4_2(oNodeQuad4->getG4());

						break;
					default:
						break;
				}

				lstNodesProcessed.push_back(oNodeQuad4->getEID());

				if(lstNodesProcessed.size() == 2) break;

				oNodeQuad4 = CGlobal::FindAssociatedNodeToGFEM(oNode.getIdNode(), CGFEMReader::GetGFEMReader()->getMapCQUAD4Data(), lstNodesProcessed);
			}
		}

		bReturn = RESULT_OK;
	}
	catch(std::exception &exc) {
		CLogger::GetLogger()->Log(" <EXCEPTION>: CCalculations::StoreCQUADData " + std::string(exc.what()));
	}

	return bReturn;
}

/**
 * Method to
 * @return: Result of the operation.
 */
ListStringData * CCalculations::GetGFEMNodesString(){

	ListStringData *lstNodesGFEM = new ListStringData();
	ListIntegerData lstNodesProcessed;

	try {

		ListConnections *lstConnections2D2D = CCSVReader::GetCSVReader()->GetAssociativityFile()->GetConnections2D2D();

		if(lstConnections2D2D != NULL && lstConnections2D2D->size() > 0 ) {

			std::string strNodes2D2d = STRING_EMPTY;

			for(ListConnections::iterator itConn = lstConnections2D2D->begin(); itConn != lstConnections2D2D->end(); itConn++) {
				strNodes2D2d = CGlobal::GetGlobal()->GetNodesGFEM_OutputData((*itConn), lstNodesProcessed);

				lstNodesGFEM->push_back(strNodes2D2d);
			}
		}

		lstNodesGFEM->unique();

		//We process all the 1D2D connections to generate the data associated to the GFEM nodes of the connections.
		ListConnections *lstConnections1D2D = CCSVReader::GetCSVReader()->GetAssociativityFile()->GetConnections1D2D();

		if(lstConnections1D2D != NULL && lstConnections1D2D->size() > 0 ) {
			std::string strNodes1D2d = STRING_EMPTY;

			for(ListConnections::iterator itConn = lstConnections1D2D->begin(); itConn != lstConnections1D2D->end(); itConn++) {
				strNodes1D2d = CGlobal::GetGlobal()->GetNodesGFEM_OutputData((*itConn), lstNodesProcessed);

				lstNodesGFEM->push_back(strNodes1D2d);
			}
		}

		lstNodesGFEM->unique();

	}
	catch(std::exception &exc) {
		CLogger::GetLogger()->Log(" <EXCEPTION>: CCalculations::GetGFEMNodes " + std::string(exc.what()));
	}

	return lstNodesGFEM;

}

/**
 * Method to
 * @return: Result of the operation.
 */
ListStringData * CCalculations::GetNode2Node3CoGString() {
	ListStringData *lstNode2Node3CoG = new ListStringData();

	ListIntegerData lstNodesProcessed;

	try {

		ListConnections *lstConnections2D2D = CCSVReader::GetCSVReader()->GetAssociativityFile()->GetConnections2D2D();

		if(lstConnections2D2D != NULL && lstConnections2D2D->size() > 0 ) {

			std::string strNodes2D2d = STRING_EMPTY;

			for(ListConnections::iterator itConn = lstConnections2D2D->begin(); itConn != lstConnections2D2D->end(); itConn++) {
				strNodes2D2d = CGlobal::GetGlobal()->GetNode2Node3CoG_OutputData((*itConn), TYPE_2D2D, lstNodesProcessed);

				lstNode2Node3CoG->push_back(strNodes2D2d);
			}
		}

		//We process all the 1D2D connections to generate the data associated to the GFEM nodes of the connections.
		ListConnections *lstConnections1D2D = CCSVReader::GetCSVReader()->GetAssociativityFile()->GetConnections1D2D();

		if(lstConnections1D2D != NULL && lstConnections1D2D->size() > 0 ) {
			std::string strNodes1D2d = STRING_EMPTY;

			for(ListConnections::iterator itConn = lstConnections1D2D->begin(); itConn != lstConnections1D2D->end(); itConn++) {
				strNodes1D2d = CGlobal::GetGlobal()->GetNode2Node3CoG_OutputData((*itConn), TYPE_1D2D, lstNodesProcessed);

				lstNode2Node3CoG->push_back(strNodes1D2d);
			}
		}
	}
	catch(std::exception &exc) {
		CLogger::GetLogger()->Log(" <EXCEPTION>: CCalculations::GetNode2Node3CoGString " + std::string(exc.what()));
	}

	return lstNode2Node3CoG;
}

/**
 * Method to
 * @return: Result of the operation.
 */
std::string  CCalculations::GetStringKINEMATIC_COUPLING_COG_DFEM_1D2D() {
	std::string strReturn = STRING_EMPTY;

	try {
		//We process all the 1D2D connections to generate the data associated to the GFEM nodes of the connections.
		ListConnections *lstConnections1D2D = CCSVReader::GetCSVReader()->GetAssociativityFile()->GetConnections1D2D();

		if(lstConnections1D2D != NULL && lstConnections1D2D->size() > 0 ) {
			std::string strNodes1D2d = STRING_EMPTY;

			for(ListConnections::iterator itConn = lstConnections1D2D->begin(); itConn != lstConnections1D2D->end(); itConn++) {

				strReturn += CGlobal::GetGlobal()->Create_Kinematic_Coupling_CoG_DFEM_1D_2D((*itConn), PART_0);
			}
		}
	}
	catch(std::exception &exc) {
		CLogger::GetLogger()->Log(" <EXCEPTION>: CCalculations::GetStringKINEMATIC_COUPLING_COG_DFEM_1D2D " + std::string(exc.what()));
	}

	return strReturn;
}


/**
 * Method to
 * @return: Result of the operation.
 */
std::string  CCalculations::GetStringT3D2_ABAQUS() {
	std::string strReturn = STRING_EMPTY;

	try {
		//We process all the 2D2D connections to generate the data associated to the GFEM nodes of the connections.
		ListConnections *lstConnections2D2D = CCSVReader::GetCSVReader()->GetAssociativityFile()->GetConnections2D2D();

		if(lstConnections2D2D != NULL && lstConnections2D2D->size() > 0 ) {

			for(ListConnections::iterator itConn = lstConnections2D2D->begin(); itConn != lstConnections2D2D->end(); itConn++) {

				strReturn += (*itConn)->getStrT3D2Abaqus() + "\n**\n**\n";
			}
		}
	}
	catch(std::exception &exc) {
		CLogger::GetLogger()->Log(" <EXCEPTION>: CCalculations::GetStringT3D2_ABAQUS " + std::string(exc.what()));
	}

	return strReturn;
}

/**
 * Method to
 * @return: Result of the operation.
 */
std::string  CCalculations::GetSurfaceDFEMNodes() {
	std::string strReturn = STRING_EMPTY;

	try {
		//We process all the 2D2D connections to generate the data associated to the GFEM nodes of the connections.
		ListConnections *lstConnections2D2D = CCSVReader::GetCSVReader()->GetAssociativityFile()->GetConnections2D2D();

		if(lstConnections2D2D != NULL && lstConnections2D2D->size() > 0 ) {

			for(ListConnections::iterator itConn = lstConnections2D2D->begin(); itConn != lstConnections2D2D->end(); itConn++) {

				strReturn += CGlobal::GetGlobal()->Create_Surface_DFEM_Nodes((*itConn)) + "\n**\n**";
			}
		}
	}
	catch(std::exception &exc) {
		CLogger::GetLogger()->Log(" <EXCEPTION>: CCalculations::GetSurfaceDFEMNodes " + std::string(exc.what()));
	}

	return strReturn;
}

/**
 * Method to
 * @return: Result of the operation.
 */
std::string CCalculations::GetKINEMATIC_COUPLING_1_2_CARD() {

	std::string strReturn = STRING_EMPTY;

	try {

		//We process all the 2D2D connections to generate the data associated to the GFEM nodes of the connections.
		ListConnections *lstConnections2D2D = CCSVReader::GetCSVReader()->GetAssociativityFile()->GetConnections2D2D();

		ListIntegerData lstNodesProcessed;

		if(lstConnections2D2D != NULL && lstConnections2D2D->size() > 0 ) {

			for(ListConnections::iterator itConn = lstConnections2D2D->begin(); itConn != lstConnections2D2D->end(); itConn++) {

				if((*itConn)->GetGFEMNodes()->size() <= 0) continue;

				MapGFEMNodes *mapNodes = (*itConn)->GetGFEMNodes();

				for(MapGFEMNodes::iterator itNodeGFEM = mapNodes->begin(); itNodeGFEM != mapNodes->end(); itNodeGFEM++) {

					std::string strKinematicCoupling = (*itNodeGFEM).second->getKINEMATIC_COUPLING_1_2_CARD() ;
					CGlobal::GetGlobal()->Trim(strKinematicCoupling);

					if(strKinematicCoupling !=  STRING_EMPTY && !CGlobal::GetGlobal()->NodeInList((*itNodeGFEM).second->getIdNode(), lstNodesProcessed)) {

						lstNodesProcessed.push_back((*itNodeGFEM).second->getIdNode());
						strReturn += (*itNodeGFEM).second->getKINEMATIC_COUPLING_1_2_CARD() + "\n";

						strReturn += "**\n";
					}
				}
			}
		}

		//We process all the 2D2D connections to generate the data associated to the GFEM nodes of the connections.
		ListConnections *lstConnections1D2D = CCSVReader::GetCSVReader()->GetAssociativityFile()->GetConnections1D2D();

		if(lstConnections1D2D != NULL && lstConnections1D2D->size() > 0 ) {

			for(ListConnections::iterator itConn = lstConnections1D2D->begin(); itConn != lstConnections1D2D->end(); itConn++) {

				if((*itConn)->GetGFEMNodes()->size() <= 0) continue;

				MapGFEMNodes *mapNodes = (*itConn)->GetGFEMNodes();

				for(MapGFEMNodes::iterator itNodeGFEM = mapNodes->begin(); itNodeGFEM != mapNodes->end(); itNodeGFEM++) {

					std::string strKinematicCoupling = (*itNodeGFEM).second->getKINEMATIC_COUPLING_1_2_CARD() ;
					CGlobal::GetGlobal()->Trim(strKinematicCoupling);

					if(strKinematicCoupling !=  STRING_EMPTY && !CGlobal::GetGlobal()->NodeInList((*itNodeGFEM).second->getIdNode(), lstNodesProcessed)) {

						lstNodesProcessed.push_back((*itNodeGFEM).second->getIdNode());
						strReturn += (*itNodeGFEM).second->getKINEMATIC_COUPLING_1_2_CARD() + "\n";

						strReturn += "**\n";
					}
				}
			}
		}
	}
	catch(std::exception &exc) {

		CLogger::GetLogger()->Log(" <EXCEPTION>: CCalculations::GetKINEMATIC_COUPLING_1_2_CARD " + std::string(exc.what()));
	}

	return strReturn;
}

/**
 * Method to
 * @return: Result of the operation.
 */
std::string CCalculations::GetKINEMATIC_COUPLING_CoG_DFEM_1D_2D() {
	std::string strReturn = STRING_EMPTY;

	try {

		ListConnections *lstConnections1D2D = CCSVReader::GetCSVReader()->GetAssociativityFile()->GetConnections1D2D();

		//We process all the 1D2D connections to generate the data associated to the DFEM nodes of the connections.
		if((lstConnections1D2D ) != NULL && lstConnections1D2D->size() > 0 ) {

			for(ListConnections::iterator itConn = lstConnections1D2D->begin(); itConn != lstConnections1D2D->end(); itConn++) {

				strReturn += CGlobal::GetGlobal()->Create_Kinematic_Coupling_CoG_DFEM_1D_2D((*itConn), PART_1) + "\n**\n";
			}
		}
	}
	catch(std::exception &exc) {

		CLogger::GetLogger()->Log(" <EXCEPTION>: CCalculations::GetKINEMATIC_COUPLING_CoG_DFEM_1D_2D " + std::string(exc.what()));
	}

	return strReturn;
}

std::string CCalculations::GetConnTwoNodesProjGFEM1D2DToCoG(int dTypeToShow) {

	std::string strReturn = STRING_EMPTY;

	try {
		ListConnections *lstConnections1D2D = CCSVReader::GetCSVReader()->GetAssociativityFile()->GetConnections1D2D();

		//We process all the 1D2D connections to generate the data associated to the DFEM nodes of the connections.
		if((lstConnections1D2D ) != NULL && lstConnections1D2D->size() > 0 ) {

			for(ListConnections::iterator itConn = lstConnections1D2D->begin(); itConn != lstConnections1D2D->end(); itConn++) {

				if((*itConn)->GetGFEMNodes()->size() <= 0) continue;

				MapGFEMNodes::iterator itGFEMNode = (*itConn)->GetGFEMNodes()->begin();

				if(itGFEMNode == (*itConn)->GetGFEMNodes()->end()) continue;

				//Generate 1D Elm Asoc.  Type value
				int dIdType = GetAssociated_1D_ElementType((*itGFEMNode).second);

				if(dIdType == dTypeToShow) {

					strReturn +=  m_pThis->CreateConnTwoNodesProjGFEM1D2DToCoG((*itGFEMNode).second, dIdType) + "\n**\n";
				}
			}
		}
	}
	catch(std::exception &exc) {
		CLogger::GetLogger()->Log(" <EXCEPTION>: CCalculations::GetConnTwoNodesProjGFEM1D2DToCoG " + std::string(exc.what()));
	}

	return strReturn;
}

std::string CCalculations::GetEQUATION_CARD_NODE3_NODE2_GFEM_2D2D() {

	std::string strReturn = STRING_EMPTY;

	try {
		//We process all the 2D2D connections to generate the data associated to the GFEM nodes of the connections.
		ListConnections *lstConnections2D2D = CCSVReader::GetCSVReader()->GetAssociativityFile()->GetConnections2D2D();

		if(lstConnections2D2D != NULL && lstConnections2D2D->size() > 0 ) {

			for(ListConnections::iterator itConn = lstConnections2D2D->begin(); itConn != lstConnections2D2D->end(); itConn++) {

				if((*itConn)->GetGFEMNodes()->size() <= 0) continue;

				MapGFEMNodes *mapNodes = (*itConn)->GetGFEMNodes();

				for(MapGFEMNodes::iterator itNodeGFEM = mapNodes->begin(); itNodeGFEM != mapNodes->end(); itNodeGFEM++) {

					MapGFEMNodes::iterator itAux = itNodeGFEM;

					if(++itAux != mapNodes->end()) {
						strReturn += "\n" + (*itNodeGFEM).second->getEQUATION_CARD() ;
					}
					else {
						strReturn += "\n" + (*itNodeGFEM).second->getEQUATION_CARD() + "\n**";
					}
				}
			}
		}
	}
	catch(std::exception &exc) {
		CLogger::GetLogger()->Log(" <EXCEPTION>: CCalculations::GetEQUATION_CARD_NODE3_NODE2_GFEM_2D2D " + std::string(exc.what()));
	}

	return strReturn;
}
