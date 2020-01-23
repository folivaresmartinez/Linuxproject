/*
 * CDFEMNode.h
 *
 *  Created on: 12 nov. 2019
 *      Author: NG82748
 */

#ifndef DFEMNODE_H_
#define DFEMNODE_H_

#include "../Headers/Node.h"

class CDFEMNode : public CNode{

private:

	/**
	 * m_SYST value
	 */
	int						m_SYST;

	/**
	 * m_x value
	 */
	float					m_x;

	/**
	 * m_y value
	 */
	float					m_y;

	/**
	 * m_z value
	 */
	float					m_z;

	/**
	 * m_Transf value
	 */
	int						m_Transf;

	/**
	 * m_Elm_As_1 value
	 */
	int						m_Elm_As_1;

	/**
	 * m_ELSET_1 value
	 */
	std::string				m_ELSET_1;

	/**
	 * m_G1_Elm_As_1 value
	 */
	int						m_G1_Elm_As_1;

	/**
	 * m_G2_Elm_As_1 value
	 */
	int						m_G2_Elm_As_1;

	/**
	 * m_G3_Elm_As_1 value
	 */
	int						m_G3_Elm_As_1;
	/**
	 * m_G4_Elm_As_1 value
	 */
	int						m_G4_Elm_As_1;

	/**
	 * m_ELSET_2 value
	 */
	int						m_Elm_As_2;

	/**
	 * m_ELSET_2 value
	 */
	std::string				m_ELSET_2;

	/**
	 * m_G1_Elm_As_2 value
	 */
	int						m_G1_Elm_As_2;

	/**
	 * m_G2_Elm_As_2 value
	 */
	int						m_G2_Elm_As_2;

	/**
	 * m_G3_Elm_As_2 value
	 */
	int						m_G3_Elm_As_2;

	/**
	 * m_G4_Elm_As_2 value
	 */
	int						m_G4_Elm_As_2;

	/**
	 * m_Elm_As_3 value
	 */
	int						m_Elm_As_3;

	/**
	 * m_ELSET_3 value
	 */
	std::string				m_ELSET_3;

	/**
	 * m_G1_Elm_As_3 value
	 */
	int						m_G1_Elm_As_3;

	/**
	 * m_G2_Elm_As_3 value
	 */
	int						m_G2_Elm_As_3;

	/**
	 * m_G3_Elm_As_3 value
	 */
	int						m_G3_Elm_As_3;

	/**
	 * m_G4_Elm_As_3 value
	 */
	int						m_G4_Elm_As_3;
	/**
	 * m_Elm_As_4 value
	 */
	int						m_Elm_As_4;

	/**
	 * m_ELSET_4 value
	 */
	std::string				m_ELSET_4;

	/**
	 * m_G1_Elm_As_4 value
	 */
	int						m_G1_Elm_As_4;

	/**
	 * m_G2_Elm_As_4 value
	 */
	int						m_G2_Elm_As_4;

	/**
	 * m_G3_Elm_As_4 value
	 */
	int						m_G3_Elm_As_4;

	/**
	 * m_G4_Elm_As_4 value
	 */
	int						m_G4_Elm_As_4;

	/**
	 * m_t1 value
	 */
	float					m_t1;

	/**
	 * m_t2 value
	 */
	float					m_t2;

	/**
	 * m_t3 value
	 */
	float					m_t3;

	/**
	 * m_t4 value
	 */
	float					m_t4;

	/**
	 * m_segment_1 value
	 */
	std::string				m_segment_1;

	/**
	 * m_Syst_NODE_2_1 value
	 */
	int						m_Syst_NODE_2_1;

	/**
	 * m_X2_1 value
	 */
	float					m_X2_1;

	/**
	 * m_Y2_1 value
	 */
	float					m_Y2_1;

	/**
	 * m_Z2_1 value
	 */
	float					m_Z2_1;

	/**
	 * m_segment_2 value
	 */
	std::string				m_segment_2;

	/**
	 * m_Syst_NODE_2 value
	 */
	int						m_Syst_NODE_2;

	/**
	 * m_X2_2 value
	 */
	float					m_X2_2;

	/**
	 * m_Y2_2 value
	 */
	float					m_Y2_2;

	/**
	 * m_Z2_2 value
	 */
	float					m_Z2_2;

	/**
	 * m_segment_3 value
	 */
	std::string				m_segment_3;

	/**
	 * m_Syst_NODE_2_3 value
	 */
	int						m_Syst_NODE_2_3;

	/**
	 * m_X2_3 value
	 */
	float					m_X2_3;

	/**
	 * m_Y2_3 value
	 */
	float					m_Y2_3;

	/**
	 * m_Z2_3 value
	 */
	float					m_Z2_3;

	/**
	 * m_segment_4 value
	 */
	std::string				m_segment_4;

	/**
	 * m_Syst_NODE_2_4 value
	 */
	int						m_Syst_NODE_2_4;

	/**
	 * m_X2_4 value
	 */
	float					m_X2_4;

	/**
	 * m_Y2_4 value
	 */
	float					m_Y2_4;

	/**
	 * m_Z2_4 value
	 */
	float					m_Z2_4;

	/**
	 * m_Segment_1_xG value
	 */
	float					m_Segment_1_xG;

	/**
	 * m_segment_1_yG value
	 */
	float					m_segment_1_yG;

	/**
	 * m_segment_1_zG value
	 */
	float					m_segment_1_zG;

	/**
	 * m_segment_1_L value
	 */
	float					m_segment_1_L;

	/**
	 * m_segment_1_A value
	 */
	float					m_segment_1_A;

	/**
	 * m_segment_2_xG value
	 */
	float					m_segment_2_xG;

	/**
	 * m_segment_2_yG value
	 */
	float					m_segment_2_yG;

	/**
	 * m_segment_2_zG value
	 */
	float					m_segment_2_zG;

	/**
	 * m_segment_2_L value
	 */
	float					m_segment_2_L;

	/**
	 * m_segment_3_yG value
	 */
	float					m_segment_2_A;

	/**
	 * m_segment_3_yG value
	 */
	float					m_Segment_3_xG;

	/**
	 * m_segment_3_yG value
	 */
	float					m_segment_3_yG;

	/**
	 * m_segment_3_zG value
	 */
	float					m_segment_3_zG;

	/**
	 * m_segment_3_L value
	 */
	float					m_segment_3_L;

	/**
	 * m_segment_3_A value
	 */
	float					m_segment_3_A;

	/**
	 * m_segment_4_xG value
	 */
	float					m_segment_4_xG;

	/**
	 * m_segment_4_yG value
	 */
	float					m_segment_4_yG;

	/**
	 * m_segment_4_zG value
	 */
	float					m_segment_4_zG;

	/**
	 * m_segment_4_L value
	 */
	float					m_segment_4_L;

	/**
	 * m_segment_4_A value
	 */
	float					m_segment_4_A;


public:
	CDFEMNode();
	virtual ~CDFEMNode();

	/**
	 * Getter/Setter of m_Elm_As_1
	 */
	int getElm_As_1() const { return m_Elm_As_1; }
	void setElm_As_1(int elmAs1) { m_Elm_As_1 = elmAs1; }

	/**
	 * Getter/Setter of m_Elm_As_2
	 */
	int getElm_As_2() const { return m_Elm_As_2; }
	void setElm_As_2(int elmAs2) { m_Elm_As_2 = elmAs2; }

	/**
	 * Getter/Setter of m_Elm_As_3
	 */
	int getElm_As_3() const { return m_Elm_As_3; }
	void setElm_As_3(int elmAs3) { m_Elm_As_3 = elmAs3; }

	/**
	 * Getter/Setter of m_Elm_As_4
	 */
	int getElm_As_4() const { return m_Elm_As_4; }
	void setElm_As_4(int elmAs4) { m_Elm_As_4 = elmAs4; }

	/**
	 * Getter/Setter of m_ELSET_1
	 */
	const std::string& getELSET_1() const { return m_ELSET_1; }
	void setELSET_1(const std::string &elset1) { m_ELSET_1 = elset1; }

	/**
	 * Getter/Setter of m_ELSET_2
	 */
	const std::string& getELSET_2() const { return m_ELSET_2; }
	void setELSET_2(const std::string &elset2) { m_ELSET_2 = elset2; }

	/**
	 * Getter/Setter of m_ELSET_3
	 */
	const std::string& getELSET_3() const { return m_ELSET_3; }
	void setELSET_3(const std::string &elset3) { m_ELSET_3 = elset3; }

	/**
	 * Getter/Setter of m_ELSET_4
	 */
	const std::string& getELSET_4() const { return m_ELSET_4; }
	void setELSET_4(const std::string &elset4) { m_ELSET_4 = elset4; }

	/**
	 * Getter/Setter of m_G1_Elm_As_1
	 */
	int getG1_Elm_As_1() const { return m_G1_Elm_As_1; }
	void setG1_Elm_As_1(int g1ElmAs1) { m_G1_Elm_As_1 = g1ElmAs1; }

	/**
	 * Getter/Setter of m_G1_Elm_As_2
	 */
	int getG1_Elm_As_2() const { return m_G1_Elm_As_2; }
	void setG1_Elm_As_2(int g1ElmAs2) { m_G1_Elm_As_2 = g1ElmAs2; }

	/**
	 * Getter/Setter of m_G1_Elm_As_3
	 */
	int getG1_Elm_As_3() const { return m_G1_Elm_As_3; }
	void setG1_Elm_As_3(int g1ElmAs3) { m_G1_Elm_As_3 = g1ElmAs3; }

	/**
	 * Getter/Setter of m_G1_Elm_As_4
	 */
	int getG1_Elm_As_4() const { return m_G1_Elm_As_4; }
	void setG1_Elm_As_4(int g1ElmAs4) { m_G1_Elm_As_4 = g1ElmAs4; }

	/**
	 * Getter/Setter of m_G2_Elm_As_1
	 */
	int getG2_Elm_As_1() const { return m_G2_Elm_As_1; }
	void setG2_Elm_As_1(int g2ElmAs1) { m_G2_Elm_As_1 = g2ElmAs1; }

	/**
	 * Getter/Setter of m_G2_Elm_As_2
	 */
	int getG2_Elm_As_2() const { return m_G2_Elm_As_2; }
	void setG2_Elm_As_2(int g2ElmAs2) { m_G2_Elm_As_2 = g2ElmAs2; }

	/**
	 * Getter/Setter of m_G2_Elm_As_3
	 */
	int getG2_Elm_As_3() const { return m_G2_Elm_As_3; }
	void setG2_Elm_As_3(int g2ElmAs3) { m_G2_Elm_As_3 = g2ElmAs3; }

	/**
	 * Getter/Setter of m_G3_Elm_As_1
	 */
	int getG3_Elm_As_1() const { return m_G3_Elm_As_1; }
	void setG3_Elm_As_1(int g3ElmAs1) { m_G3_Elm_As_1 = g3ElmAs1; }

	/**
	 * Getter/Setter of m_G3_Elm_As_2
	 */
	int getG3_Elm_As_2() const { return m_G3_Elm_As_2; }
	void setG3_Elm_As_2(int g3ElmAs2) { m_G3_Elm_As_2 = g3ElmAs2; }

	/**
	 * Getter/Setter of m_G3_Elm_As_3
	 */
	int getG3_Elm_As_3() const { return m_G3_Elm_As_3; }
	void setG3_Elm_As_3(int g3ElmAs3) { m_G3_Elm_As_3 = g3ElmAs3; }

	/**
	 * Getter/Setter of m_G3_Elm_As_4
	 */
	int getG3_Elm_As_4() const { return m_G3_Elm_As_4; }
	void setG3_Elm_As_4(int g3ElmAs4) { m_G3_Elm_As_4 = g3ElmAs4; }


	/**
	 * Getter/Setter of m_G2_Elm_As_4
	 */
	int getG2_Elm_As_4() const { return m_G2_Elm_As_4; }
	void setG2_Elm_As_4(int g2ElmAs4) { m_G2_Elm_As_4 = g2ElmAs4; }

	/**
	 * Getter/Setter of m_G4_Elm_As_1
	 */
	int getG4_Elm_As_1() const { return m_G4_Elm_As_1; }
	void setG4_Elm_As_1(int g4ElmAs1) { m_G4_Elm_As_1 = g4ElmAs1; }

	/**
	 * Getter/Setter of m_G4_Elm_As_2
	 */
	int getG4_Elm_As_2() const { return m_G4_Elm_As_2; }
	void setG4_Elm_As_2(int g4ElmAs2) { m_G4_Elm_As_2 = g4ElmAs2; }

	/**
	 * Getter/Setter of m_G4_Elm_As_3
	 */
	int getG4_Elm_As_3() const { return m_G4_Elm_As_3; }
	void setG4_Elm_As_3(int g4ElmAs3) { m_G4_Elm_As_3 = g4ElmAs3; }

	/**
	 * Getter/Setter of m_G4_Elm_As_4
	 */
	int getG4_Elm_As_4() const { return m_G4_Elm_As_4; }
	void setG4_Elm_As_4(int g4ElmAs4) { m_G4_Elm_As_4 = g4ElmAs4; }

	/**
	 * Getter/Setter of m_segment_1
	 */
	const std::string& getSegment_1() const { return m_segment_1; }
	void setSegment_1(const std::string &segment1) { m_segment_1 = segment1; }

	/**
	 * Getter/Setter of m_segment_1_A
	 */
	float getsegment_1_A() const { return m_segment_1_A; }
	void setsegment_1_A(float segment1A) { m_segment_1_A = segment1A; }

	/**
	 * Getter/Setter of m_segment_1_L
	 */
	float getsegment_1_L() const { return m_segment_1_L; }
	void setsegment_1_L(float segment1L) { m_segment_1_L = segment1L; }

	/**
	 * Getter/Setter of m_Segment_1_xG
	 */
	float getSegment_1_xG() const { return m_Segment_1_xG; }
	void setSegment_1_xG(float segment1XG) { m_Segment_1_xG = segment1XG; }

	/**
	 * Getter/Setter of m_segment_1_yG
	 */
	float getSegment_1_yG() const { return m_segment_1_yG; }
	void setSegment_1_yG(float segment1YG) { m_segment_1_yG = segment1YG; }

	/**
	 * Getter/Setter of m_segment_1_zG
	 */
	float getSegment_1_zG() const { return m_segment_1_zG; }
	void setSegment_1_zG(float segment1ZG) { m_segment_1_zG = segment1ZG; }

	/**
	 * Getter/Setter of m_segment_2
	 */
	const std::string& getsegment_2() const { return m_segment_2; }
	void setSegment_2(const std::string &segment2) { m_segment_2 = segment2; }

	/**
	 * Getter/Setter of m_segment_2_A
	 */
	float getSegment_2_A() const { return m_segment_2_A; }
	void setSegment_2_A(float segment2A) { m_segment_2_A = segment2A; }

	/**
	 * Getter/Setter of m_segment_2_L
	 */
	float getSegment_2_L() const { return m_segment_2_L; }
	void setSegment_2_L(float segment2L) { m_segment_2_L = segment2L; }

	/**
	 * Getter/Setter of m_segment_2_xG
	 */
	float getSegment_2_xG() const { return m_segment_2_xG; }
	void setSegment_2_xG(float segment2XG) { m_segment_2_xG = segment2XG; }

	/**
	 * Getter/Setter of m_segment_2_yG
	 */
	float getSegment_2_yG() const { return m_segment_2_yG; }
	void setSegment_2_yG(float segment2YG) { m_segment_2_yG = segment2YG; }

	/**
	 * Getter/Setter of m_segment_2_zG
	 */
	float getSegment_2_zG() const { return m_segment_2_zG; }
	void setSegment_2_zG(float segment2ZG) { m_segment_2_zG = segment2ZG; }

	/**
	 * Getter/Setter of m_segment_3
	 */
	const std::string& getSegment_3() const { return m_segment_3; }
	void setSegment_3(const std::string &segment3) { m_segment_3 = segment3; }

	/**
	 * Getter/Setter of m_segment_3_A
	 */
	float getSegment_3_A() const { return m_segment_3_A; }
	void setSegment_3_A(float segment3A) { m_segment_3_A = segment3A; }

	/**
	 * Getter/Setter of m_segment_3_L
	 */
	float getSegment_3_L() const { return m_segment_3_L; }
	void setSegment_3_L(float segment3L) { m_segment_3_L = segment3L; }

	/**
	 * Getter/Setter of m_Segment_3_xG
	 */
	float getSegment_3_xG() const { return m_Segment_3_xG; }
	void setSegment_3_xG(float segment3XG) { m_Segment_3_xG = segment3XG; }

	/**
	 * Getter/Setter of m_segment_3_yG
	 */
	float getSegment_3_yG() const { return m_segment_3_yG; }
	void setSegment_3_yG(float segment3YG) { m_segment_3_yG = segment3YG; }

	/**
	 * Getter/Setter of m_segment_3_zG
	 */
	float getSegment_3_zG() const { return m_segment_3_zG; }
	void setSegment_3_zG(float segment3ZG) { m_segment_3_zG = segment3ZG; }

	/**
	 * Getter/Setter of m_segment_4
	 */
	const std::string& getSegment_4() const { return m_segment_4; }
	void setSegment_4(const std::string &segment4) { m_segment_4 = segment4; }

	/**
	 * Getter/Setter of m_segment_4_A
	 */
	float getSegment_4_A() const { return m_segment_4_A; }
	void setSegment_4_A(float segment4A) { m_segment_4_A = segment4A; }

	/**
	 * Getter/Setter of m_segment_4_L
	 */
	float getSegment_4_L() const { return m_segment_4_L; }
	void setSegment_4_L(float segment4L) { m_segment_4_L = segment4L; }

	/**
	 * Getter/Setter of m_segment_4_yG
	 */
	float getSegment_4_xG() const { return m_segment_4_xG; }
	void setSegment_4_xG(float segment4XG) { m_segment_4_xG = segment4XG; }

	/**
	 * Getter/Setter of m_segment_4_yG
	 */
	float getSegment_4_yG() const { return m_segment_4_yG; }
	void setSegment_4_yG(float segment4YG) { m_segment_4_yG = segment4YG; }

	/**
	 * Getter/Setter of m_segment_4_zG
	 */
	float getSegment_4_zG() const { return m_segment_4_zG; }
	void setSegment_4_zG(float segment4ZG) { m_segment_4_zG = segment4ZG; }

	/**
	 * Getter/Setter of m_SYST
	 */
	int getSYST() const { return m_SYST; }
	void setSYST(int syst) { m_SYST = syst; }

	/**
	 * Getter/Setter of m_Syst_NODE_2
	 */
	int getSyst_NODE_2() const { return m_Syst_NODE_2; }
	void setSyst_NODE_2(int systNode2) { m_Syst_NODE_2 = systNode2; }

	/**
	 * Getter/Setter of m_Syst_NODE_2_1
	 */
	int getSyst_NODE_2_1() const { return m_Syst_NODE_2_1; }
	void setSyst_NODE_2_1(int systNode21) { m_Syst_NODE_2_1 = systNode21; }

	/**
	 * Getter/Setter of m_Syst_NODE_2_3
	 */
	int getSyst_NODE_2_3() const { return m_Syst_NODE_2_3; }
	void setSyst_NODE_2_3(int systNode23) { m_Syst_NODE_2_3 = systNode23; }

	/**
	 * Getter/Setter of m_Syst_NODE_2_4
	 */
	int getSyst_NODE_2_4() const { return m_Syst_NODE_2_4; }
	void setSyst_NODE_2_4(int systNode24) { m_Syst_NODE_2_4 = systNode24; }

	/**
	 * Getter/Setter of m_t1
	 */
	float getT1() const { return m_t1; }
	void setT1(float t1) {  m_t1 = t1;}

	/**
	 * Getter/Setter of m_t2
	 */
	float getT2() const { return m_t2; }
	void setT2(float t2) { m_t2 = t2; }

	/**
	 * Getter/Setter of m_t3
	 */
	float getT3() const { return m_t3; }
	void setT3(float t3) { m_t3 = t3; }

	/**
	 * Getter/Setter of m_t4
	 */
	float getT4() const { return m_t4; }
	void setT4(float t4) { m_t4 = t4; }

	/**
	 * Getter/Setter of m_Transf
	 */
	int getTransf() const { return m_Transf; }
	void setTransf(int transf) { m_Transf = transf; }

	/**
	 * Getter/Setter of m_x
	 */
	float getX() const { return m_x; }
	void setX(float x) { m_x = x; }

	/**
	 * Getter/Setter of m_X2_1
	 */
	float getX2_1() const { return m_X2_1; }
	void setX2_1(float x21) { m_X2_1 = x21; }

	/**
	 * Getter/Setter of m_X2_2
	 */
	float getX2_2() const { return m_X2_2; }
	void setX2_2(float x22) { m_X2_2 = x22; }

	/**
	 * Getter/Setter of m_X2_3
	 */
	float getX2_3() const { return m_X2_3; }
	void setX2_3(float x23) { m_X2_3 = x23; }

	/**
	 * Getter/Setter of m_X2_4
	 */
	float getX2_4() const { return m_X2_4; }
	void setX2_4(float x24) { m_X2_4 = x24; }

	/**
	 * Getter/Setter of m_y
	 */
	float getY() const { return m_y; }
	void setY(float y) { m_y = y; }

	/**
	 * Getter/Setter of m_Y2_1
	 */
	float getY2_1() const { return m_Y2_1; }
	void setY2_1(float y21) { m_Y2_1 = y21; }

	/**
	 * Getter/Setter of m_Y2_2
	 */
	float getY2_2() const { return m_Y2_2; }
	void setY2_2(float y22) { m_Y2_2 = y22; }

	/**
	 * Getter/Setter of m_Y2_3
	 */
	float getY2_3() const { return m_Y2_3; }
	void setY2_3(float y23) { m_Y2_3 = y23; }

	/**
	 * Getter/Setter of m_Y2_4
	 */
	float getY2_4() const { return m_Y2_4; }
	void setY2_4(float y24) { m_Y2_4 = y24; }

	/**
	 * Getter/Setter of m_z
	 */
	float getZ() const { return m_z; }
	void setZ(float z) { m_z = z; }

	/**
	 * Getter/Setter of m_Z2_1
	 */
	float getZ2_1() const { return m_Z2_1; }
	void setZ2_1(float z21) { m_Z2_1 = z21; }

	/**
	 * Getter/Setter of m_Z2_2
	 */
	float getZ2_2() const { return m_Z2_2; }
	void setZ2_2(float z22) { m_Z2_2 = z22; }

	/**
	 * Getter/Setter of m_Z2_3
	 */
	float getZ2_3() const { return m_Z2_3; }
	void setZ2_3(float z23) { m_Z2_3 = z23; }

	/**
	 * Getter/Setter of m_Z2_4
	 */
	float getZ2_4() const { return m_Z2_4; }
	void setZ2_4(float z24) { m_Z2_4 = z24; }
};

#endif /* DFEMNODE_H_ */
