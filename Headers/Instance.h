/*
 * Instance.h
 *
 *  Created on: 11 dic. 2019
 *      Author: fernando.olivares
 */

#ifndef INSTANCE_H_
#define INSTANCE_H_

#include <string>

using namespace std;


class CInstance {
private:
	/**
	 * m_InstanceName value
	 */
	std::string m_InstanceName;

	/**
	 * m_PartName value
	 */
	std::string m_PartName;

	/**
	 * m_Value1 value
	 */
	float m_Value1;

	/**
	 * m_Value2 value
	 */
	float m_Value2;

	/**
	 * m_Value3 value
	 */	float m_Value3;

public:
	CInstance();
	virtual ~CInstance();

	/*
	 * Getter/Setter of m_InstanceName
	 */
	std::string getInstanceName() { return m_InstanceName; }
	void setInstanceName(std::string instanceName) { m_InstanceName = instanceName; }

	/*
	 * Getter/Setter of m_PartName
	 */
	std::string getPartName() { return m_PartName; }
	void setPartName(std::string partName) { m_PartName = partName; }

	/*
	 * Getter/Setter of m_PartName
	 */
	float getValue1() { return m_Value1; }
	void setValue1(float value1) { m_Value1 = value1; }

	/*
	 * Getter/Setter of m_Value2
	 */
	float getValue2() { return m_Value2; }
	void setValue2(float value2) { m_Value2 = value2; }

	/*
	 * Getter/Setter of m_Value3
	 */
	float getValue3() { return m_Value3; }
	void setValue3(float value3) { m_Value3 = value3; }
};

#endif /* INSTANCE_H_ */
