/*
 * GlobalDFEMReader.h
 *
 *  Created on: 5 dic. 2019
 *      Author: fernando.olivares
 */

#ifndef GLOBALDFEMREADER_H_
#define GLOBALDFEMREADER_H_

#include <list>
#include <string>
#include <map>
#include "Global.h"

using namespace std;

class CGlobalDFEMReader {

private:

	/**
	 * m_PathFile value
	 */
	std::string 	m_PathFile;

	/**
	 * m_PathRoot value
	 */
	std::string 	m_PathRoot;

	/**
	 * m_strDelimiter value
	 */
	std::string 	m_strDelimiter;

	/**
	 * m_lstPathDataFiles value
	 */
	ListStringData *m_lstPathDataFiles;

	/**
	 * m_lstPathInstanceFiles value
	 */
	ListStringData *m_lstPathInstanceFiles;

	/**
	 * m_MapDFEmGroups value
	 */

	MapDFEMGroups *m_MapDFEmGroups;

	/**
	 * m_MapInstances value
	 */

	MapInstances *m_MapInstances;

	/**
	 * m_MapGlobalDFEMObjects value
	 */
	MapDFEMObjects *m_MapGlobalDFEMObjects;

	/**
	 * m_MapGlobalDFEMData value
	 */
	MapDFEMData *m_MapGlobalDFEMData;

	/**
	 * m_MapGlobalSHELLSections value
	 */
	MapSHELLSections *m_MapGlobalSHELLSections;

	/**
	 * m_MapGlobalELSETSections value
	 */
	MapELSETSections *m_MapGlobalELSETSections;

	/**
	 * m_MapGlobalELEMENTSections value
	 */
	MapELEMENTSections *m_MapGlobalELEMENTSections;

public:

	/**
	 * Default Destructor
	 */
	virtual ~CGlobalDFEMReader();

	/**
	*   Function to return the instance of CGlobalDFEMReader class.
	*   @return singleton object of CGlobalDFEMReader class..
	*/
	static CGlobalDFEMReader* GetCGlobalDFEMReader();

	/**
	 * Getter/Setter of m_PathRoot property
	 */
	void setPathRoot(std::string strPath) {m_PathRoot = strPath;}
	std::string  getPathRoot() {return m_PathRoot;}

	/**
	 * Getter/Setter of m_lstPathInstanceFiles property
	 */
	ListStringData* getLstPathDataFiles()  { return m_lstPathDataFiles; }
	void setLstPathDataFiles( ListStringData *lstPathDataFiles) { m_lstPathDataFiles = lstPathDataFiles; }

	/**
	 * Getter/Setter of m_lstPathInstanceFiles property
	 */
	ListStringData*& getLstPathInstanceFiles() { return m_lstPathInstanceFiles; }
	void setLstPathInstanceFiles(ListStringData *&lstPathInstanceFiles) { m_lstPathInstanceFiles = lstPathInstanceFiles; }

	/**
	 * Getter/Setter of m_PathFile property
	 */
	std::string  getPathFile() {return m_PathFile;}
	void setPathFile(std::string strPath) {m_PathFile = strPath;}

	/**
	 * Getter/Setter of m_strDelimiter
	 */
	void setDelimiter(std::string strDelimiter) {m_strDelimiter = strDelimiter;}
	std::string  getDelimiter() {return m_strDelimiter;}

	/**
	 * Getter/Setter of m_MapDFEmGroups
	 */
	MapDFEMGroups* getMapDFEMGroups() { return m_MapDFEmGroups; }
	void setMapDFEMGroups(MapDFEMGroups *mapDEFEMGroups) { m_MapDFEmGroups = mapDEFEMGroups; }

	/**
	 * Getter/Setter of m_MapInstances
	 */
	MapInstances* getMapInstances() { return m_MapInstances; }
	void setMapInstances(MapInstances *mapInstances) { m_MapInstances = mapInstances; }

	/**
	 * Getter/Setter of m_MapGlobalDFEMObjects
	 */
	MapDFEMObjects* getMapGlobalDFEMObjects() { return m_MapGlobalDFEMObjects; }
	void setMapGlobalDFEMObjects(MapDFEMObjects *mapGlobalDFEMObjects) { m_MapGlobalDFEMObjects = mapGlobalDFEMObjects; }

	/**
	 * Getter/Setter of m_MapGlobalDFEMData
	 */
	MapDFEMData* getMapGlobalDFEMData() { return m_MapGlobalDFEMData; }
	void setMapGlobalDFEMData(MapDFEMData *mapGlobalDFEMData) { m_MapGlobalDFEMData = mapGlobalDFEMData; }

	/**
	 * Getter/Setter of m_MapELEMENTSections
	 */
	MapELEMENTSections* getMapGlobalElementSections() const { return m_MapGlobalELEMENTSections; }
	void setMapGlobalElementSections(MapELEMENTSections *mapElementSections) { m_MapGlobalELEMENTSections = mapElementSections; }

	/**
	 * Getter/Setter of m_MapELSETSections
	 */
	MapELSETSections* getMapGlobalElsetSections() { return m_MapGlobalELSETSections; }
	void setMapGlobalElsetSections(MapELSETSections *mapElsetSections) { m_MapGlobalELSETSections = mapElsetSections; }

	/**
	 * Getter/Setter of m_MapSHELLSections
	 */
	MapSHELLSections* getMapGlobalShellSections() { return m_MapGlobalSHELLSections; }
	void setMapGlobalShellSections(MapSHELLSections *mapShellSections) { m_MapGlobalSHELLSections = mapShellSections; }

	/**
	 * Load Main Data Files
	 */
	bool 			LoadMainDataFile(std::string strDFEMFile);

	/**
	 * Load DFEM Data Files included into Main File
	 */
	bool 				LoadAllPathsDataFiles();

	/**
	 * Load Instance Data Files included into Main File
	 */
	bool 				LoadAllInstanceDataFiles();

	/**
	 * Process to map of DFEM data files
	 */
	bool				LoadGlobalDFEMDataFile(std::string strPathFile);

	/**
	 * Process to map of the Instance data files
	 */
	bool 				LoadGlobalInstanceData(std::string strPathFile);

	/**
	 * Process to erad Part Name into DFEm File.
	 */
	std::string 		LoadPartNameSection(ListStringData *lstDFEMFile);

	/**
	 * Process to load NODE Section to the Global DFEM data
	 */
	bool  				LoadGlobalNODESection(ListStringData *lstDFEMFile, CDFEMGroup &oDFEMGroup);

	/**
	 * Process to Load SHELL Section of the Global DFEM File
	 */
	bool 				LoadGlobalSHELLSection(ListStringData *lstDFEMFile, CDFEMGroup &oDFEMGroup);

	/**
	 * Process to Load Global ELSET Section of the DFEM File
	 */
	bool 				LoadGlobalELSETSection(ListStringData *lstDFEMFile, CDFEMGroup &oDFEMGroup);

	/**
	 * Process to Load GlobalELEMENT Section of the DFEM File
	 */
	bool 				LoadGlobalELEMENTSection(ListStringData *lstDFEMFile, CDFEMGroup &oDFEMGroup);

	/**
	 * Process to Get Global Map DFEM Objects
	 */
	MapDFEMObjects 		* LoadGlobalMapDFEMObjects();

	/**
	 * Process to Load Global DFEM Objects
	 */
	bool 				LoadGlobalDFEMObjects();

	/**
	 * Process to Get Global Map DFEMData
	 */
	MapDFEMData	 		* GetGlobalMapDFEMData();

	/**
	 * Process to Load Global DFEM Data
	 */
	bool 				LoadGlobalDFEMData();




private:

	/**
	*    Default constructor for the CDFEMReader class.
	*/
	CGlobalDFEMReader();

	/**
	*   Singleton CDFEMReader class object pointer.
	**/
	static CGlobalDFEMReader* m_pThis;

};

#endif /* GLOBALDFEMREADER_H_ */
