/*
 * GridNode.h
 *
 *  Created on: 15 nov. 2019
 *      Author: fernando.olivares
 */


#ifndef GRIDNODE_H_
#define GRIDNODE_H_

class CGridNode {
private:
	long m_idNode;

	int m_CP;
	float m_CoordX1;
	float m_CoordX2;
	float m_CoordX3;
	int m_CD;

public:
	CGridNode();
	virtual ~CGridNode();

public:

	CGridNode * 		LocalToGlobal();

	long getIdNode() const { return m_idNode; }
	void setIdNode(long idNode) { m_idNode = idNode; }

	int getCD() const { return m_CD; }
	void setCD(int cd) { m_CD = cd; }

	float getCoord_X1() const { return m_CoordX1; }
	void setCoord_X1(float coordX1) { m_CoordX1 = coordX1; }

	float getCoord_X2() const { return m_CoordX2; }
	void setCoord_X2(float coordX2) { m_CoordX2 = coordX2; }

	float getCoord_X3() const { return m_CoordX3; }
	void setCoord_X3(float coordX3) { m_CoordX3 = coordX3; }

	int getCP() const { return m_CP; }
	void setCP(int cp) { m_CP = cp; }

};

#endif /* GRIDNODE_H_ */
