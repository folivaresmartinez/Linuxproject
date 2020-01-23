/*
 * GFEMReader.cpp
 *
 *  Created on: 13 nov. 2019
 *      Author: fernando.olivares
 */


#include "../Headers/GFEMReader.h"
#include "../Headers/Global.h"
#include "../Headers/Logger.h"

CGFEMReader* CGFEMReader::m_pThis = NULL;

#pragma GCC diagnostic ignored "-Wunused-variable"

CGFEMReader::CGFEMReader() {

	m_PathFile = STRING_EMPTY;
	m_strDelimiter = ",";
	m_MapGFEMData = new MapGFEMData();

	m_MapGRIDData = new MapGRIDData();
	m_MapCQUAD4Data = new MapCQUAD4Data();
	m_MapCTRIA3Data = new MapCTRIA3Data();

	m_ListCBEAMData = new ListIntegerData;
	m_ListCRODData = new ListIntegerData;
}

/**
 *
 * @return
 */
CGFEMReader* CGFEMReader::GetGFEMReader()
{
    if (m_pThis == NULL)
    {
            m_pThis = new CGFEMReader();
    }
    return m_pThis;
}


CGFEMReader::~CGFEMReader() {

	m_MapGFEMData->clear();
	delete m_MapGFEMData;
	m_MapGFEMData = NULL;

	for (MapGRIDData::iterator it=m_MapGRIDData->begin(); it != m_MapGRIDData->end(); it++)  {
		delete (*it).second;
		it = m_MapGRIDData->erase(it);
	}
	delete m_MapGRIDData;
	m_MapGRIDData = NULL;

	for (MapCQUAD4Data::iterator it=m_MapCQUAD4Data->begin(); it != m_MapCQUAD4Data->end(); it++)  {
		delete (*it).second;
		it = m_MapCQUAD4Data->erase(it);
	}
	delete m_MapCQUAD4Data;
	m_MapCQUAD4Data = NULL;

	for (MapCTRIA3Data::iterator it=m_MapCTRIA3Data->begin(); it != m_MapCTRIA3Data->end(); it++)  {
		delete (*it).second;
		it = m_MapCTRIA3Data->erase(it);
	}
	delete m_MapCTRIA3Data;
	m_MapCTRIA3Data = NULL;

	m_ListCBEAMData->clear();
	delete m_ListCBEAMData;
	m_ListCBEAMData = NULL;

	m_ListCRODData->clear();
	delete m_ListCRODData;
	m_ListCRODData = NULL;
}

/**
 *
 * @param strGridLine
 * @param dFieldSize
 * @return
 */
list<std::string> CGFEMReader::GetLinesWithPattern(std::string strPathFile, std::string strPattern) {

	std::list<std::string> lstReturn;
    std::string strReadLine = STRING_EMPTY;
    std::list<std::string> dataList;

	try {

		if(CGlobal::FileExist(strPathFile)) {

		    ifstream oDataFile;
		    oDataFile.open(strPathFile.c_str());

		    while(getline(oDataFile, strReadLine)) {

		        if (strReadLine.find(strPattern) != std::string::npos) {
		        	lstReturn.push_back(strReadLine);
		        }
			}

		    oDataFile.close();
		}
	}
	catch(std::exception &exc) {

		CLogger::GetLogger()->Log(" <EXCEPTION>: CGFEMReader::GetLinesWithPattern " + std::string(exc.what()));
	}

	return lstReturn;
}

/**
 *
 * @param strPathFile
 * @param dFieldSize
 * @param strPattern
 * @return
 */
MapGFEMData*  CGFEMReader::GetGFEMNodes(std::string strPathFile, int dFieldSize, std::string strPattern) {

	MapGFEMData* mapReturn = NULL;
    std::string strReadLine = STRING_EMPTY;
    ListStringData dataList;
	try {

		if(CGlobal::FileExist(strPathFile)) {

			mapReturn = new MapGFEMData();

		    ifstream oDataFile;
		    oDataFile.open(strPathFile.c_str());

		    while(getline(oDataFile, strReadLine)) {

		        if (strReadLine.find(strPattern) != std::string::npos) {

		        	ListStringData lstGridData =  CGlobal::ParseDataLine(strReadLine, dFieldSize, strPattern);

		        	if (lstGridData.size() > 0)
		        	{
		        		ListStringData::iterator it = lstGridData.begin();

		        		MapGFEMData::iterator itMap = mapReturn->begin();
						mapReturn->insert(itMap, std::pair<int, ListStringData>(std::stoi((*it)),lstGridData));
		        	}
		        }
			}

		    oDataFile.close();
		}
	}
	catch(std::exception &exc) {

		if(mapReturn != NULL) {
			delete mapReturn;
			mapReturn = NULL;
		}

		CLogger::GetLogger()->Log(" <EXCEPTION>: CGFEMReader::GetGFEMNodes " + std::string(exc.what()));
	}

	return mapReturn;
}

/**
 *
 * @param mapGridData
 * @param keyNode
 * @return
 */
ListStringData  CGFEMReader::GetGFEMNode(MapGFEMData *mapGFEMData, int keyNode) {

	ListStringData lstGFEMNode;

	try {

		if((mapGFEMData == NULL) ||
		   (mapGFEMData != NULL && mapGFEMData->size() <= 0)) return lstGFEMNode;

		MapGFEMData::iterator itMap;
		itMap = mapGFEMData->find(keyNode);

		if (itMap != mapGFEMData->end()) {
			lstGFEMNode = itMap->second;
		}
		else {
			lstGFEMNode.clear();
		}
	}
	catch(std::exception &exc) {

		CLogger::GetLogger()->Log(" <EXCEPTION>: CGFEMReader::GetGFEMNode " + std::string(exc.what()));
	}



	return lstGFEMNode;
}

/**
 *
 * @param strGridLine
 * @param dFieldSize
 * @return: Result of the operation OK or KO
 */
bool  CGFEMReader::LoadAllGFEMData(std::string strPathFile, int dFieldSize) {
	bool bReturn = false;

	try {

		ListStringData *lstGFEMMFile = CGlobal::GetGlobal()->ReadFileAll(strPathFile);

		if((lstGFEMMFile == NULL) ||
	       (lstGFEMMFile != NULL && lstGFEMMFile->size() <= 0)) return bReturn;

		m_pThis->LoadGFEMData(lstGFEMMFile, dFieldSize, GRID);
		m_pThis->LoadGFEMData(lstGFEMMFile, dFieldSize, CBEAM);
		m_pThis->LoadGFEMData(lstGFEMMFile, dFieldSize, CROD);

		m_pThis->LoadGFEMData(lstGFEMMFile, dFieldSize, CQUAD4);
		m_pThis->LoadGFEMData(lstGFEMMFile, dFieldSize, CTRIA3);

		lstGFEMMFile->clear();
		delete lstGFEMMFile;
		lstGFEMMFile = NULL;

		bReturn = true;
	}
	catch(std::exception &exc) {
		CLogger::GetLogger()->Log(" <EXCEPTION>: CGFEMReader::LoadAllGFEMData " + std::string(exc.what()));
	}

	return bReturn;
}

/**
 *
 * @param strGridLine
 * @param dFieldSize
 * @param strPattern
 * @return: Result of the operation OK or KO
 */
bool  CGFEMReader::LoadGFEMData(ListStringData *lstGFEMMFile, int dFieldSize, std::string strPattern) {

	bool bReturn = false;

	try {

		if((lstGFEMMFile == NULL) ||
	       (lstGFEMMFile != NULL && lstGFEMMFile->size() <= 0)) return bReturn;


		std::string strReadLine = STRING_EMPTY;
		ListStringData dataList;

		for(ListStringData::iterator itLine = lstGFEMMFile->begin(); itLine != lstGFEMMFile->end(); itLine++) {

			strReadLine = (*itLine);
			CGlobal::Trim(strReadLine);

			if (strReadLine.find(strPattern) != std::string::npos) {

				ListStringData lstNodeData;

				if(strPattern == GRID) {

					lstNodeData =  CGlobal::ParseDataLine(strReadLine, dFieldSize, strPattern);

					if (lstNodeData.size() > 0)
					{
						ListStringData::iterator it = lstNodeData.begin();

						MapGFEMData::iterator itMap = m_pThis->getMapGFEMData()->begin();
						m_pThis->getMapGFEMData()->insert(itMap, std::pair<int, ListStringData>(std::stoi((*it)),lstNodeData));

						MapGRIDData::iterator itMapGrid = m_pThis->getMapGRIDData()->begin();
						CGridNode *oGRIDNode = CreateGRIDNode(lstNodeData);

						if(oGRIDNode == NULL) continue;

						m_pThis->getMapGRIDData()->insert(itMapGrid, std::pair<int, CGridNode*>(oGRIDNode->getIdNode(),oGRIDNode));
					}
				}
				else if(strPattern == CBEAM) {
					lstNodeData =  CGlobal::ParseDataLine(strReadLine, dFieldSize, strPattern);

					if (lstNodeData.size() > 0)
					{
						int dPosIni = 3;
						int dIdCDBEM = std::stoi(CGlobal::GetGlobal()->GetItemAtPosition(lstNodeData,dPosIni++));
						m_pThis->getListCBEAM_Data()->push_back(dIdCDBEM);

						dIdCDBEM = std::stoi(CGlobal::GetGlobal()->GetItemAtPosition(lstNodeData,dPosIni));
						m_pThis->getListCBEAM_Data()->push_back(dIdCDBEM);
					}
				}
				else if(strPattern == CROD) {
					lstNodeData =  CGlobal::ParseDataLine(strReadLine, dFieldSize, strPattern);

					if (lstNodeData.size() > 0)
					{
						int dPosIni = 3;
						int dIdCROD = std::stoi(CGlobal::GetGlobal()->GetItemAtPosition(lstNodeData,dPosIni++));
						m_pThis->getListCROD_Data()->push_back(dIdCROD);

						dIdCROD = std::stoi(CGlobal::GetGlobal()->GetItemAtPosition(lstNodeData,dPosIni));
						m_pThis->getListCROD_Data()->push_back(dIdCROD);
					}
				}
				else if(strPattern == CQUAD4) {

					lstNodeData =  CGlobal::ParseDataLine(strReadLine, dFieldSize, strPattern);

					if (lstNodeData.size() > 0)
					{
						MapCQUAD4Data::iterator itMap = m_pThis->getMapCQUAD4Data()->begin();
						CCQUAD4Node *oCQUAD4Node = CreateCQuad4Node(lstNodeData);

						if(oCQUAD4Node == NULL) continue;

						m_pThis->getMapCQUAD4Data()->insert(itMap, std::pair<int, CCQUAD4Node*>(oCQUAD4Node->getEID(),oCQUAD4Node));
					}
				}

				else if(strPattern == CTRIA3) {

					lstNodeData =  CGlobal::ParseDataLine(strReadLine, dFieldSize, strPattern);

					if (lstNodeData.size() > 0)
					{
						CCTRIA3Node *oCTria3Node = CreateCTria3Node(lstNodeData);

						MapCTRIA3Data::iterator itMap = m_pThis->getMapCTRIA3Data()->begin();
						m_pThis->getMapCTRIA3Data()->insert(itMap, std::pair<int, CCTRIA3Node *>(oCTria3Node->getEID(),oCTria3Node));
					}
				}
			}
		}

		m_pThis->getListCBEAM_Data()->unique();
		m_pThis->getListCROD_Data()->unique();

		bReturn = true;
	}
	catch(std::exception &exc) {

		CLogger::GetLogger()->Log(" <EXCEPTION>: CGFEMReader::GetGFEMNodes " + std::string(exc.what()));
	}

	return bReturn;
}

/**
 *
 * @param lstNodeData
 * @return
 */
CCQUAD4Node * CGFEMReader::CreateCQuad4Node(ListStringData lstNodeData) {

	CCQUAD4Node *oCCQUAD4Node = new CCQUAD4Node();


	try {
		ListStringData::iterator itList = lstNodeData.begin();

		if(itList != lstNodeData.end()) {
			std::string strEID = (*itList++); //cout << "strEID: " << strEID << endl;
			int dEID = std::stoi(strEID);
			oCCQUAD4Node->setEID(dEID);
		}

		if(itList != lstNodeData.end()) {
			std::string strPID = (*itList++); //cout << "strPID: " << strPID << endl;
			int dPID = std::stoi(strPID);
			oCCQUAD4Node->setPID(dPID);
		}

		if(itList != lstNodeData.end()) {
			std::string strG1 = (*itList++); //cout << "strG1: " << strG1 << endl;
			int dG1 = std::stoi(strG1);
			oCCQUAD4Node->setG1(dG1);
		}

		if(itList != lstNodeData.end()) {
			std::string strG2 = (*itList++); //cout << "strG2: " << strG2 << endl;
			int dG2 = std::stoi(strG2);
			oCCQUAD4Node->setG2(dG2);
		}

		if(itList != lstNodeData.end()) {
			std::string strG3 = (*itList++); //cout << "strG3: " << strG3 << endl;
			int dG3 = std::stoi(strG3);
			oCCQUAD4Node->setG3(dG3);
		}

		if(itList != lstNodeData.end()) {
			std::string strG4 = (*itList++); //cout << "strG4: " << strG4 << endl;
			int dG4 = std::stoi(strG4);
			oCCQUAD4Node->setG4(dG4);
		}

		if(itList != lstNodeData.end()) {
			std::string strTHETA_MCID = (*itList++); //cout << "strTHETA_MCID: " << strTHETA_MCID << endl;
			float dTHETA_MCID = 0;
			CGlobal::Trim(strTHETA_MCID);

			if(strTHETA_MCID != STRING_EMPTY) {
				dTHETA_MCID = std::stoi(strTHETA_MCID);
			}
			oCCQUAD4Node->setTHETA_MCID(dTHETA_MCID);
		}

		if(itList != lstNodeData.end()) {
			std::string strZOFFS = (*itList++); //cout << "strZOFFS: " << strZOFFS << endl;
			float fZOFFS = 0;
			CGlobal::Trim(strZOFFS);

			if(strZOFFS != STRING_EMPTY) {
				fZOFFS = std::stof(strZOFFS);
			}
			oCCQUAD4Node->setZOFFS(fZOFFS);
		}
	}
	catch(std::exception &exc) {

		CLogger::GetLogger()->Log(" <EXCEPTION>: CGFEMReader::CreateCQuad4Node " + std::string(exc.what()));

		return NULL;
	}

	return oCCQUAD4Node;
}

/**
 *
 * @param lstNodeData
 * @return
 */
CCTRIA3Node * CGFEMReader::CreateCTria3Node(ListStringData lstNodeData) {

	CCTRIA3Node *oCCTRIA3Node = new CCTRIA3Node();

	try {

		ListStringData::iterator itList = lstNodeData.begin();

		if(itList != lstNodeData.end()) {
			std::string strEID = (*itList++); //cout << "strEID: " << strEID << endl;
			int dEID = std::stoi(strEID);
			oCCTRIA3Node->setEID(dEID);
		}

		if(itList != lstNodeData.end()) {
			std::string strPID = (*itList++); //cout << "strPID: " << strPID << endl;
			int dPID = std::stoi(strPID);
			oCCTRIA3Node->setPID(dPID);
		}

		if(itList != lstNodeData.end()) {
			std::string strG1 = (*itList++); //cout << "strG1: " << strG1 << endl;
			int dG1 = std::stoi(strG1);
			oCCTRIA3Node->setG1(dG1);
		}

		if(itList != lstNodeData.end()) {
			std::string strG2 = (*itList++); //cout << "strG2: " << strG2 << endl;
			int dG2 = std::stoi(strG2);
			oCCTRIA3Node->setG2(dG2);
		}

		if(itList != lstNodeData.end()) {
			std::string strG3 = (*itList++); //cout << "strG3: " << strG3 << endl;
			int dG3 = std::stoi(strG3);
			oCCTRIA3Node->setG3(dG3);
		}

		if(itList != lstNodeData.end()) {
			std::string strTHETA_MCID = (*itList++); //cout << "strTHETA_MCID: " << strTHETA_MCID << endl;
			float dTHETA_MCID = 0;
			CGlobal::Trim(strTHETA_MCID);

			if(strTHETA_MCID != STRING_EMPTY) {
				dTHETA_MCID = std::stoi(strTHETA_MCID);
			}
			oCCTRIA3Node->setTHETA_MCID(dTHETA_MCID);
		}

		if(itList != lstNodeData.end()) {
			std::string strZOFFS = (*itList++); //cout << "strZOFFS: " << strZOFFS << endl;
			float fZOFFS = 0;
			CGlobal::Trim(strZOFFS);

			if(strZOFFS != STRING_EMPTY) {
				fZOFFS = std::stof(strZOFFS);
			}
			oCCTRIA3Node->setZOFFS(fZOFFS);
		}
	}
	catch(std::exception &exc) {

		CLogger::GetLogger()->Log(" <EXCEPTION>: CGFEMReader::CreateCTria3Node " + std::string(exc.what()));

		return NULL;
	}

	return oCCTRIA3Node;
}

/**
 *
 * @param lstNodeData
 * @return
 */
CGridNode * CGFEMReader::CreateGRIDNode(ListStringData lstNodeData) {

	CGridNode *oGridNode = new CGridNode();

	try {
		ListStringData::iterator itListData = lstNodeData.begin();

		long m_idNode;

		int m_CP;
		float m_CoordX1;
		float m_CoordX2;
		float m_CoordX3;
		int m_CD;

		if(itListData != lstNodeData.end()) {
			std::string strIDNode = (*itListData++); //cout << "strIDNode: " << strIDNode << endl;
			int dIDNode = std::stoi(strIDNode);
			oGridNode->setIdNode(dIDNode);
		}

		if(itListData != lstNodeData.end()) {
			std::string strCP = (*itListData++); //cout << "strCP: " << strCP << endl;

			if(strCP != STRING_EMPTY) {
				int dCP = std::stoi(strCP);
				oGridNode->setCP(dCP);
			}
			else {
				oGridNode->setCP(ZERO);
			}
		}

		if (itListData != lstNodeData.end()) {
			std::string strCoord_X1 = (*itListData++); //cout << "strCoord_X1: " << strCoord_X1 << endl;

			if(strCoord_X1 != STRING_EMPTY) {
				oGridNode->setCoord_X1(std::atof(strCoord_X1.c_str()));
			}
			else {
				oGridNode->setCoord_X1(ZERO);
			}
		}

		if (itListData != lstNodeData.end()) {
			std::string strCoord_X2 = (*itListData++); //cout << "strCoord_X2: " << strCoord_X2 << endl;

			if(strCoord_X2 != STRING_EMPTY) {
				oGridNode->setCoord_X2(std::atof(strCoord_X2.c_str()));
			}
			else {
				oGridNode->setCoord_X2(ZERO);
			}
		}

		if (itListData != lstNodeData.end()) {
			std::string strCoord_X3 = (*itListData++); //cout << "strCoord_X3: " << strCoord_X3 << endl;

			if(strCoord_X3 != STRING_EMPTY) {
				oGridNode->setCoord_X3(std::atof(strCoord_X3.c_str()));
			}
			else {
				oGridNode->setCoord_X3(ZERO);
			}
		}

		if (itListData != lstNodeData.end()) {
			std::string strCD = (*itListData++); //cout << "strCD: " << strCD << endl;

			if(strCD != STRING_EMPTY) {
				oGridNode->setCD(std::atoi(strCD.c_str()));
			}
			else {
				oGridNode->setCD(ZERO);
			}
		}
	}
	catch(std::exception &exc) {

		CLogger::GetLogger()->Log(" <EXCEPTION>: CGFEMReader::CreateGRIDNode " + std::string(exc.what()));

		return NULL;
	}

	return oGridNode;
}


