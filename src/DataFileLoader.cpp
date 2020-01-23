/*
 * CDataFileLoader.cpp
 *
 *  Created on: 18 nov. 2019
 *      Author: fernando.olivares
 */

#include "../Headers/DataFileLoader.h"
#include "../Headers/Global.h"
#include "../Headers/Logger.h"
#include "../Headers/CSVReader.h"
#include "../Headers/GFEMReader.h"
#include "../Headers/DFEMReader.h"
#include "../Headers/ConfigurationReader.h"
#include "../Headers/AssociativityFile.h"
#include "../Headers/GlobalDFEMReader.h"
#include "../Headers/DFEMGroup.h"

CDataFileLoader* CDataFileLoader::m_pThis = NULL;

#pragma GCC diagnostic ignored "-Wunused-variable"

/**
 * Default Class Contructor
 */
CDataFileLoader::CDataFileLoader() {
	// TODO Auto-generated constructor stub

}

/**
 * Default Class Destructor
 */
CDataFileLoader::~CDataFileLoader() {
	delete m_pThis;
}

/**
 *
 * @return
 */
CDataFileLoader* CDataFileLoader::GetDataFileLoader()
{
    if (m_pThis == NULL)
    {
            m_pThis = new CDataFileLoader();
    }
    return m_pThis;
}

/**
 * Method to load ini File
 * @param strResourcesPath
 * @return: Result of the operation
 */
bool CDataFileLoader::LoadIniFile(std::string strResourcesPath) {

	bool bReturn = RESULT_KO;

	try {
		/* read from file */
		mINI::INIFile file(strResourcesPath);
		mINI::INIStructure ini;
		file.read(ini);

		CGlobal::GetGlobal()->setIniFile(ini);

		bReturn = RESULT_OK;
	}
	catch(std::exception &exc) {
		CLogger::GetLogger()->Log(" <EXCEPTION>: CDataFileLoader::LoadIniFile " + std::string(exc.what()));
	}



	return bReturn;
}

/**
 * Method to load Data Files
 * @param strCurrentPath
 * @param strPathFileCSV
 * @return: Result of the operation
 */
bool CDataFileLoader::LoadCSVFile(std::string strCurrentPath, std::string strPathFileCSV) {

	bool bReturn = RESULT_KO;

	try {
		std::string strCSVFile = (strCurrentPath + CGlobal::GetGlobal()->getIniFile().get("DATA_DIRECTORIES").get("associativity_files") + strPathFileCSV);
		CGlobal::Replace(strCSVFile, "/cygdrive/c/", "C:/");
		CCSVReader::GetCSVReader()->setDelimiter(CGlobal::GetGlobal()->getIniFile().get("CSV_PARSER").get("delimiter"));
		CCSVReader::GetCSVReader()->LoadFile(strCSVFile);
		bReturn = RESULT_OK;
	}
	catch(std::exception &exc) {
		CLogger::GetLogger()->Log(" <EXCEPTION>: CDataFileLoader::LoadCSVFile " + std::string(exc.what()));
	}

	return bReturn;
}

/**
 * Method to load Data Files
 * @param strCurrentPath
 * @param strPathFileINP
 * @return: Result of the operation
 */
bool CDataFileLoader::LoadDFEMFile(std::string strCurrentPath, std::string strPathFileINP) {
	bool bReturn = RESULT_KO;

	try {
		std::string strDFEMFile = (strCurrentPath + CGlobal::GetGlobal()->getIniFile().get("DATA_DIRECTORIES").get("input_files") + strPathFileINP);
		CGlobal::Replace(strDFEMFile, "/cygdrive/c/", "C:/");
		CDFEMReader::GetDFEMReader()->setDelimiter(CGlobal::GetGlobal()->getIniFile().get("DFEM_PARSER").get("delimiter"));
		CDFEMReader::GetDFEMReader()->LoadDFEMData(strDFEMFile);
	}
	catch(std::exception &exc) {
		CLogger::GetLogger()->Log(" <EXCEPTION>: CDataFileLoader::LoadDFEMFile " + std::string(exc.what()));
	}

	return bReturn;
}


/**
 * Method to load Data Files
 * @param strCurrentPath
 * @param strPathFileINP
 * @return: Result of the operation
 */
bool CDataFileLoader::LoadGFEMFile(std::string strCurrentPath, std::string strPathFileBDF) {
	bool bReturn = RESULT_KO;

	try {
		CGFEMReader::GetGFEMReader()->setDelimiter(CGlobal::GetGlobal()->getIniFile().get("GFEM_PARSER").get("delimiter"));
		std::string strBDFFile = (strCurrentPath + CGlobal::GetGlobal()->getIniFile().get("DATA_DIRECTORIES").get("input_files") + strPathFileBDF);
		CGFEMReader::GetGFEMReader()->LoadAllGFEMData(strBDFFile, std::stoi(CGlobal::GetGlobal()->getIniFile().get("GFEM_PARSER").get("grid_field_size")));

		bReturn = RESULT_OK;
	}
	catch(std::exception &exc) {
		CLogger::GetLogger()->Log(" <EXCEPTION>: CDataFileLoader::LoadGFEMFile " + std::string(exc.what()));
	}

	return bReturn;
}

/**
 * Method to load Data Files
 * @param strCurrentPath
 * @param strPathFileINP
 * @return: Result of the operation
 */
bool CDataFileLoader::LoadGlobalGFEMFile(std::string strCurrentPath, std::string strPathFileBDF) {
	bool bReturn = RESULT_KO;

	try {

		CGlobal::Replace(strCurrentPath, "/cygdrive/c/", "C:/");

		CGFEMReader::GetGFEMReader()->setDelimiter(CGlobal::GetGlobal()->getIniFile().get("GFEM_PARSER").get("delimiter"));
		std::string strBDFFile = (strCurrentPath + CGlobal::GetGlobal()->getIniFile().get("DATA_DIRECTORIES").get("gfem_main_file_Format_2") + strPathFileBDF);
		CGFEMReader::GetGFEMReader()->LoadAllGFEMData(strBDFFile, std::stoi(CGlobal::GetGlobal()->getIniFile().get("GFEM_PARSER").get("grid_field_size")));

		bReturn = RESULT_OK;
	}
	catch(std::exception &exc) {
		CLogger::GetLogger()->Log(" <EXCEPTION>: CDataFileLoader::LoadGFEMFile " + std::string(exc.what()));
	}

	return bReturn;
}

/**
 * Method to load the remainder data files
 * @param mapGFEMData
 * @param mapDFEMData
 * @return: Result of the operation
 */
bool CDataFileLoader::ProcessDataConnections(MapGFEMData *mapGFEMData, MapDFEMData *mapDFEMData) {

	bool bReturn = RESULT_KO;

	ListIntegerData *lstNodesGFEM = NULL;

	try {
		//Recorremos las conexiones 2D2D y obtenemos los nodos GFEM. A cada nodo le a�adimos los datos obtenidos de la "Tarjeta GRID"
		ListConnections *lstConnections2D2D = CCSVReader::GetCSVReader()->GetAssociativityFile()->GetConnections2D2D();
		lstNodesGFEM = LoadDataConnectionsGFEM(lstConnections2D2D, mapGFEMData);

		if(lstNodesGFEM->size() > 0) {
			ActualizeNodesGFEM(lstConnections2D2D, lstNodesGFEM);
			lstNodesGFEM->clear();
		}

		LoadDataConnectionsDFEM(lstConnections2D2D, mapDFEMData);

		//Recorremos las conexiones 2D2D y obtenemos los nodos GFEM. A cada nodo le a�adimos los datos obtenidos de la "Tarjeta GRID"
		ListConnections *lstConnections1D2D = CCSVReader::GetCSVReader()->GetAssociativityFile()->GetConnections1D2D();
		lstNodesGFEM = LoadDataConnectionsGFEM(lstConnections1D2D, mapGFEMData);

		if(lstNodesGFEM->size() > 0) {
			ActualizeNodesGFEM(lstConnections1D2D, lstNodesGFEM);
			lstNodesGFEM->clear();
		}


		LoadDataConnectionsDFEM(lstConnections1D2D, mapDFEMData);
	}
	catch(std::exception &exc) {
		CLogger::GetLogger()->Log(" <EXCEPTION>: CDataFileLoader::ProcessDataConnections " + std::string(exc.what()));
	}

	return bReturn;
}

bool CDataFileLoader::ActualizeNodesGFEM(ListConnections *lstConnections, ListIntegerData *lstNodesGFEM) {

	bool bReturn = RESULT_KO;

	try {

		if(lstConnections == NULL|| lstNodesGFEM->size() == 0) return bReturn;

		for(ListConnections::iterator itConn = lstConnections->begin(); itConn != lstConnections->end(); itConn++) {

			MapGFEMNodes *mapGFEMNodes =  (*itConn)->GetGFEMNodes();

			if((mapGFEMNodes == NULL) ||
			   (mapGFEMNodes != NULL && mapGFEMNodes->size() <= 0)) continue;

			for(ListIntegerData::iterator itNode = lstNodesGFEM->begin(); itNode != lstNodesGFEM->end(); itNode++) {

				MapGFEMNodes::iterator itMapGFEM = mapGFEMNodes->find((*itNode));

				if(itMapGFEM != mapGFEMNodes->end()) {
					mapGFEMNodes->erase((*itNode));
				}

			}
		}
	}
	catch(std::exception &exc) {

	}

	return RESULT_OK;
}

/**
 * Method to load Data Files
 * @param strPathFileCSV
 * @param strPathFileBDF
 * @param strPathFileINP
 * @return: Result of the operation
 */
bool CDataFileLoader::LoadDataFiles(std::string strCurrentPath, std::string strPathFileCSV, std::string strPathFileBDF, std::string strPathFileINP) {

	bool bReturn = RESULT_KO;

	try {

		CLogger::GetLogger()->SetPath(strCurrentPath + "/Logs");

		std::string strResourcesPath = strCurrentPath + "/Resources/ConfigurationFile.ini";
		CGlobal::Replace(strResourcesPath, "/cygdrive/c/", "C:/");

		LoadIniFile(strResourcesPath);

		CGlobal::GetGlobal()->LoadOFFSETNODE2_NODE3();

		LoadCSVFile(strCurrentPath, strPathFileCSV);
		LoadDFEMFile(strCurrentPath, strPathFileINP);

		if (m_pThis->CheckAllDFEMNodesExistInFile()) {
			return false;
		}

		LoadGFEMFile(strCurrentPath, strPathFileBDF);

		ProcessDataConnections(CGFEMReader::GetGFEMReader()->getMapGFEMData(), CDFEMReader::GetDFEMReader()->getMapDFEMData());

		bReturn = true;
	}
	catch(std::exception &exc) {

		CLogger::GetLogger()->Log(" <EXCEPTION>: CDataFileLoader::LoadDataFiles " + std::string(exc.what()));
	}

	return bReturn;
}

/**
 * Method to load Data Files
 * @param lstConnections
 * @param mapGFEMData
 * @return: Result of the operation
 */
ListIntegerData * CDataFileLoader::LoadDataConnectionsGFEM(ListConnections *lstConnections, MapGFEMData *mapGFEMData) {

	ListIntegerData *lstNodesGFEM = new ListIntegerData();

	try {

		if(lstConnections == NULL|| mapGFEMData == NULL) return lstNodesGFEM;

		for(ListConnections::iterator itConn = lstConnections->begin(); itConn != lstConnections->end(); itConn++) {

			MapGFEMNodes *mapGFEMNodes =  (*itConn)->GetGFEMNodes();

			if((mapGFEMNodes == NULL) ||
			   (mapGFEMNodes != NULL && mapGFEMNodes->size() <= 0)) continue;


			for(MapGFEMNodes::iterator itGFEMNodes = mapGFEMNodes->begin(); itGFEMNodes != mapGFEMNodes->end(); itGFEMNodes++) {

				ListStringData oGridDataGFEM = CGFEMReader::GetGFEMReader()->GetGFEMNode(mapGFEMData, (*itGFEMNodes).second->getIdNode());

				if(oGridDataGFEM.size() <= 0){
					lstNodesGFEM->push_back((*itGFEMNodes).second->getIdNode());

					continue;
				}

				//CGlobal::ShowListData(oGridDataGFEM);

				CGridNode *oGridNode = new CGridNode();
				oGridNode->setIdNode((*itGFEMNodes).second->getIdNode());

				ListStringData::iterator itGridData = ++oGridDataGFEM.begin();

				if (itGridData != oGridDataGFEM.end()) {
					std::string strCP = (*itGridData++);
					if(strCP != STRING_EMPTY) {
						oGridNode->setCP(std::atoi(strCP.c_str()));
					}
				}

				if (itGridData != oGridDataGFEM.end()) {
					std::string strCoord_X1 = (*itGridData++);
					if(strCoord_X1 != STRING_EMPTY) {
						oGridNode->setCoord_X1(std::atof(strCoord_X1.c_str()));
					}
				}

				if (itGridData != oGridDataGFEM.end()) {
					std::string strCoord_X2 = (*itGridData++);
					if(strCoord_X2 != STRING_EMPTY) {
						oGridNode->setCoord_X2(std::atof(strCoord_X2.c_str()));
					}
				}

				if (itGridData != oGridDataGFEM.end()) {
					std::string strCoord_X3 = (*itGridData++);
					if(strCoord_X3 != STRING_EMPTY) {
						oGridNode->setCoord_X3(std::atof(strCoord_X3.c_str()));
					}
				}

				if (itGridData != oGridDataGFEM.end()) {
					std::string strCD = (*itGridData++);
					if(strCD != STRING_EMPTY) {
						oGridNode->setCD(std::atoi(strCD.c_str()));
					}
				}

				(*itGFEMNodes).second->setGridNode(oGridNode);
			}
		}
	}
	catch(std::exception &exc) {

		CLogger::GetLogger()->Log(" <EXCEPTION>: CDataFileLoader::LoadDataConnectionsGFEM " + std::string(exc.what()));
	}

	return lstNodesGFEM;
}

/**
 * Method to load Data Files
 * @param lstConnections
 * @param mapDFEMData
 * @return: Result of the operation
 */
bool CDataFileLoader::LoadDataConnectionsDFEM(ListConnections *lstConnections, MapDFEMData *mapDFEMData) {
	bool bReturn = false;

	try {

		if(lstConnections == NULL|| mapDFEMData == NULL) return bReturn;

		for(ListConnections::iterator itConn = lstConnections->begin(); itConn != lstConnections->end(); itConn++) {

			MapDFEMNodes *mapDFEMNodes =  (*itConn)->GetDFEMNodes();

			for(MapDFEMNodes::iterator itDFEMNodes = mapDFEMNodes->begin(); itDFEMNodes != mapDFEMNodes->end(); itDFEMNodes++) {

				ListStringData oDFEMNode = CGlobal::GetGlobal()->GetDFEMNode(mapDFEMData, (*itDFEMNodes).second->getStrIdNode());

				//CGlobal::ShowListData(oDFEMNode);

				ListStringData::iterator itDFEMData = ++oDFEMNode.begin();
				float dValue = 0;

				if(itDFEMData != oDFEMNode.end()) {
					std::string strX = (*itDFEMData++);
					dValue = std::atof(strX.c_str());
					(*itDFEMNodes).second->setX(dValue);
				}

				if(itDFEMData != oDFEMNode.end()) {
					std::string strY = (*itDFEMData++);
					dValue = std::atof(strY.c_str());
					(*itDFEMNodes).second->setY(dValue);
				}

				if(itDFEMData != oDFEMNode.end()) {
					std::string strZ = (*itDFEMData);
					dValue = std::atof(strZ.c_str());
					(*itDFEMNodes).second->setZ(dValue);
				}
			}
		}
	}
	catch(std::exception &exc) {

		CLogger::GetLogger()->Log(" <EXCEPTION>: CDataFileLoader::LoadDataConnectionsDFEM " + std::string(exc.what()));
	}

	return bReturn;
}

/**
 * Method to check that all DEFEM Nodes exists in DFEM data File
 * @return: Result of the operation
 */
bool CDataFileLoader::CheckAllDFEMNodesExistInFile() {

	bool bError2D2D = false;
	bool bError1D2D = false;
	std::string strIdNode = STRING_EMPTY;

	MapDFEMObjects::iterator itMapObjects;

	ListConnections *lstConnections2D2D = CCSVReader::GetCSVReader()->GetAssociativityFile()->GetConnections2D2D();

	for(ListConnections::iterator itConn = lstConnections2D2D->begin(); itConn != lstConnections2D2D->end(); itConn++) {

		MapDFEMNodes *mapNodes = (*itConn)->GetDFEMNodes();

		CConnection *oConn = (*itConn);

		for(MapDFEMNodes::iterator itDFEM = mapNodes->begin(); itDFEM != mapNodes->end(); itDFEM++) {

			if(CGlobal::GetGlobal()->getFormatData() == FORMAT_1) {

				CDFEMNode *oNode = (*itDFEM).second;

				strIdNode = std::to_string((*itDFEM).second->getIdNode());

				itMapObjects = CDFEMReader::GetDFEMReader()->getMapDFEMObjects()->find(strIdNode);

				if (itMapObjects == CDFEMReader::GetDFEMReader()->getMapDFEMObjects()->end()) {
					bError2D2D = true;
					break;
				}

			}
			else {

				strIdNode = (*itDFEM).second->getStrIdNode();
				itMapObjects = CGlobalDFEMReader::GetCGlobalDFEMReader()->getMapGlobalDFEMObjects()->find(strIdNode);

				if (itMapObjects == CDFEMReader::GetDFEMReader()->getMapDFEMObjects()->end()) {
					bError2D2D = true;
					break;
				}
			}
		}
	}

	ListConnections *lstConnections1D2D = CCSVReader::GetCSVReader()->GetAssociativityFile()->GetConnections1D2D();

	for(ListConnections::iterator itConn = lstConnections1D2D->begin(); itConn != lstConnections1D2D->end(); itConn++) {

		MapDFEMNodes *mapNodes = (*itConn)->GetDFEMNodes();

		for(MapDFEMNodes::iterator itDFEM = mapNodes->begin(); itDFEM != mapNodes->end(); itDFEM++) {

			if(CGlobal::GetGlobal()->getFormatData() == FORMAT_1) {

				strIdNode = std::to_string((*itDFEM).second->getIdNode());

				itMapObjects = CDFEMReader::GetDFEMReader()->getMapDFEMObjects()->find(strIdNode);

				if (itMapObjects == CDFEMReader::GetDFEMReader()->getMapDFEMObjects()->end()) {
					bError2D2D = true;
					break;
				}
			}
			else {

				strIdNode = (*itDFEM).second->getStrIdNode();
				itMapObjects = CGlobalDFEMReader::GetCGlobalDFEMReader()->getMapGlobalDFEMObjects()->find(strIdNode);

				if (itMapObjects == CDFEMReader::GetDFEMReader()->getMapDFEMObjects()->end()) {
					bError2D2D = true;
					break;
				}
			}
		}
	}

	bool bReturn = (bError2D2D || bError1D2D);

	if(bReturn) {

		cout << "*************************************************************************************************************************" << endl;
		cout << "*************************************************************************************************************************" << endl;
		cout << "*************************************************************************************************************************" << endl;
		cout << "*******                                                                                                           *******" << endl;
		cout << "*******                                           ERROR BAD INPUT DATA FILES                                      *******" << endl;
		cout << "*******                                           ERROR BAD INPUT DATA FILES                                      *******" << endl;
		cout << "*******                                           ERROR BAD INPUT DATA FILES                                      *******" << endl;
		cout << "*******                                           ERROR BAD INPUT DATA FILES                                      *******" << endl;
		cout << "*******                                           ERROR BAD INPUT DATA FILES                                      *******" << endl;
		cout << "*******                                                                                                           *******" << endl;
		cout << "*************************************************************************************************************************" << endl;
		cout << "*************************************************************************************************************************" << endl;
		cout << "*************************************************************************************************************************" << endl;
	}

	return bReturn;
}

/**
 * Method to load Data Files
 * @param strPathFileCSV
 * @param strPathFileBDF
 * @param strPathFileINP
 * @return: Result of the operation
 */
bool CDataFileLoader::LoadGlobalDataFiles(std::string strCurrentPath, std::string strFileCSV, std::string strPathGFEMFile, std::string strPathDFEMFile) {

	bool bReturn = false;

	int dType = 1;

	try {
		CLogger::GetLogger()->SetPath(strCurrentPath + "/Logs");

		std::string strResourcesPath = strCurrentPath + "/Resources/ConfigurationFile.ini";
		CGlobal::Replace(strResourcesPath, "/cygdrive/c/", "C:/");

		LoadIniFile(strResourcesPath);

		std::string strCSVPath = CGlobal::GetGlobal()->getIniFile().get("DATA_DIRECTORIES").get("associativity_files_Format_2");
		m_pThis->LoadGlobalCSVFile(strCurrentPath, (strCSVPath + strFileCSV));

		std::string strDFEMPath = CGlobal::GetGlobal()->getIniFile().get("DATA_DIRECTORIES").get("dfem_main_file_Format_2");
		CGlobalDFEMReader::GetCGlobalDFEMReader()->setPathRoot(strCurrentPath + strDFEMPath);
		CGlobalDFEMReader::GetCGlobalDFEMReader()->LoadMainDataFile(strPathDFEMFile);
		CGlobalDFEMReader::GetCGlobalDFEMReader()->LoadAllPathsDataFiles();
		CGlobalDFEMReader::GetCGlobalDFEMReader()->LoadAllInstanceDataFiles();

		std::string strRootPath = strCurrentPath + strDFEMPath;

		//The next step is load Instance Files Data
		m_pThis->LoadGlobalInstanceFiles(strRootPath);

		//The next step is load DFEM Files Data
		m_pThis->LoadGlobalDFEMFiles(strRootPath);

		if (m_pThis->CheckAllDFEMNodesExistInFile()) {
			return false;
		}

		LoadGlobalGFEMFile(strCurrentPath, strPathGFEMFile);

		//Esto lo adaptamos a lo nuevo
		ProcessDataConnections(CGFEMReader::GetGFEMReader()->getMapGFEMData(), CGlobalDFEMReader::GetCGlobalDFEMReader()->getMapGlobalDFEMData());

		bReturn = true;
	}
	catch(std::exception &exc) {

		CLogger::GetLogger()->Log(" <EXCEPTION>: CDataFileLoader::LoadGlobalDataFiles " + std::string(exc.what()));
	}

	return bReturn;
}

/**
 * Method to load Data Files
 * @param strCurrentPath
 * @param strPathFileCSV
 * @return: Result of the operation
 */
bool CDataFileLoader::LoadGlobalCSVFile(std::string strCurrentPath, std::string strPathFileCSV) {

	bool bReturn = RESULT_KO;

	CGlobal::Replace(strCurrentPath, "/cygdrive/c/", "C:/");

	try {
		std::string strCSVFile = (strCurrentPath + strPathFileCSV);
		CCSVReader::GetCSVReader()->setDelimiter(CGlobal::GetGlobal()->getIniFile().get("CSV_PARSER").get("delimiter"));
		CCSVReader::GetCSVReader()->LoadGlobalFile(strCSVFile);
		bReturn = RESULT_OK;
	}
	catch(std::exception &exc) {
		CLogger::GetLogger()->Log(" <EXCEPTION>: CDataFileLoader::LoadGlobalCSVFile " + std::string(exc.what()));
	}

	return bReturn;
}


/**
 * Method to load DFEM Data Files
 * @param strRootPath
 * @return: Result of the operation
 */
bool CDataFileLoader::LoadGlobalDFEMFiles(std::string strRootPath) {
	bool bReturn = RESULT_KO;

	CGlobal::Replace(strRootPath, "/cygdrive/c/", "C:/");
	std::string strDFEMFile = STRING_EMPTY;

	CDFEMReader::GetDFEMReader()->setDelimiter(CGlobal::GetGlobal()->getIniFile().get("DFEM_PARSER").get("delimiter"));

	try {

		for(ListStringData::iterator itDFEMFile = CGlobalDFEMReader::GetCGlobalDFEMReader()->getLstPathDataFiles()->begin();
									 itDFEMFile != CGlobalDFEMReader::GetCGlobalDFEMReader()->getLstPathDataFiles()->end();
									 itDFEMFile++) {

			strDFEMFile = strRootPath + (*itDFEMFile);
			CGlobalDFEMReader::GetCGlobalDFEMReader()->LoadGlobalDFEMDataFile(strDFEMFile);
		}

		cout << CGlobalDFEMReader::GetCGlobalDFEMReader()->getMapGlobalDFEMData()->size() << endl;
	}
	catch(std::exception &exc) {
		CLogger::GetLogger()->Log(" <EXCEPTION>: CDataFileLoader::LoadGlobalDFEMFiles " + std::string(exc.what()));
	}

	return bReturn;
}

/**
 * Method to load Instance Data Files
 * @param strRootPath
 * @return: Result of the operation
 */
bool CDataFileLoader::LoadGlobalInstanceFiles(std::string strRootPath) {
	bool bReturn = RESULT_KO;

	CGlobal::Replace(strRootPath, "/cygdrive/c/", "C:/");
	std::string strDFEMFile = STRING_EMPTY;

	CDFEMReader::GetDFEMReader()->setDelimiter(CGlobal::GetGlobal()->getIniFile().get("DFEM_PARSER").get("delimiter"));

	try {

		for(ListStringData::iterator itInstanceFile = CGlobalDFEMReader::GetCGlobalDFEMReader()->getLstPathInstanceFiles()->begin();
									 itInstanceFile != CGlobalDFEMReader::GetCGlobalDFEMReader()->getLstPathInstanceFiles()->end();

									 itInstanceFile++) {

			strDFEMFile = strRootPath + (*itInstanceFile);
			CGlobalDFEMReader::GetCGlobalDFEMReader()->LoadGlobalInstanceData(strDFEMFile);
		}
	}
	catch(std::exception &exc) {
		CLogger::GetLogger()->Log(" <EXCEPTION>: CDataFileLoader::LoadGlobalInstanceFiles " + std::string(exc.what()));
	}

	return bReturn;
}

