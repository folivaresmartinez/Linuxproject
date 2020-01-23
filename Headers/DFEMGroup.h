/*
 * DFEMGroup.h
 *
 *  Created on: 10 dic. 2019
 *      Author: fernando.olivares
 */

#ifndef DFEMGROUP_H_
#define DFEMGROUP_H_


#include <string>
#include "../Headers/Global.h"

using namespace std;

class CDFEMGroup {
private:

	/**
	 * m_PartName value
	 */
	std::string m_PartName;

	/**
	 * m_InstanceName value
	 */
	std::string m_InstanceName;

	/**
	 * m_MapDFEMData value
	 */
	MapDFEMData 	*m_MapDFEMData;

	/**
	 * m_MapDFEMObjects value
	 */
	MapDFEMObjects 	*m_MapDFEMObjects;

	/**
	 * m_lstSHELLSections value
	 */
	MapSHELLSections *m_MapSHELLSections;

	/**
	 * m_lstSHELLSections value
	 */
	MapELSETSections *m_MapELSETSections;

	/**
	 * m_MapELEMENTSections value
	 */
	MapELEMENTSections *m_MapELEMENTSections;

public:
	CDFEMGroup();
	virtual ~CDFEMGroup();

	/**
	 * Getter/Setter of m_PartName
	 */
	std::string getPartName()  { return m_PartName; }
	void setPartName( std::string partName) { m_PartName = partName; }


	/**
	 * Getter/Setter of m_PartName
	 */
	std::string getInstanceName()  { return m_InstanceName; }
	void setInstanceName( std::string instanceName) { m_InstanceName = instanceName; }

	/**
	 * Getter/Setter of m_MapDFEMData
	 */
	MapDFEMData* getMapDFEMData() { return m_MapDFEMData; }
	void setMapDFEMData(MapDFEMData *mapDfemData) { m_MapDFEMData = mapDfemData; }
	/**
	 * Getter/Setter of m_MapDFEMObjects
	 */
	MapDFEMObjects* getMapDFEMObjects()  { return m_MapDFEMObjects; }
	void setMapDFEMObjects( MapDFEMObjects *mapDfemObjects) { m_MapDFEMObjects = mapDfemObjects;}

	/**
	 * Getter/Setter of m_MapELEMENTSections
	 */
	MapELEMENTSections* getMapElementSections() { return m_MapELEMENTSections; }
	void setMapElementSections( MapELEMENTSections *mapElementSections) { m_MapELEMENTSections = mapElementSections; }

	/**
	 * Getter/Setter of m_MapELSETSections
	 */
	MapELSETSections* getMapElsetSections()  { return m_MapELSETSections; }
	void setMapElsetSections( MapELSETSections *mapElsetSections) { m_MapELSETSections = mapElsetSections; }

	/**
	 * Getter/Setter of m_MapSHELLSections
	 */
	MapSHELLSections* getMapShellSections() { return m_MapSHELLSections; }
	void setMapShellSections(MapSHELLSections *mapShellSections) { m_MapSHELLSections = mapShellSections; }

};

#endif /* DFEMGROUP_H_ */
