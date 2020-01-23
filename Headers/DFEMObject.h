/*
 * CDFEMObject.h
 *
 *  Created on: 22 nov. 2019
 *      Author: fernando.olivares
 */

#ifndef DFEMOBJECT_H_
#define DFEMOBJECT_H_

#include <string>

using namespace std;

class CDFEMObject {
private:

	/**
	 * m_IdNode value
	 */
	std::string m_IdNode;

	/**
	 * m_Coord_X value
	 */
	float m_Coord_X;

	/**
	 * m_Coord_Y value
	 */
	float m_Coord_Y;

	/**
	 * m_Coord_Z value
	 */
	float m_Coord_Z;


public:
	CDFEMObject();
	virtual ~CDFEMObject();


	/**
	 * Getter/Setter of m_Coord_X
	 */
	float getCoord_X() const { return m_Coord_X; }
	void setCoord_X(float coordX) { m_Coord_X = coordX; }

	/**
	 * Getter/Setter of m_Coord_Y
	 */
	float getCoord_Y() const { return m_Coord_Y; }
	void setCoord_Y(float coordY) { m_Coord_Y = coordY; }

	/**
	 * Getter/Setter of m_Coord_Z
	 */
	float getCoord_Z() const { return m_Coord_Z; }
	void setCoord_Z(float coordZ) { m_Coord_Z = coordZ; }

	/**
	 * Getter/Setter of m_IdNode
	 */
	std::string getIdNode() const { return m_IdNode; }
	void setIdNode(std::string idNode) { m_IdNode = idNode; }
};

#endif /* DFEMOBJECT_H_ */
