/*
 * Coordinate3D.h
 *
 *  Created on: 22 nov. 2019
 *      Author: fernando.olivares
 */

#ifndef COORDINATE3D_H_
#define COORDINATE3D_H_

class CCoordinate3D {
	/**
	 * m_X value
	 */
	float m_X;

	/**
	 * m_Y value
	 */
	float m_Y;

	/**
	 * m_Z value
	 */
	float m_Z;
public:
	CCoordinate3D();
	virtual ~CCoordinate3D();

	/**
	 * Getter/Setter of m_X
	 */
	float getX() const { return m_X; }
	void setX(float x) { m_X = x; }

	/**
	 * Getter/Setter of m_X
	 */
	float getY() const { return m_Y; }
	void setY(float y) { m_Y = y; }

	/**
	 * Getter/Setter of m_Z
	 */
	float getZ() const { return m_Z; }
	void setZ(float z) { m_Z = z; }
};

#endif /* COORDINATE3D_H_ */
