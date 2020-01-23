/*
 * QUAD4Node.h
 *
 *  Created on: 18 nov. 2019
 *      Author: fernando.olivares
 */

#ifndef CQUAD4NODE_H_
#define CQUAD4NODE_H_

class CCQUAD4Node {
private:
	/**
	 * m_EID value
	 */
	int		m_EID;

	/**
	 * m_PID value
	 */
	int		m_PID;

	/**
	 * m_G1 value
	 */
	int		m_G1;

	/**
	 * m_G2 value
	 */
	int		m_G2;

	/**
	 * m_G3 value
	 */
	int		m_G3;

	/**
	 * m_G4 value
	 */
	int		m_G4;

	/**
	 * m_THETA_MCID value
	 */
	float	m_THETA_MCID;
	/**
	 * m_ZOOFS value
	 */
	float	m_ZOOFS;

public:
	CCQUAD4Node();
	virtual ~CCQUAD4Node();

	/**
	 * Getter/Setter of m_EID
	 */
	int getEID() const { return m_EID; }
	void setEID(int eid) { m_EID = eid; }

	/**
	 * Getter/Setter of m_G1
	 */
	int getG1() const { return m_G1; }
	void setG1(int g1) { m_G1 = g1; }

	/**
	 * Getter/Setter of m_G2
	 */
	int getG2() const { return m_G2; }
	void setG2(int g2) { m_G2 = g2; }

	/**
	 * Getter/Setter of m_G3
	 */
	int getG3() const { return m_G3; }
	void setG3(int g3) { m_G3 = g3; }

	/**
	 * Getter/Setter of m_G4
	 */
	int getG4() const { return m_G4; }
	void setG4(int g4) { m_G4 = g4; }

	/**
	 * Getter/Setter of m_PID
	 */
	int getPID() const { return m_PID; }
	void setPID(int pid) { m_PID = pid; }

	/**
	 * Getter/Setter of m_THETA_MCID
	 */
	int getTHETA_MCID() const { return m_THETA_MCID; }
	void setTHETA_MCID(int thetaMcid) { m_THETA_MCID = thetaMcid; }

	/**
	 * Getter/Setter of m_ZOOFS
	 */float getZOFFS() const { return m_ZOOFS; }
	void setZOFFS(float zoofs) { m_ZOOFS = zoofs; }
};

#endif /* CQUAD4NODE_H_ */

