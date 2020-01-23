/*
 * Calculations.h
 *
 *  Created on: 19 nov. 2019
 *      Author: fernando.olivares
 */

#ifndef CALCULATIONS_H_
#define CALCULATIONS_H_

#include "Global.h"

class CGridNode;
class CGFEMNode;
class CVector3D;

/**
* Class that implements the operations to generate the data that we will write to the output file.
 */
class CCalculations {

private:

	/**
	 * Private default constructor
	 */
	CCalculations();

	/**
	 * Static object used in the singleton object
	 */
	static CCalculations	* m_pThis;

	/**
	 * m_T3D2OFFSET value
	 */
	int m_T3D2OFFSET;

	/**
	 * Map to store the GFEM 2D2D Processed
	 */
	MapGFEMNodes	*m_mapGFEMNodes;

public:

	/**
	 * Default Destructor
	 */
	virtual ~CCalculations();

	/**
	* Getter/Setter of the map GFEM.
	**/
	MapGFEMNodes * GetMapGFEMNodes() { return m_mapGFEMNodes;}
	void setMapGFEMNodes(MapGFEMNodes *mapGFEMNodes) { m_mapGFEMNodes = mapGFEMNodes; }

	/**
	* Getter/Setter of the m_T3D2OFFSET.
	**/
	int 					getT3D2OFFSET() const { return m_T3D2OFFSET; }
	void 					setT3D2OFFSET(int t3D2Offset) { m_T3D2OFFSET = t3D2Offset; }

	/**
	* Getter of the map GFEM.
	**/
	std::map<int, CGFEMNode *> * GetGFEMNodes() { return m_mapGFEMNodes;}

	/**
	*   Function to create the instance of CCalculations class.
	*   @return singleton object of CCalculations class..
	*/
	static CCalculations* GetCalculations();

	/**
	 * Method to process the GFEM Associated Data for 1D2d and 2D2D connections. The method use the data stored in the imput files
	 */
	bool 					Get1D2D_2D2D_GFEM_AssociatedData();

	/**
	 * Method to return the GFEM Associated Data of 1D2D/2D2D connections. The method use the data stored in the imput files
	 */
	bool 					GetGFEMAssociatedData(ListConnections *lstConnections, int dTypeConnection);

	/**
	 * Method that implement the operation to Store CQUAD Data
	 */
	bool 					StoreCQUADData(CGFEMNode &oNode, ListIntegerData &lstNodesProcessed);

	/**
	 * Method that implement the operation to generate the normal plain vector
	 */
	CVector3D * 			GenetareNormalPlainVector(CGFEMNode *nodeGFEM, int IdVector);

	/**
	 * Method that return the vector product of two vectors passed as parameter
	 */
	CVector3D * 			GenerateVectorProduct(CVector3D *oVector1, CVector3D *oVector2);

	/**
	 * Method that return the normal vector product the vector passed as parameter
	 */
	CVector3D * 			GenetareNormalVector(CGFEMNode *nodeGFEM);

	/**
	 * Method that implement the operation to generate the GFEM Node Coordinates Associated Data
	 */
	CGFEMNode * 			GetGFEMNodeCoordAssociatedData(CGFEMNode *nodeGFEM,  MapGRIDData *mapGridData);

	/**
	 * Method that perform the operation to generate a new NODE1 data
	 */
	CGridNode * 			CreateNewNode1(CGFEMNode *nodeGFEM, CVector3D *oVector3D);

	/**
	 *  * Method that perform the operation to generate a new NODE2 data
	 */
	CGridNode * 			CreateNewNode2(CGFEMNode *nodeGFEM, CVector3D *oVector3D);

	/**
	 * Method that perform the operation to generate the KINEMATIC_COUPLING_1_2 data associated to the node passed as parameter
	 */
	bool 					CreateKinematicCoupling(CGFEMNode *nodeGFEM);

	/**
	 * Method that perform the operation to create the new nodes on the DFEM suurface
	 */
	bool 					CreateNewNode3(CGFEMNode &oNodeGFEM, CConnection *connection);

	/**
	 * Method that perform the operation to Process Nodes 2D2D Connections
	 */
	bool 					ProcessNodes2D2DConnections(CConnection *connection);

	/**
	 * Function to calculate the distance between the node to project and the DFEM plane/surface
	 */
	float 					CalculateDistanceNodeProjectToDFEMPlain(CGFEMNode *nodeGFEM, CDFEMObject *nodeDFEM);

	/**
	 * Function to generate a new EQUATION CARD Data for de actual CGFEM Node
	 */
	bool 					CreaterEQuationCard(CGFEMNode *nodeGFEM);

	/**
	 * Method that implement the operation to Create T3D2 ABAQUS Data
	 */
	bool 					CreateT3D2ABAQUSData(CConnection *oConnection);

	/**
	 * Method that implement the operation to Process Associated Data to GFEM Nodes
	 */
	PairNodes *				ProcessAssociatedData(MapGFEMNodes *mapNodes, int dValueG1, int dValueG2, int dValueG3, int dValueG4);

	/**
	 * Method to generate the associated data to 1D2D connections. The method use the data stored in the imput files
	 */
	bool 					Get1D2DAssociatedData();

	/**
	 * Method to generate the associated information to a Segment of a connection 1D2D. The method use the data stored in the imput files
	 */
	bool 					ProcessSegment1D2DConnection(CConnection *connection, CSegment *segment);

	/**
	 * Method to return the get T and ELSET_NAME value of a segment.
	 */
	bool 					GetSegment_T_ELSETNAME(CSegment &segment);

	/**
	 * Method that perform the operation to Create Conn Two Nodes Proj GFEM 1D2D To CoG
	 */
	std::string 			CreateConnTwoNodesProjGFEM1D2DToCoG(CGFEMNode *nodeGFEM, int dType);

	/**
	 * Method that perform the operation to Get Associated 1D Element Type
	 */
	int  					GetAssociated_1D_ElementType(CGFEMNode *nodeGFEM);


	//Output File Methods

	/**
	 * Method that perform the operation to Get GFEM Nodes String
	 */
	ListStringData *		GetGFEMNodesString();

	/**
	 * Method that perform the operation to Get Node2 Node3 CoG String
	 */
	ListStringData * 		GetNode2Node3CoGString();

	/**
	 * Method that perform the operation to Get String KINEMATIC COUPLING COG DFEM 1D2D
	 */
	std::string  			GetStringKINEMATIC_COUPLING_COG_DFEM_1D2D();

	/**
	 * Method that perform the operation to Get String T3D2 ABAQUS
	 */
	std::string  			GetStringT3D2_ABAQUS();

	/**
	 * Method that perform the operation to Get Associated 1D Element Type
	 */
	std::string		 		GetSOLIDSECTION_Cards();

	/**
	 * Method that perform the operation to Get Surface With T3D2 Elements
	 */
	std::string 			GetSurfaceWithT3D2Elements();

	/**
	 * Method that perform the operation to Get Surface DFEM Nodes
	 */
	std::string  			GetSurfaceDFEMNodes();

	/**
	 * Method that perform the operation to Get Surface NSET
	 */
	std::string 			GetSurfaceNSET();

	/**
	 * Method that perform the operation to Get T3D2 Element Between GFEM Projected Nodes
	 */
	std::string 			GetT3D2ElementBetweenGFEMProjectedNodes();

	/**
	 * Method that perform the operation to Get TIE Card
	 */
	std::string 			GetTIECard();

	/**
	 * Method that perform the operation to Get KINEMATIC COUPLING 1 2 CARD
	 */
	std::string 			GetKINEMATIC_COUPLING_1_2_CARD();

	/**
	 * Method that perform the operation to Get KINEMATIC COUPLING CoG DFEM 1D2D
	 */
	std::string 			GetKINEMATIC_COUPLING_CoG_DFEM_1D_2D();

	/**
	 * Method that perform the operation to Get Get Conn Two Nodes Proj GFEM 1D2D To CoG
	 */
	std::string 			GetConnTwoNodesProjGFEM1D2DToCoG(int dTypeToShow);

	/**
	 * Method that perform the operation to Get EQUATION CARD NODE3 NODE2 GFEM2D2D
	 */
	std::string 			GetEQUATION_CARD_NODE3_NODE2_GFEM_2D2D();


};

#endif /* CALCULATIONS_H_ */
