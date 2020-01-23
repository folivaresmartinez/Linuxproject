/*
 * CGFEMReader.h
 *
 *  Created on: 13 nov. 2019
 *      Author: fernando.olivares
 */


#ifndef GFEMREADER_H_
#define GFEMREADER_H_

#include <list>
#include <string>
#include "Global.h"

class CGFEMNode;

class CGFEMReader {

private:
	/**
	*   Singleton CDataFileLoader class object pointer.
	**/
	static CGFEMReader	* m_pThis;


	/**
	 * Default Constructor
	 */
	CGFEMReader();

	/**
	 * m_PathFile value
	 */
	std::string m_PathFile;

	/**
	 * m_strDelimiter value
	 */
	std::string m_strDelimiter;

	/**
	 * m_MapGFEMData value
	 */
	MapGFEMData 		*m_MapGFEMData;

	/**
	 * m_MapGRIDData value
	 */
	MapGRIDData 		*m_MapGRIDData;

	/**
	 * m_MapCQUAD4Data value
	 */
	MapCQUAD4Data 		*m_MapCQUAD4Data;

	/**
	 * m_MapCTRIA3Data value
	 */
	MapCTRIA3Data 		*m_MapCTRIA3Data;

	/**
	 * m_ListCBEAMData value
	 */
	ListIntegerData 	*m_ListCBEAMData;

	/**
	 * m_ListCRODData value
	 */
	ListIntegerData 	*m_ListCRODData;

public:
	/**
	*   Function to create the instance of CGFEMReader class.
	*   @return singleton object of CGFEMReader class..
	*/
	static CGFEMReader* GetGFEMReader();

	/**
	 * Default destructor
	 */
	virtual ~CGFEMReader();

public:

	/**
	 * Set Method for Path member
	 */
	void setPathFile(std::string strPath) {m_PathFile = strPath;}

	/**
	 * Get Method for Path member
	 */
	std::string  getPathFile() {return m_PathFile;}

	/**
	 * Set Method for delimiter member
	 */
	void setDelimiter(std::string strDelimiter) {m_strDelimiter = strDelimiter;}

	/**
	 * Get Method for delimiter member
	 */
	std::string  getDelimiter() {return m_strDelimiter;};

	/**
	 * Get Node
	 */
	ListStringData GetNode(std::string strPathFile, std::string strPattern);

	/**
	 * Get Lines Wit hPattern
	 */
	list<std::string> 			GetLinesWithPattern(std::string strPathFile, std::string strPattern);

	/**
	 * Get GFEM Nodes
	 */
	MapGFEMData*  				GetGFEMNodes(std::string strPathFile, int dFieldSize, std::string strPattern);

	/**
	 * Get GFEM Node
	 */
	ListStringData				GetGFEMNode(MapGFEMData *mapGFEMData, int keyNode);

	/**
	 * Load All GFEM Data
	 */
	bool  						LoadAllGFEMData(std::string strPathFile, int dFieldSize);

	/**
	 * Load GFEM Data
	 */
    bool  						LoadGFEMData(ListStringData *lstGFEMMFile, int dFieldSize, std::string strPattern);

	/**
	 * Create CQuad4 Node
	 */
    CCQUAD4Node * 				CreateCQuad4Node(ListStringData lstNodeData);

	/**
	 * Create CTria3 Node
	 */
    CCTRIA3Node * 				CreateCTria3Node(ListStringData lstNodeData);

	/**
	 * Create GRID Node
	 */
    CGridNode * 				CreateGRIDNode(ListStringData lstNodeData);

	/**
	 * Getter/Setter of m_MapGFEMData
	 */
    MapGFEMData* getMapGFEMData() { return m_MapGFEMData; }
	void setMapGFEMData(MapGFEMData *mapGfemData) { m_MapGFEMData = mapGfemData; }

	/**
	 * Getter/Setter of m_MapGFEMData
	 */
	MapGRIDData* getMapGRIDData() { return m_MapGRIDData; }
	void setMapGRID4Data(MapGRIDData *mapGRIDData) { m_MapGRIDData = mapGRIDData; }

	/**
	 * Getter/Setter of m_MapCQUAD4Data
	 */
	MapCQUAD4Data* getMapCQUAD4Data() { return m_MapCQUAD4Data; }
	void setMapCQUAD4Data(MapCQUAD4Data *mapCQUAD4Data) { m_MapCQUAD4Data = mapCQUAD4Data; }

	/**
	 * Getter/Setter of m_MapCTRIA3Data
	 */
	MapCTRIA3Data* getMapCTRIA3Data() { return m_MapCTRIA3Data; }
	void setMapCTRIA3Data(MapCTRIA3Data *mapCTRIA3Data) { m_MapCTRIA3Data = mapCTRIA3Data; }

	/**
	 * Getter/Setter of m_ListCBEAMData
	 */
	ListIntegerData*& getListCBEAM_Data() { return m_ListCBEAMData; }
	void setListCBEAM_Data(ListIntegerData *&listCbeamData) { m_ListCBEAMData = listCbeamData; }

	/**
	 * Getter/Setter of m_ListCRODData
	 */
	ListIntegerData*& getListCROD_Data() { return m_ListCRODData; }
	void setListCROD_Data(ListIntegerData *&listCrodData) { m_ListCRODData = listCrodData; }
};

#endif /* GFEMREADER_H_ */
