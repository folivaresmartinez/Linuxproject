/*
 * Vector3D.h
 *
 *  Created on: 20 nov. 2019
 *      Author: fernando.olivares
 */


#ifndef VECTOR3D_H_
#define VECTOR3D_H_

class CVector3D {
private:

	/**
	 * m_CP value
	 */
	int m_CP;

	/**
	 * m_V_X1 value
	 */
	float m_V_X1;

	/**
	 * m_V_X2 value
	 */
	float m_V_X2;

	/**
	 * m_V_X3 value
	 */
	float m_V_X3;
public:

	/**
	 * Default Constructor
	 */
	CVector3D();

	/**
	 * Default Destructor
	 */
	virtual ~CVector3D();

	/**
	 * Method that implement the operation to normalize a vector
	 */
	void 			Normalize();

	 /**
	  * Getter/Setter of m_CP.
	  **/
	int 			getCP() const { return m_CP; }
	void 			setCP(int cp) { m_CP = cp; }

	 /**
	  * Getter/Setter of m_V_X1.
	  **/
	float 			getV_X1() const { return m_V_X1; }
	void 			setV_X1(float vX1) { m_V_X1 = vX1; }

	 /**
	  * Getter/Setter of m_V_X2.
	  **/
	float 			getV_X2() const { return m_V_X2; }
	void 			setV_X2(float vX2) { m_V_X2 = vX2; }

	 /**
	  * Getter/Setter of m_V_X3.
	  **/
	float 			getV_X3() const { return m_V_X3; }
	void 			setV_X3(float vX3) { m_V_X3 = vX3; }
};

#endif /* VECTOR3D_H_ */
