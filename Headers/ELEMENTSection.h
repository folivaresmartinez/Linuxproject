/*
 * ELEMTSSection.h
 *
 *  Created on: 28 nov. 2019
 *      Author: fernando.olivares
 */

#ifndef ELEMENTSECTION_H_
#define ELEMENTSECTION_H_

#include <string>
#include <list>

class CELEMENTSection {
private:
	/**
	 * m_ElementName value
	 */
	std::string 	m_ElementName;

	/**
	 * m_ElementName value
	 */
	std::string 	m_InstanceName;

	/**
	 * m_lstNodes value
	 */
	std::list<std::string>	*m_lstNodes;
public:
	CELEMENTSection();
	virtual ~CELEMENTSection();

	/**
	 * Getter/Setter of m_ElementName
	 */
	std::string getElementName()  { return m_ElementName; }
	void setElementName(const std::string elementName) { m_ElementName = elementName; }

	/**
	 * Getter/Setter of m_InstanceName
	 */
	std::string getInstanceName()  { return m_InstanceName; }
	void setInstanceName(const std::string instanceName) { m_InstanceName = instanceName; }


	/**
	 * Getter/Setter of m_lstNodes
	 */
	std::list<std::string>* getListNodes() { return m_lstNodes; }
	void setListNodes(std::list<std::string> *lstNodes) { m_lstNodes = lstNodes; }
};

#endif /* ELEMENTSECTION_H_ */
