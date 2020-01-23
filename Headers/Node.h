/*
 * Node.h
 *
 *  Created on: 12 nov. 2019
 *      Author: NG82748
 */


#ifndef NODE_H_
#define NODE_H_

#include <string>


using namespace std;

class CNode {

public:
	CNode();
	virtual ~CNode();

private:
	/**
	 * m_TieArea value
	 */
	int m_TieArea;

	/**
	 * m_idNode value
	 */
	int m_idNode;

	/**
	 * m_strName value
	 */
	std::string m_strName;

	/**
	 * m_strIdNode value
	 */
	std::string m_strIdNode;

	/**
	 * m_NodeType value
	 */
	int m_NodeType;

public:

	/*
	 * Getter/Setter of m_idNode
	 */
	int getIdNode() { return m_idNode; };
	void setIdNode(int dIdValue) { m_idNode = dIdValue;};

	/*
	 * Getter/Setter of m_strIdNode
	 */
	std::string getStrIdNode() { return m_strIdNode; };
	void setStrIdNode(std::string dIdValue) { m_strIdNode = dIdValue;};

	/*
	 * Getter/Setter of m_strName
	 */
	std::string getName() { return m_strName; };
	void setName(std::string strName) { m_strName = strName; }

	/*
	 * Getter/Setter of m_NodeType
	 */
	int getNodeType() const { return m_NodeType; }
	void setNodeType(int nodeType) { m_NodeType = nodeType; }

	/*
	 * Getter/Setter of Tie Area
	 */
	int getTieArea() const { return m_TieArea; }
	void setTieArea(int tieArea) { m_TieArea = tieArea; }
};

#endif /* NODE_H_ */
