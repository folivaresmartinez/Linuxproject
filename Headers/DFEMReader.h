/*
 * CDFEMReader.h
 *
 *  Created on: 13 nov. 2019
 *      Author: fernando.olivares
 */

#ifndef DFEMREADER_H_
#define DFEMREADER_H_

#include <list>
#include <string>
#include "Global.h"

/**
 * Class that implement the functionality required to read an parse the DFEM files
 */
class CDFEMReader {

private:
	/**
	 * m_PathFile value
	 */
	std::string 	m_PathFile;

	/**
	 * m_strDelimiter value
	 */
	std::string 	m_strDelimiter;

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

	/**
	 * Default Destructor
	 */
	virtual ~CDFEMReader();

	/**
	*   Funtion to return the instance of DFEMReader class.
	*   @return singleton object of DFEMReader class..
	*/
	static CDFEMReader* GetDFEMReader();

	/**
	 * Set Method for delimiter member
	 */
	void setDelimiter(std::string strDelimiter) {m_strDelimiter = strDelimiter;}

	/**
	 * Get Method for delimiter member
	 */
	std::string  getDelimiter() {return m_strDelimiter;}


	/**
	 * Set Method for Path member
	 */
	void setPathFile(std::string strPath) {m_PathFile = strPath;}

	/**
	 * Get Method for Path member
	 */
	std::string  getPathFile() {return m_PathFile;}

	/**
	 * Getter/Setter of m_MapDFEMData
	 */
	MapDFEMData* getMapDFEMData() { return m_MapDFEMData; }
	void setMapDFEMData(MapDFEMData *mapDfemData) { m_MapDFEMData = mapDfemData; }

	/**
	 * Getter/Setter of m_MapDFEMObjects
	 */
	MapDFEMObjects* getMapDFEMObjects() { return m_MapDFEMObjects; }
	void setMapDFEMObjects(MapDFEMObjects *mapDFEMObjects) { m_MapDFEMObjects = mapDFEMObjects; }

	/**
	 * Getter/Setter of m_MapELEMENTSections
	 */
	MapELEMENTSections* getMapElementSections() const { return m_MapELEMENTSections; }
	void setMapElementSections(MapELEMENTSections *mapElementSections) { m_MapELEMENTSections = mapElementSections; }

	/**
	 * Getter/Setter of m_MapELSETSections
	 */
	MapELSETSections* getMapElsetSections() { return m_MapELSETSections; }
	void setMapElsetSections(MapELSETSections *mapElsetSections) { m_MapELSETSections = mapElsetSections; }

	/**
	 * Getter/Setter of m_MapSHELLSections
	 */
	MapSHELLSections* getMapShellSections() { return m_MapSHELLSections; }
	void setMapShellSections(MapSHELLSections *mapShellSections) { m_MapSHELLSections = mapShellSections; }


	/**
	 * Process to map of the DFEM data files
	 */
	bool  				LoadDFEMData(std::string strPathFile);

	/**
	 * Process to map the DFEM data
	 */
	bool  				LoadNODESection(ListStringData *lstDFEMFile);

	/**
	 * Process to Load SHELL Section of the DFEM File
	 */
	bool 				LoadSHELLSection(ListStringData *lstDFEMFile);

	/**
	 * Process to Load ELSET Section of the DFEM File
	 */
	bool 				LoadELSETSection(ListStringData *lstDFEMFile);

	/**
	 * Process to Load ELEMENT Section of the DFEM File
	 */
	bool 				LoadELEMENTSection(ListStringData *lstDFEMFile);

private:

	/**
	*    Default constructor for the CDFEMReader class.
	*/
	CDFEMReader();

	/**
	*   Singleton CDFEMReader class object pointer.
	**/
	static CDFEMReader* m_pThis;
};

#endif /* DFEMREADER_H_ */
