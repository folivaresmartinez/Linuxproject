/*
 * CConnection2D2D.h
 *
 *  Created on: 12 nov. 2019
 *      Author: NG82748
 */


#ifndef CONNECTION_H_
#define CONNECTION_H_

#include <iostream>
#include <list>
#include <map>


class CGFEMNode;
class CDFEMNode;
class CSegment;

/**
* Class that implements the operations to generate the data associated to each one of the connections objects.
 */

class CConnection {
private:

	/**
	 * Id Connection
	 */
	int m_IdConnection;

	/**
	 * Tie Area
	 */
	int m_TieArea;

	/**
	 * String to store the elements T3D2 with ABAQUS format
	 */
	std::string m_strT3D2ABAQUS;

	/**
	 * XCoG value
	 */
	float m_XCoG = 0;

	/**
	 * YCoG value
	 */
	float m_YCoG = 0;

	/**
	 * ZCoG value
	 */
	float m_ZCoG = 0;

	/**
	 * m_IdCoGNode value
	 */
	int m_IdCoGNode;

	/**
	 * Map to store the GFEM Nodes
	 */
	std::map<int, CGFEMNode *> *m_mapGFEMNodes;

	/**
	 * Map to store the DFEM Nodes
	 */
	std::map<std::string, CDFEMNode *> *m_mapDFEMNodes;

	/**
	 * Map to store the segments associated to the 1D2D connections
	 */
	std::map<std::string, CSegment *> *m_mapSegments;

	/**
	 * Aux MAtrix Data
	 */
	std::list<std::list<std::string> *> *m_MatrixData;


public:

	/**
	 * Getter/Setter of IdConnection propertie
	 */
	int getIdConnection() const { return m_IdConnection; }
	void setIdConnection(int idConnection) { m_IdConnection = idConnection; }

	/*
	 * Getter/Setter of Tie Area
	 */
	int getTieArea() const { return m_TieArea; }
	void setTieArea(int tieArea) { m_TieArea = tieArea; }

	/*
	 * Getter/Setter of Tie Area
	 */
	int getIdCoGNode() const { return m_IdCoGNode; }
	void setIdCoGNode(int idcognode) { m_IdCoGNode = idcognode; }


	/*
	 * Getter/Setter of T3D2 Abaqus string
	 */
	const std::string& getStrT3D2Abaqus() const { return m_strT3D2ABAQUS; }
	void setStrT3D2Abaqus(const std::string &strT3D2Abaqus) { m_strT3D2ABAQUS = strT3D2Abaqus; }

	 /**
	  * Getter of the map GFEM.
	  **/
	std::map<std::string, CSegment *> * GetMapSegments() { return m_mapSegments;}

	 /**
	  * Getter of the map GFEM.
	  **/
	std::map<int, CGFEMNode *> * GetGFEMNodes() { return m_mapGFEMNodes;}

	/*
	 * Getter of map DFEM Nodes
	 */
	std::map<std::string, CDFEMNode *> * GetDFEMNodes() { return m_mapDFEMNodes;}


	/**
	 * Getter/Setter of MatrixData
	 */
	std::list<std::list<std::string> *> * GetMatrixData() { return m_MatrixData; }
	void SetMatrixData(std::list<std::list<std::string> *> *matrix) { m_MatrixData = matrix; }


	/**
	 * Getter/Setter of m_XCoG
	 */
	float getXCoG() const { return m_XCoG; }
	void setXCoG(float xCoG = 0) { m_XCoG = xCoG; }

	/**
	 * Getter/Setter of m_XCoG
	 */
	float getYCoG() const { return m_YCoG; }
	void setYCoG(float yCoG = 0) { m_YCoG = yCoG; }

	/**
	 * Getter/Setter of m_ZCoG
	 */
	float getZCoG() const { return m_ZCoG; }
	void setZCoG(float zCoG = 0) { m_ZCoG = zCoG; }

public:
	CConnection();
	virtual ~CConnection();
};

#endif /* CONNECTION_H_ */
