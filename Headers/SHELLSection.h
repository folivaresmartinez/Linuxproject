/*
 * SHELLSection.h
 *
 *  Created on: 28 nov. 2019
 *      Author: fernando.olivares
 */


#ifndef SHELLSECTION_H_
#define SHELLSECTION_H_

#include <string>

class CSHELLSection {
private:

	/**
	 * m_ShellName value
	 */
	std::string 	m_ShellName;

	/**
	 * m_ShellMaterial value
	 */
	std::string 	m_ShellMaterial;

	/**
	 * m_ShellValue value
	 */
	float 			m_ShellValue;

public:
	CSHELLSection();
	virtual ~CSHELLSection();

	/**
	 * Getter/Setter of m_ShellName
	 */
	const std::string& getShellName() const { return m_ShellName; }
	void setShellName(const std::string &shellName) { m_ShellName = shellName; }

	/**
	 * Getter/Setter of m_ShellMaterial
	 */
	const std::string& getShellMaterial() const { return m_ShellMaterial; }
	void setShellMaterial(const std::string &shellMaterial) { m_ShellMaterial = shellMaterial; }

	/**
	 * Getter/Setter of m_ShellValue
	 */
	float getShellValue() const { return m_ShellValue; }
	void setShellValue(float shellValue) { m_ShellValue = shellValue; }
};

#endif /* SHELLSECTION_H_ */
