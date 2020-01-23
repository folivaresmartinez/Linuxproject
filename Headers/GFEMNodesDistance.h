/*
 * SourfaceNodesDistanceStore.h
 *
 *  Created on: 25 nov. 2019
 *      Author: fernando.olivares
 */


#ifndef GFEMNODESDISTANCE_H_
#define GFEMNODESDISTANCE_H_
#include <string>

using namespace std;

class CGFEMNodesDistance {
	int m_IdConnection;

	long 			m_idNodeGFEM;
	std::string 	m_idNodeDFEM;

	double m_Distance;

public:
	CGFEMNodesDistance();
	virtual ~CGFEMNodesDistance();

	double getDistance() const { return m_Distance; }
	void setDistance(double distance) { m_Distance = distance; }

	int getIdConnection() const { return m_IdConnection; }
	void setIdConnection(int idConnection) { m_IdConnection = idConnection; }

	int getIdNodeGFEM() const { return m_idNodeGFEM; }
	void setIdNodeGFEM(int idNodeFrom) { m_idNodeGFEM = idNodeFrom; }

	std::string getIdNodeDFEM() const { return m_idNodeDFEM; }
	void setIdNodeDFEM(std::string idNodeTo) { m_idNodeDFEM = idNodeTo; }
};

#endif /* GFEMNODESDISTANCE_H_ */
