/*
 * VectorPlano.cpp
 *
 *  Created on: 20 nov. 2019
 *      Author: fernando.olivares
 */

#include "../Headers/Vector3D.h"
#include "../Headers/Global.h"

#include <iostream>
#include <cmath>


CVector3D::CVector3D() {
	m_CP 	= ZERO;
	m_V_X1 	= ZERO;
	m_V_X2 	= ZERO;
	m_V_X3 	= ZERO;
}

CVector3D::~CVector3D() {
	// TODO Auto-generated destructor stub
}

void CVector3D::Normalize()
{
    float fLenth = std::sqrt(m_V_X1 * m_V_X1 + m_V_X2 * m_V_X2 + m_V_X3 * m_V_X3);

    if (fLenth != 0)
    {
    	m_V_X1 /= fLenth;
    	m_V_X2 /= fLenth;
    	m_V_X3 /= fLenth;
    }
}
