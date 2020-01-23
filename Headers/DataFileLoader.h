/*
 * CDataFileLoader.h
 *
 *  Created on: 18 nov. 2019
 *      Author: fernando.olivares
 */

#ifndef DATAFILELOADER_H_
#define DATAFILELOADER_H_

#include <string>
#include "../Headers/Global.h"


class CGlobal;

class CDataFileLoader {

private:

	/**
	*   Singleton CDataFileLoader class object pointer.
	**/
	static CDataFileLoader* m_pThis;

	CDataFileLoader();

	/**
	 * Method that perform the operation to Load Data Connections GFEM
	 */
	ListIntegerData * LoadDataConnectionsGFEM(ListConnections *lstConnections, MapGFEMData *mapGFEMData);

	/**
	 * Method that perform the operation to Load Data Connections DFEM
	 */
	bool LoadDataConnectionsDFEM(ListConnections *lstConnections, MapDFEMData *mapDFEMData);


public:

	/**
	 * Method that perform the operation to Load Global Data Connections DFEM (Many files)
	 */
	bool LoadGlobalDataFiles(std::string strCurrentPath, std::string strFileCSV, std::string strPathGFEMFile, std::string strPathDFEMFile);

	/**
	 * Method that perform the operation to Load CSV File Format 2
	 */
	bool LoadGlobalCSVFile(std::string strCurrentPath, std::string strPathFileCSV);

	/**
	 * Method that perform the operation to Actualize GFEM Nodes of each Connection 2D2D/1D2D
	 */
	bool ActualizeNodesGFEM(ListConnections *lstConnections, ListIntegerData *lstNodesGFEM);

	/**
	 * Method that perform the operation to Load Data Files
	 */
	bool LoadDataFiles(std::string strCurrentPath, std::string strPathFileCSV, std::string strPathFileBDF, std::string strPathFileINP);

	/**
	 * Method that perform the operation to Load INI File
	 */
	bool LoadIniFile(std::string strResourcesPath);

	/**
	 * Method that perform the operation to Load CSV File
	 */
	bool LoadCSVFile(std::string strCurrentPath, std::string strPathFileCSV);

	/**
	 * Method that perform the operation to Load DFEM File
	 */
	bool LoadDFEMFile(std::string strCurrentPath, std::string strPathFileINP);

	/**
	 * Method that perform the operation to Load Global DFEM Files Data
	 */
	bool LoadGlobalDFEMFiles(std::string strRootPath);

	/**
	 * Method that perform the operation to Load Global Instance Files Data
	 */
	bool LoadGlobalInstanceFiles(std::string strRootPath);

	/**
	 * Method that perform the operation to Load GFEM File
	 */
	bool LoadGFEMFile(std::string strCurrentPath, std::string strPathFileBDF);

	/**
	 * Method that perform the operation to Load Global GFEM File
	 */
	bool LoadGlobalGFEMFile(std::string strCurrentPath, std::string strPathFileBDF);

	/**
	 * Method that perform the operation to Process Data Connections
	 */
	bool ProcessDataConnections(MapGFEMData *mapGFEMData, MapDFEMData *mapDFEMData);

	/**
	 * Method that perform the operation to Check AllDFEM Nodes Exist In File
	 */
	bool CheckAllDFEMNodesExistInFile();




	/**
	*   Funtion to create the instance of CSVReader class.
	*   @return singleton object of CCSVReader class..
	*/
	static CDataFileLoader* GetDataFileLoader();

	/**
	 * Default destructor
	 */
	virtual ~CDataFileLoader();

};

#endif /* DATAFILELOADER_H_ */
