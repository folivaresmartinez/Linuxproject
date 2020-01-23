/*
 * ELSETSection.h
 *
 *  Created on: 28 nov. 2019
 *      Author: fernando.olivares
 */

#ifndef ELSETSECTION_H_
#define ELSETSECTION_H_

#include <string>
#include <list>

class CELSETSection {
private:

	/**
	 * m_ElsetName value
	 */
	std::string 	m_ElsetName;

	/**
	 * m_InstanceName value
	 */
	std::string m_InstanceName;

	/**
	 * m_lstNodes value
	 */
	std::list<std::string>	*m_lstNodes;

public:
	CELSETSection();
	virtual ~CELSETSection();

	/**
	 * Getter/Setter of m_lstNodes
	 */
	std::list<std::string> * getListNodes() { return m_lstNodes; }
	void setListNodes(std::list<std::string> *lstNodes) { m_lstNodes = lstNodes; }

	/**
	 * Getter/Setter of m_ShellName
	 */
	std::string getInstanceName()  { return m_InstanceName; }
	void setInstanceName(const std::string instanceName) { m_InstanceName = instanceName; }

	/**
	 * Getter/Setter of m_ShellName
	 */
	std::string getElsetName()  { return m_ElsetName; }
	void setElsetName(const std::string elsetName) { m_ElsetName = elsetName; }


};

#endif /* ELSETSECTION_H_ */
