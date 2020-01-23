/*
 * Segments.h
 *
 *  Created on: 27 nov. 2019
 *      Author: fernando.olivares
 */


#ifndef SEGMENT_H_
#define SEGMENT_H_

#include <string>

class CSegment {
private:

	/**
	 * Unique ID of each Segment
	 */
	std::string m_IdSegment;

	/**
	 * G1 Node
	 */
	std::string		m_G1;

	/**
	 * Coord. X of G1 Node
	 */
	float			m_xG1;

	/**
	 * Coord. Y of G1 Node
	 */
	float			m_yG1;

	/**
	 * Coord. Z of G1 Node
	 */
	float			m_zG1;

	/**
	 * G2 Node
	 */
	std::string		m_G2;

	/**
	 * Coord. X of G2 Node
	 */
	float			m_xG2;

	/**
	 * Coord. Y of G2 Node
	 */
	float			m_yG2;

	/**
	 * Coord. Z of G2 Node
	 */
	float			m_zG2;

	/**
	 * ELSET Name
	 */
	std::string		m_ELSET_NAME;

	/**
	 * T param Value
	 */
	float			m_t;

	/**
	 * L param Value
	 */
	float			m_L;

	/**
	 * Ai Param Value
	 */
	float			m_Ai;

	/**
	 * Coord. X Gi Node
	 */
	float			m_xGi;

	/**
	 * Coord. Y Gi Node
	 */
	float			m_yGi;

	/**
	 * Coord. Z Gi Node
	 */
	float			m_zGi;

	/**
	 * Coord. X Ai-Gi Node
	 */
	float			m_Ai_xGi;

	/**
	 * Coord. Y Ai-Gi Node
	 */
	float			m_Ai_yGi;

	/**
	 * Coord. Z Ai-Gi Node
	 */
	float			m_Ai_zGi;

public:
	CSegment();
	virtual ~CSegment();

	/**
	 * Getter/Setter of m_IdSegment
	 */
	std::string getIdSegment() { return m_IdSegment; }
	void setIdSegment(std::string idSegment) { m_IdSegment = idSegment; }

	/**
	 * Getter/Setter of m_Ai
	 */
	float getAi() const { return m_Ai; }
	void setAi(float ai) { m_Ai = ai; }

	/**
	 * Getter/Setter of m_Ai_xGi
	 */
	float getAi_XGi() const { return m_Ai_xGi; }
	void setAi_XGi(float aiXGi) { m_Ai_xGi = aiXGi; }

	/**
	 * Getter/Setter of m_Ai_yGi
	 */
	float getAi_YGi() const { return m_Ai_yGi; }
	void setAi_YGi(float aiYGi) { m_Ai_yGi = aiYGi; }

	/**
	 * Getter/Setter m_Ai_zGi m_Ai
	 */
	float getAi_ZGi() const { return m_Ai_zGi; }
	void setAi_ZGi(float aiZGi) { m_Ai_zGi = aiZGi; }

	/**
	 * Getter/Setter of m_ELSET_NAME
	 */
	const std::string& getElset_Name() const { return m_ELSET_NAME; }
	void setElsetName(const std::string &elsetName) { m_ELSET_NAME = elsetName; }

	/**
	 * Getter/Setter of m_G1
	 */
	std::string getG1() const { return m_G1; }
	void setG1(std::string g1) { m_G1 = g1; }

	/**
	 * Getter/Setter of m_G2
	 */
	std::string getG2() const { return m_G2; }
	void setG2(std::string g2) { m_G2 = g2; }

	/**
	 * Getter/Setter of m_G2
	 */
	float getL() const { return m_L; }
	void setL(float l) { m_L = l; }

	/**
	 * Getter/Setter of m_t
	 */
	float getT() const { return m_t; }
	void setT(float t) { m_t = t; }

	/**
	 * Getter/Setter of m_xG1
	 */
	float getX_G1() const { return m_xG1; }
	void setX_G1(float xG1) { m_xG1 = xG1; }

	/**
	 * Getter/Setter of m_xG2
	 */
	float getX_G2() const { return m_xG2; }
	void setX_G2(float xG2) { m_xG2 = xG2; }

	/**
	 * Getter/Setter of m_xGi
	 */
	float getX_Gi() const { return m_xGi; }
	void setX_Gi(float xGi) { m_xGi = xGi; }

	/**
	 * Getter/Setter of m_yG1
	 */
	float getY_G1() const { return m_yG1; }
	void setY_G1(float yG1) { m_yG1 = yG1; }

	/**
	 * Getter/Setter of m_yG2
	 */
	float getY_G2() const { return m_yG2; }
	void setY_G2(float yG2) { m_yG2 = yG2; }

	/**
	 * Getter/Setter of m_yGi
	 */
	float getY_Gi() const { return m_yGi; }
	void setY_Gi(float yGi) { m_yGi = yGi; }

	/**
	 * Getter/Setter of m_zG1
	 */
	float getZ_G1() const { return m_zG1; }
	void setZ_G1(float zG1) { m_zG1 = zG1; }

	/**
	 * Getter/Setter of m_zG2
	 */
	float getZ_G2() const { return m_zG2; }
	void setZ_G2(float zG2) { m_zG2 = zG2; }

	/**
	 * Getter/Setter of m_zGi
	 */
	float getZ_Gi() const { return m_zGi; }
	void setZ_Gi(float zGi) { m_zGi = zGi; }
};

#endif /* SEGMENT_H_ */
