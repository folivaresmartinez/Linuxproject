/*
 * CGFEMNode.h
 *
 *  Created on: 12 nov. 2019
 *      Author: NG82748
 */

#ifndef GFEMNODE_H_
#define GFEMNODE_H_

#include "GridNode.h"
#include "Node.h"

class CGFEMNode : public CNode {

private:

	/**
	 * m_GridNode value
	 */
	CGridNode 			*m_GridNode;

	/**
	 * m_EID_1 value
	 */
	int 				m_EID_1;

	/**
	 * m_ZOFFS_1 value
	 */
	float				m_ZOFFS_1;

	/**
	 * m_G1_1 value
	 */
	int					m_G1_1;

	/**
	 * m_G2_1 value
	 */
	int 				m_G2_1;

	/**
	 * m_G3_1 value
	 */
	int 				m_G3_1;

	/**
	 * m_G4_1 value
	 */
	int 				m_G4_1;

	/**
	 * m_EID_2 value
	 */
	int 				m_EID_2;

	/**
	 * m_ZOFFS_2 value
	 */
	float 				m_ZOFFS_2;

	/**
	 * m_G1_2 value
	 */
	int 				m_G1_2;

	/**
	 * m_G2_2 value
	 */
	int 				m_G2_2;

	/**
	 * m_G3_2 value
	 */
	int 				m_G3_2;

	/**
	 * m_G4_2 value
	 */
	int 				m_G4_2;

	/**
	 * m_ZOFFS value
	 */
	float 				m_ZOFFS;

	/**
	 * m_G1_1_CP value
	 */
	int 				m_G1_1_CP;

	/**
	 * m_G1_1_X1 value
	 */
	float 				m_G1_1_X1;

	/**
	 * m_G1_1_X2 value
	 */
	float 				m_G1_1_X2;

	/**
	 * m_G1_1_X3 value
	 */
	float 				m_G1_1_X3;

	/**
	 * m_G2_1_CP value
	 */
	int 				m_G2_1_CP;

	/**
	 * m_G2_1_X1 value
	 */
	float 				m_G2_1_X1;

	/**
	 * m_G2_1_X2 value
	 */
	float 				m_G2_1_X2;

	/**
	 * m_G2_1_X3 value
	 */
	float 				m_G2_1_X3;

	/**
	 * m_G3_1_CP value
	 */
	int 				m_G3_1_CP;

	/**
	 * m_G3_1_X1 value
	 */
	float 				m_G3_1_X1;

	/**
	 * m_G3_1_X2 value
	 */
	float 				m_G3_1_X2;

	/**
	 * m_G3_1_X3 value
	 */
	float 				m_G3_1_X3;

	/**
	 * m_G1_2_CP value
	 */
	int 				m_G1_2_CP;

	/**
	 * m_G1_2_X1 value
	 */
	float 				m_G1_2_X1;

	/**
	 * m_G1_2_X2 value
	 */
	float 				m_G1_2_X2;

	/**
	 * m_G1_2_X3 value
	 */
	float 				m_G1_2_X3;

	/**
	 * m_G2_2_CP value
	 */
	int 				m_G2_2_CP;

	/**
	 * m_G2_2_X1 value
	 */
	float 				m_G2_2_X1;

	/**
	 * m_G2_2_X2 value
	 */
	float 				m_G2_2_X2;

	/**
	 * m_G2_2_X3 value
	 */
	float 				m_G2_2_X3;

	/**
	 * m_G3_2_CP value
	 */
	int 				m_G3_2_CP;

	/**
	 * m_G3_2_X1 value
	 */
	float 				m_G3_2_X1;

	/**
	 * m_G3_2_X2 value
	 */
	float 				m_G3_2_X2;

	/**
	 * m_G3_2_X3 value
	 */
	float 				m_G3_2_X3;

	/**
	 * m_V3_X1_NORM value
	 */
	float				m_V3_X1_NORM;

	/**
	 * m_V3_X2_NORM value
	 */
	float				m_V3_X2_NORM;

	/**
	 * m_V3_X3_NORM value
	 */
	float				m_V3_X3_NORM;

	/**
	 * m_NODE_2_ID value
	 */
	int 				m_NODE_2_ID;

	/**
	 * m_NODE_2_CP value
	 */
	int 				m_NODE_2_CP;

	/**
	 * m_NODE_2_X1 value
	 */
	float 				m_NODE_2_X1;

	/**
	 * m_NODE_2_X2 value
	 */
	float 				m_NODE_2_X2;

	/**
	 * m_NODE_2_X3 value
	 */
	float 				m_NODE_2_X3;

	/**
	 * m_NODE_2_CD value
	 */
	int 				m_NODE_2_CD;

	/**
	 * m_X0 value
	 */
	float 				m_X0;

	/**
	 * m_Y0 value
	 */
	float 				m_Y0;

	/**
	 * m_Z0 value
	 */
	float 				m_Z0;

	/**
	 * m_d value
	 */
	float 				m_d;

	/**
	 * m_NODE_3_ID value
	 */
	int 				m_NODE_3_ID;

	/**
	 * m_NODE_3_CP value
	 */
	int 				m_NODE_3_CP;

	/**
	 * m_NODE_3_X1 value
	 */
	float 				m_NODE_3_X1;

	/**
	 * m_NODE_3_X2 value
	 */
	float 				m_NODE_3_X2;

	/**
	 * m_NODE_3_X3 value
	 */
	float 				m_NODE_3_X3;

	/**
	 * m_NODE_3_CD value
	 */
	int 				m_NODE_3_CD;

	/**
	 * m_Nodes_Adyacent_1 value
	 */
	std::string			m_Nodes_Adyacent_1;

	/**
	 * m_Nodes_Adyacent_2 value
	 */
	std::string			m_Nodes_Adyacent_2;

	/**
	 * m_KINEMATIC_COUPLING_1_2_CARD value
	 */
	std::string 		m_KINEMATIC_COUPLING_1_2_CARD;

	/**
	 * m_NODE_1_CARD value
	 */
	std::string			m_NODE_1_CARD;

	/**
	 * m_NODE_2_CARD value
	 */
	std::string 		m_NODE_2_CARD;

	/**
	 * m_NODE_3_CARD value
	 */
	std::string			m_NODE_3_CARD;

	/**
	 * m_EQUATION_CARD value
	 */
	std::string			m_EQUATION_CARD;

	/**
	 * m_1D_Elm_Asoc_Type value
	 */
	std::string			m_1D_Elm_Asoc_Type;

	/**
	 * m_CoG_NODE value
	 */
	int					m_CoG_NODE;

	/**
	 * m_CoG_NODE_CP value
	 */
	int					m_CoG_NODE_CP;

	/**
	 * m_CoG_NODE_X1 value
	 */
	float				m_CoG_NODE_X1;

	/**
	 * m_CoG_NODE_X2 value
	 */
	float				m_CoG_NODE_X2;

	/**
	 * m_CoG_NODE_X3 value
	 */
	float				m_CoG_NODE_X3;

	/**
	 * m_CoG_NODE_CD value
	 */
	int					m_CoG_NODE_CD;

	/**
	 * m_CoG_NODE_Card value
	 */
	std::string			m_CoG_NODE_Card;

	/**
	 * m_KINEMATIC_COUPLING_CoG_DFEM_CARD value
	 */
	std::string			m_KINEMATIC_COUPLING_CoG_DFEM_CARD;

	/**
	 * m_EQUATION_CARD_CoG_DFEM value
	 */
	std::string			m_EQUATION_CARD_CoG_DFEM;

public:
	CGFEMNode();
	virtual ~CGFEMNode();

	std::string getNODE_1_CARD();

	/**
	 * Getter/Setter of m_GridNode
	 */
	CGridNode* getGridNode() { return m_GridNode; }
	void setGridNode(CGridNode *gridData) { m_GridNode = gridData; }

	/**
	 * Getter/Setter of m_EID_1
	 */
	int getEid_1() const { return m_EID_1; }
	void setEid_1(int eid1) { m_EID_1 = eid1; }

	/**
	 * Getter/Setter of m_EID_2
	 */
	int getEid_2() const { return m_EID_2; }
	void setEid_2(int eid2) { m_EID_2 = eid2; }

	/**
	 * Getter/Setter of m_G1_1
	 */
	int getG1_1() const { return m_G1_1; }
	void setG1_1(int g11) { m_G1_1 = g11; }

	/**
	 * Getter/Setter of m_G2_1
	 */
	int getG2_1() const { return m_G2_1; }
	void setG2_1(int g21) { m_G2_1 = g21; }

	/**
	 * Getter/Setter of m_G3_1
	 */
	int getG3_1() const { return m_G3_1; }
	void setG3_1(int g31) { m_G3_1 = g31; }

	/**
	 * Getter/Setter of m_G4_1
	 */
	int getG4_1() const { return m_G4_1; }
	void setG4_1(int g41) { m_G4_1 = g41; }

	/**
	 * Getter/Setter of m_ZOFFS_1
	 */
	float getZoffs_1() const { return m_ZOFFS_1; }
	void setZoffs_1(float zoffs1) { m_ZOFFS_1 = zoffs1; }

	/**
	 * Getter/Setter of m_d
	 */
	float getD() const { return m_d; }
	void setD(float d) { m_d = d; }

	/**
	 * Getter/Setter of m_G1_1_CP
	 */
	int getG1_1_CP() const { return m_G1_1_CP; }
	void setG1_1_CP(int g11Cp) { m_G1_1_CP = g11Cp; }


	/**
	 * Getter/Setter of m_G1_1_X1
	 */
	float getG1_1_X1() const { return m_G1_1_X1; }
	void setG1_1_X1(float g11X1) { m_G1_1_X1 = g11X1; }

	/**
	 * Getter/Setter of m_G1_1_X2
	 */
	float getG1_1_X2() const { return m_G1_1_X2; }
	void setG1_1_X2(float g11X2) { m_G1_1_X2 = g11X2; }

	/**
	 * Getter/Setter of m_G1_1_X3
	 */
	float getG1_1_X3() const { return m_G1_1_X3; }
	void setG1_1_X3(float g11X3) { m_G1_1_X3 = g11X3; }

	/**
	 * Getter/Setter of m_G1_2
	 */
	int getG1_2() const { return m_G1_2; }
	void setG1_2(int g12) { m_G1_2 = g12; }

	/**
	 * Getter/Setter of m_G1_2_CP
	 */
	int getG1_2_CP() const { return m_G1_2_CP; }
	void setG1_2_CP(int g12Cp) { m_G1_2_CP = g12Cp; }

	/**
	 * Getter/Setter of m_G1_2_X1
	 */
	float getG1_2_X1() const { return m_G1_2_X1; }
	void setG1_2_X1(float g12X1) { m_G1_2_X1 = g12X1; }

	/**
	 * Getter/Setter of m_G1_2_X2
	 */
	float getG1_2_X2() const { return m_G1_2_X2; }
	void setG1_2_X2(float g12X2) { m_G1_2_X2 = g12X2; }

	/**
	 * Getter/Setter of m_G1_2_X3
	 */
	float getG1_2_X3() const { return m_G1_2_X3; }
	void setG1_2_X3(float g12X3) { m_G1_2_X3 = g12X3; }

	/**
	 * Getter/Setter of m_G2_1_CP
	 */
	int getG2_1_CP() const { return m_G2_1_CP; }
	void setG2_1_CP(int g21Cp) { m_G2_1_CP = g21Cp; }

	/**
	 * Getter/Setter of m_G2_1_X1
	 */
	float getG2_1_X1() const { return m_G2_1_X1; }
	void setG2_1_X1(float g21X1) { m_G2_1_X1 = g21X1; }

	/**
	 * Getter/Setter of m_G2_1_X2
	 */
	float getG2_1_X2() const { return m_G2_1_X2; }
	void setG2_1_X2(float g21X2) { m_G2_1_X2 = g21X2; }

	/**
	 * Getter/Setter of m_G2_1_X3
	 */
	float getG2_1_X3() const { return m_G2_1_X3; }
	void setG2_1_X3(float g21X3) { m_G2_1_X3 = g21X3; }

	/**
	 * Getter/Setter of m_G2_2
	 */
	int getG2_2() const { return m_G2_2; }
	void setG2_2(int g22) { m_G2_2 = g22; }

	/**
	 * Getter/Setter of m_G2_2_CP
	 */
	int getG2_2_CP() const { return m_G2_2_CP; }
	void setG2_2_CP(int g22Cp) { m_G2_2_CP = g22Cp; }

	/**
	 * Getter/Setter of m_G2_2_X1
	 */
	float getG2_2_X1() const { return m_G2_2_X1; }
	void setG2_2_X1(float g22X1) { m_G2_2_X1 = g22X1; }

	/**
	 * Getter/Setter of m_G2_2_X2
	 */
	float getG2_2_X2() const { return m_G2_2_X2; }
	void setG2_2_X2(float g22X2) { m_G2_2_X2 = g22X2; }

	/**
	 * Getter/Setter of m_G2_2_X3
	 */
	float getG2_2_X3() const { return m_G2_2_X3; }
	void setG2_2_X3(float g22X3) { m_G2_2_X3 = g22X3; }

	/**
	 * Getter/Setter of m_G3_1_CP
	 */
	int getG3_1_CP() const { return m_G3_1_CP; }
	void setG3_1_CP(int g31Cp) { m_G3_1_CP = g31Cp; }

	/**
	 * Getter/Setter of m_G3_1_X1
	 */
	float getG3_1_X1() const { return m_G3_1_X1; }
	void setG3_1_X1(float g31X1) { m_G3_1_X1 = g31X1; }

	/**
	 * Getter/Setter of m_G3_1_X2
	 */
	float getG3_1_X2() const { return m_G3_1_X2; }
	void setG3_1_X2(float g31X2) { m_G3_1_X2 = g31X2; }

	/**
	 * Getter/Setter of m_G3_1_X3
	 */
	float getG3_1_X3() const { return m_G3_1_X3; }
	void setG3_1_X3(float g31X3) { m_G3_1_X3 = g31X3; }

	/**
	 * Getter/Setter of m_G3_2
	 */
	int getG3_2() const { return m_G3_2; }
	void setG3_2(int g32) { m_G3_2 = g32; }

	/**
	 * Getter/Setter of m_G3_2_CP
	 */
	int getG3_2_CP() const { return m_G3_2_CP; }
	void setG3_2_CP(int g32Cp) { m_G3_2_CP = g32Cp; }

	/**
	 * Getter/Setter of m_G3_2_X1
	 */
	float getG3_2_X1() const { return m_G3_2_X1; }
	void setG3_2_X1(float g32X1) { m_G3_2_X1 = g32X1; }

	/**
	 * Getter/Setter of m_G3_2_X2
	 */
	float getG3_2_X2() const { return m_G3_2_X2; }
	void setG3_2_X2(float g32X2) { m_G3_2_X2 = g32X2; }

	/**
	 * Getter/Setter of m_G3_2_X3
	 */
	float getG3_2_X3() const { return m_G3_2_X3; }
	void setG3_2_X3(float g32X3) { m_G3_2_X3 = g32X3; }

	/**
	 * Getter/Setter of m_G4_2
	 */
	int getG4_2() const { return m_G4_2; }
	void setG4_2(int g42) { m_G4_2 = g42; }

	/**
	 * Getter/Setter of m_NODE_2_CD
	 */
	int getNode_2_CD() const { return m_NODE_2_CD; }
	void setNode_2_CD(int node2Cd) { m_NODE_2_CD = node2Cd; }

	/**
	 * Getter/Setter of m_NODE_2_CP
	 */
	int getNode_2_CP() const { return m_NODE_2_CP; }
	void setNode_2_CP(int node2Cp) { m_NODE_2_CP = node2Cp; }

	/**
	 * Getter/Setter of m_NODE_2_ID
	 */
	int getNode_2_ID() const { return m_NODE_2_ID; }
	void setNode_2_ID(int node2Id) { m_NODE_2_ID = node2Id; }

	/**
	 * Getter/Setter of m_NODE_2_X1
	 */
	float getNode_2_X1() const { return m_NODE_2_X1; }
	void setNode_2_X1(float node2X1) { m_NODE_2_X1 = node2X1; }

	/**
	 * Getter/Setter of m_NODE_2_X2
	 */
	float getNode_2_X2() const { return m_NODE_2_X2; }
	void setNode_2_X2(float node2X2) { m_NODE_2_X2 = node2X2; }

	/**
	 * Getter/Setter of m_NODE_2_X3
	 */
	float getNode_2_X3() const { return m_NODE_2_X3; }
	void setNode_2_X3(float node2X3) { m_NODE_2_X3 = node2X3; }

	/**
	 * Getter/Setter of m_NODE_3_CD
	 */
	int getNode_3_CD() const { return m_NODE_3_CD; }
	void setNode_3_CD(int node3Cd) { m_NODE_3_CD = node3Cd; }

	/**
	 * Getter/Setter of m_NODE_3_CP
	 */
	int getNode_3_CP() const { return m_NODE_3_CP; }
	void setNode_3_CP(int node3Cp) { m_NODE_3_CP = node3Cp; }

	/**
	 * Getter/Setter of m_NODE_3_ID
	 */
	int getNode_3_ID() const { return m_NODE_3_ID; }
	void setNode_3_ID(int node3Id) { m_NODE_3_ID = node3Id; }

	/**
	 * Getter/Setter of m_NODE_3_X1
	 */
	float getNode_3_X1() const { return m_NODE_3_X1; }
	void setNode_3_X1(float node3X1) { m_NODE_3_X1 = node3X1; }

	/**
	 * Getter/Setter of m_NODE_3_X2
	 */
	float getNode_3_X2() const { return m_NODE_3_X2; }
	void setNode_3_X2(float node3X2) { m_NODE_3_X2 = node3X2; }

	/**
	 * Getter/Setter of m_NODE_3_X2
	 */
	float getNode_3_X3() const { return m_NODE_3_X3; }
	void setNode_3_X3(float node3X3) { m_NODE_3_X3 = node3X3; }

	/**
	 * Getter/Setter of m_Nodes_Adyacent_1
	 */
	const std::string& getNodes_Adyacent_1() const { return m_Nodes_Adyacent_1; }
	void setNodes_Adyacent_1(const std::string &nodesAdyacent1) { m_Nodes_Adyacent_1 = nodesAdyacent1; }

	/**
	 * Getter/Setter of m_Nodes_Adyacent_2
	 */
	const std::string& getNodes_Adyacent_2() const { return m_Nodes_Adyacent_2; }
	void setNodes_Adyacent_2(const std::string &nodesAdyacent2) {	m_Nodes_Adyacent_2 = nodesAdyacent2; }

	/**
	 * Getter/Setter of m_V3_X1_NORM
	 */
	float getV3_X1_Norm() const {	return m_V3_X1_NORM; }
	void setV3_X1_Norm(float v3X1Norm) { m_V3_X1_NORM = v3X1Norm; }

	/**
	 * Getter/Setter of m_V3_X2_NORM
	 */
	float getV3_X2_Norm() const { return m_V3_X2_NORM; }
	void setV3_X2_Norm(float v3X2Norm) { m_V3_X2_NORM = v3X2Norm; }

	/**
	 * Getter/Setter of m_V3_X3_NORM
	 */
	float getV3_X3_Norm() const { return m_V3_X3_NORM; }
	void setV3_X3_Norm(float v3X3Norm) { m_V3_X3_NORM = v3X3Norm; }

	/**
	 * Getter/Setter of m_X0
	 */
	float getX0() const { return m_X0; }
	void setX0(float x0) { m_X0 = x0; }

	/**
	 * Getter/Setter of m_Y0
	 */
	float getY0() const { return m_Y0; }
	void setY0(float y0) { m_Y0 = y0; }

	/**
	 * Getter/Setter of m_Z0
	 */
	float getZ0() const { return m_Z0; }
	void setZ0(float z0) { m_Z0 = z0; }

	/**
	 * Getter/Setter of m_ZOFFS
	 */
	float getZOFFS() const { return m_ZOFFS; }
	void setZOFFS(float zoffs) { m_ZOFFS = zoffs; }

	/**
	 * Getter/Setter of m_ZOFFS_1
	 */
	float getZOFFS_1() const { return m_ZOFFS_1; }
	void setZOFFS_1(float zoffs1) { m_ZOFFS_1 = zoffs1; }

	/**
	 * Getter/Setter of m_ZOFFS_2
	 */
	float getZOFFS_2() const { return m_ZOFFS_2; }
	void setZOFFS_2(float zoffs2) { m_ZOFFS_2 = zoffs2; }

	/**
	 * Getter/Setter of m_EQUATION_CARD
	 */
	const std::string& getEQUATION_CARD() const { return m_EQUATION_CARD; }
	void setEQUATION_CARD(const std::string &equationCard) { m_EQUATION_CARD = equationCard; }

	/**
	 * Getter/Setter of m_KINEMATIC_COUPLING_1_2_CARD
	 */
	const std::string& getKINEMATIC_COUPLING_1_2_CARD() const { return m_KINEMATIC_COUPLING_1_2_CARD; }
	void setKINEMATIC_COUPLING_1_2_CARD( const std::string &kinematicCoupling12Card) { m_KINEMATIC_COUPLING_1_2_CARD = kinematicCoupling12Card; }

	/**
	 * Getter/Setter of m_NODE_1_CARD
	 */
	const std::string& getNODE_1_CARD() const { return m_NODE_1_CARD; }
	void setNODE_1_CARD(const std::string &node1Card) { m_NODE_1_CARD = node1Card; }

	/**
	 * Getter/Setter of m_NODE_2_CARD
	 */
	const std::string& getNODE_2_CARD() const { return m_NODE_2_CARD; }
	void setNODE_2_CARD(const std::string &node2Card) { m_NODE_2_CARD = node2Card; }

	/**
	 * Getter/Setter of m_NODE_3_CARD
	 */
	const std::string& getNODE_3_CARD() const { return m_NODE_3_CARD; }
	void setNODE_3_CARD(const std::string &node3Card) { m_NODE_3_CARD = node3Card; }

	/**
	 * Getter/Setter of m_1D_Elm_Asoc_Type
	 */
	const std::string& get1D_Elm_Asoc_Type() const { return m_1D_Elm_Asoc_Type; }
	void set1D_Elm_Asoc_Type(const std::string &_1DElmAsocType) { m_1D_Elm_Asoc_Type = _1DElmAsocType; }

	/**
	 * Getter/Setter of m_CoG_NODE
	 */
	int getCoG_NODE() const { return m_CoG_NODE; }
	void setCoG_NODE(int coGNode) { m_CoG_NODE = coGNode; }

	/**
	 * Getter/Setter of m_CoG_NODE_CD
	 */
	int getCoG_NODE_CD() const { return m_CoG_NODE_CD; }
	void setCoG_NODE_CD(int coGNodeCd) { m_CoG_NODE_CD = coGNodeCd; }

	/**
	 * Getter/Setter of m_CoG_NODE_CP
	 */
	int getCoG_NODE_CP() const { return m_CoG_NODE_CP; }
	void setCoG_NODE_CP(int coGNodeCp) { m_CoG_NODE_CP = coGNodeCp; }

	/**
	 * Getter/Setter of m_CoG_NODE_X1
	 */
	float getCoG_NODE_X1() const { return m_CoG_NODE_X1; }
	void setCoG_NODE_X1(float coGNodeX1) { m_CoG_NODE_X1 = coGNodeX1; }

	/**
	 * Getter/Setter of m_CoG_NODE_X2
	 */
	float getCoG_NODE_X2() const { return m_CoG_NODE_X2; }
	void setCoG_NODE_X2(float coGNodeX2) { m_CoG_NODE_X2 = coGNodeX2; }

	/**
	 * Getter/Setter of m_CoG_NODE_X3
	 */
	float getCoG_NODE_X3() const { return m_CoG_NODE_X3; }
	void setCoG_NODE_X3(float coGNodeX3) { m_CoG_NODE_X3 = coGNodeX3; }

	/**
	 * Getter/Setter of m_EQUATION_CARD_CoG_DFEM
	 */
	const std::string& getEQUATION_CARD_CoG_DFEM() const { return m_EQUATION_CARD_CoG_DFEM; }
	void setEQUATION_CARD_CoG_DFEM(const std::string &equationCardCoGDfem) { m_EQUATION_CARD_CoG_DFEM = equationCardCoGDfem; }

	/**
	 * Getter/Setter of m_CoG_NODE_Card
	 */
	const std::string& getCoG_NODE_Card() const { return m_CoG_NODE_Card; }
	void  setCoG_NODE_Card(const std::string &CoGNODECard) { m_CoG_NODE_Card = CoGNODECard;}

	/**
	 * Getter/Setter of m_KINEMATIC_COUPLING_CoG_DFEM_CARD
	 */
	const std::string& getKINEMATIC_COUPLING_CoG_DFEM_CARD() const { return m_KINEMATIC_COUPLING_CoG_DFEM_CARD; }
	void setKINEMATIC_COUPLING_CoG_DFEM_CARD( const std::string &kinematicCouplingCoGDfemCard) { m_KINEMATIC_COUPLING_CoG_DFEM_CARD = kinematicCouplingCoGDfemCard; }
};

#endif /* GFEMNODE_H_ */
