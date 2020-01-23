/*
 * CSVReader.cpp
 *
 *  Created on: 11 nov. 2019
 *      Author: fernando.olivares
 */

#include "../Headers/CSVReader.h"

#include <stddef.h>
#include <fstream>
#include <iostream>

#include "../Headers/AssociativityFile.h"
#include "../Headers/Connection.h"
#include "../Headers/DFEMNode.h"
#include "../Headers/GFEMNode.h"
#include "../Headers/Logger.h"
#include "../Headers/Node.h"

CCSVReader* CCSVReader::m_pThis = NULL;

#pragma GCC diagnostic ignored "-Wunused-variable"

/**
 * Default Class Contructor
 */
CCSVReader::CCSVReader() {

	m_strDelimiter = ",";
	m_AssociativityFile = new CAssociativityFile();

	m_TieArea = ONE;	//Initialization Value;
}

/**
  Default Class Destructor
 */
CCSVReader::~CCSVReader() {

	delete m_AssociativityFile;
	m_AssociativityFile = NULL;

	delete m_pThis;

}

/**
 *
 * @return
 */
CCSVReader* CCSVReader::GetCSVReader()
{
    if (m_pThis == NULL)
    {
            m_pThis = new CCSVReader();
    }
    return m_pThis;
}

/**
 *
 * @param strPathFile
 * @return
 */
bool CCSVReader::LoadFile(std::string strPathFile) {

	bool bReturn = false;

	try {
		//The first step is Check if exists the csvfile to process

		if(CGlobal::FileExist(strPathFile)) {

			ListStringData *lstAssociativityFile = CGlobal::GetGlobal()->ReadFile(strPathFile);

			if(lstAssociativityFile == NULL || lstAssociativityFile->size() == 0) {
				return false;
			}

			std::string strReadLine = STRING_EMPTY;
			ListStringData dataList;
		    ListStringData *lstDetail1D2D = new ListStringData();

		    for(ListStringData::iterator itLine = lstAssociativityFile->begin(); itLine != lstAssociativityFile->end(); itLine++) {

		    	DataMatrixDFEM1D2D *oDataMatrixDFEM1D2D = NULL;

		    	strReadLine = (*itLine);

		    	lstDetail1D2D->clear();
		    	CGlobal::Trim(strReadLine);

		    	if(strReadLine == STRING_EMPTY)
		    		return false;

		    	if (!CGlobal::StartsWithPattern(strReadLine, DETAIL1D2D)) {
		    		dataList = CGlobal::GetGlobal()->ParseDataLine(strReadLine, getDelimiter(), true);
		    	}

		    	ListStringData *lstListNodes = NULL;
		    	ListStringData *lstListNodesDetail = NULL;

				if(std::stoi(CGlobal::GetItem(dataList, 0)) == TYPE_1D2D) {

					//Obtener la lista de líneas de detalle de la línea que estamos tratando
					std::string strLineAux = STRING_EMPTY;

					ListStringData::iterator itAux = itLine;

					 if(++itAux != lstAssociativityFile->end()) {

						 if (CGlobal::StartsWithPattern((*itAux), DETAIL1D2D)) {

							 lstDetail1D2D->push_back((*itAux));

							 ++itAux;
							 while (itAux != lstAssociativityFile->end()) {
								 if (CGlobal::StartsWithPattern((*itAux), DETAIL1D2D)) {
										lstDetail1D2D->push_back((*itAux));
										itAux++;
								 }
								 else {

									 itLine = --itAux;
									 break;
								 }
							 }
						 }
					 }

					 oDataMatrixDFEM1D2D = CGlobal::GetGlobal()->GetNodesDetail(dataList, lstDetail1D2D, getDelimiter(), std::stoi(CGlobal::GetItem(dataList, 2)));

					 lstListNodes = CGlobal::GetGlobal()->GetUniqueValues(lstDetail1D2D, getDelimiter());
				}

				StoreData(std::stoi(CGlobal::GetItem(dataList, 0)), dataList, lstListNodes, oDataMatrixDFEM1D2D);

				delete lstListNodes;
				lstListNodes = NULL;

				lstDetail1D2D->clear();
				dataList.clear();
			}

		    delete lstDetail1D2D;
		    lstDetail1D2D = NULL;
		}

		bReturn = RESULT_OK;

	}
	catch(std::exception &exc) {

		CLogger::GetLogger()->Log(" <EXCEPTION>: CCSVReader::LoadFile " + std::string(exc.what()));
	}

	return bReturn;
}

/**
 *
 * @param strPathFile
 * @return
 */
bool CCSVReader::LoadGlobalFile(std::string strPathFile) {

	bool bReturn = false;

	try {
		//The first step is Check if exists the csvfile to process

		if(CGlobal::FileExist(strPathFile)) {

			ListStringData *lstAssociativityFile = CGlobal::GetGlobal()->ReadFile(strPathFile);

			if(lstAssociativityFile == NULL || lstAssociativityFile->size() == 0) {
				return false;
			}

			std::string strReadLine = STRING_EMPTY;
			ListStringData dataList;
		    ListStringData *lstDetail1D2D = new ListStringData();

		    for(ListStringData::iterator itLine = lstAssociativityFile->begin(); itLine != lstAssociativityFile->end(); itLine++) {

		    	DataMatrixDFEM1D2D *oDataMatrixDFEM1D2D = NULL;

		    	strReadLine = (*itLine);

		    	lstDetail1D2D->clear();
		    	CGlobal::Trim(strReadLine);

		    	if(strReadLine == STRING_EMPTY)
		    		return false;

		    	if (!CGlobal::StartsWithPattern(strReadLine, DETAIL1D2D)) {
		    		dataList = CGlobal::GetGlobal()->ParseDataLine(strReadLine, getDelimiter(), false);
		    	}

		    	ListStringData *lstListNodes = NULL;
		    	ListStringData *lstListNodesDetail = NULL;

				if(std::stoi(CGlobal::GetItem(dataList, 0)) == TYPE_1D2D) {

					//Obtener la lista de líneas de detalle de la línea que estamos tratando
					std::string strLineAux = STRING_EMPTY;

					ListStringData::iterator itAux = itLine;

					 if(++itAux != lstAssociativityFile->end()) {

						 if (CGlobal::StartsWithPattern((*itAux), DETAIL1D2D)) {

							 lstDetail1D2D->push_back((*itAux));

							 ++itAux;
							 while (itAux != lstAssociativityFile->end()) {
								 if (CGlobal::StartsWithPattern((*itAux), DETAIL1D2D)) {

									lstDetail1D2D->push_back((*itAux));
									itAux++;
								 }
								 else {

									 itLine = --itAux;
									 break;
								 }
							 }
						 }
					 }

					 oDataMatrixDFEM1D2D = CGlobal::GetGlobal()->GetNodesDetail(dataList, lstDetail1D2D, getDelimiter(), std::stoi(CGlobal::GetItem(dataList, 2)));

					 lstListNodes = CGlobal::GetGlobal()->GetUniqueValues(lstDetail1D2D, getDelimiter());
				}

				StoreData(std::stoi(CGlobal::GetItem(dataList, 0)), dataList, lstListNodes, oDataMatrixDFEM1D2D);

				delete lstListNodes;
				lstListNodes = NULL;

				lstDetail1D2D->clear();
				dataList.clear();
			}

		    delete lstDetail1D2D;
		    lstDetail1D2D = NULL;
		}

		bReturn = RESULT_OK;

	}
	catch(std::exception &exc) {

		CLogger::GetLogger()->Log(" <EXCEPTION>: CCSVReader::LoadGlobalFile " + std::string(exc.what()));
	}

	return bReturn;
}

/**
 *
 * @param dType
 * @param dataList
 * @return
 */
bool CCSVReader::StoreData(int dType, std::list<std::string> dataList, ListStringData *lstListNodes, DataMatrixDFEM1D2D *oDataMatrix) {
	bool bReturn = RESULT_KO;
	DataMatrixDFEM1D2D *oAuxDataMatrix = NULL;

	try {

		if(dataList.size() <= 0 ) return bReturn;

		switch(dType) {
			case TYPE_1D2D:
				m_pThis->ProcessData(dataList, m_pThis->GetAssociativityFile()->GetConnections1D2D(), TYPE_1D2D, lstListNodes, oDataMatrix);
				break;
			default:
				m_pThis->ProcessData(dataList, m_pThis->GetAssociativityFile()->GetConnections2D2D(), TYPE_2D2D, NULL, oAuxDataMatrix);
				break;
		}
	}
	catch(std::exception &exc) {
		CLogger::GetLogger()->Log(" <EXCEPTION>: CCSVReader::StoreData " + std::string(exc.what()));
	}

	return bReturn;
}

/**
 *
 * @param dataList
 * @param lstConnection
 * @param dType
 * @param lstUniqueNodes
 * @param lstUniqueNodes
 * @return
 */
bool CCSVReader::ProcessData(std::list<std::string> dataList, ListConnections *lstConnection, int dType, ListStringData *lstUniqueNodes, DataMatrixDFEM1D2D *dataMatrix) {

	bool bReturn = RESULT_KO;

	int dTieArea = -1;
	int dIdConnection = -1;

	try {

		if((dataList.size() <= 0) ||
		(lstConnection == NULL) ||
		(lstUniqueNodes != NULL && lstUniqueNodes->size() <= 0) ||
		(dataMatrix != NULL && dataMatrix->size() <= 0)) return bReturn;

		CConnection *oConnection = new CConnection();
		oConnection->setIdConnection(lstConnection->size() + 1);

		if(dType == TYPE_2D2D ) {
			dTieArea = m_pThis->m_TieArea++;
			oConnection->setTieArea(dTieArea);

			AddGFEMNodes(dataList, oConnection->GetGFEMNodes(), CGlobal::GetNodeType(dType, "G"), dTieArea);
			AddDFEMNodes(dataList, oConnection->GetDFEMNodes(), CGlobal::GetNodeType(dType, "D"), dTieArea);
		}
		else {

			dTieArea = std::stoi(CGlobal::GetItem(dataList, 1));
			oConnection->setTieArea(dTieArea);

			m_pThis->CreateSegments(lstUniqueNodes, oConnection->GetMapSegments());

			AddGFEMNodes(dataList, oConnection->GetGFEMNodes(), CGlobal::GetNodeType(dType, "G"), dTieArea);
			AddDFEMNodes(dataList, oConnection->GetDFEMNodes(), CGlobal::GetNodeType(dType, "D"), dTieArea);

			oConnection->SetMatrixData(dataMatrix);
		}

		lstConnection->push_back(oConnection);

		bReturn = true;
	}
	catch(std::exception &exc) {
		CLogger::GetLogger()->Log(" <EXCEPTION>: CCSVReader::ProcessData " + std::string(exc.what()));
	}

	return bReturn;
}

/**
 * Method that create a Map of CSegment objects with a list passed as parameter
 * @param lstSegments: List with the segments Id's
 * @return: Map Segments created
 */
bool CCSVReader::CreateSegments(ListStringData *lstSegments, MapSegments *mapSegments) {

	bool bReturn = RESULT_KO;

	try {

		if((lstSegments != NULL && lstSegments->size() <= 0) ||
		  mapSegments == NULL) return bReturn;

		for(ListStringData::iterator itSegment = lstSegments->begin(); itSegment != lstSegments->end(); itSegment++) {

			std::string IdSegment = (*itSegment);
			CSegment *oSegment = new CSegment();
			oSegment->setIdSegment(IdSegment);

			MapSegments::iterator itMap = mapSegments->begin();
			mapSegments->insert(itMap, std::pair<std::string, CSegment *>(IdSegment,oSegment));
		}
	}
	catch(std::exception &exc) {
		CLogger::GetLogger()->Log(" <EXCEPTION>: CCSVReader::CreateSegments " + std::string(exc.what()));
	}

	return bReturn;
}

/**
 *
 * @param dataList
 * @param lstGFEMNodes
 * @return
 */
bool CCSVReader::AddGFEMNodes(std::list<std::string> dataList, MapGFEMNodes *mapGFEMNodes, int dType, int dTieArea) {
	bool bReturn = RESULT_KO;

	try {

		if(dataList.size() <= 0 || mapGFEMNodes == NULL) return bReturn;

		int dNumGFEM = std::stoi(CGlobal::GetItem(dataList, 0));

		for(int dInd = 1; dInd <= dNumGFEM; dInd++) {

			std::string strNodeGFEM = CGlobal::GetItem(dataList, dInd);

			if(strNodeGFEM == STRING_EMPTY) break;

			CGFEMNode *oGFEMNode = new CGFEMNode();
			oGFEMNode->setNodeType(dType);
			oGFEMNode->setTieArea(dTieArea);
			oGFEMNode->setIdNode(std::stoi(CGlobal::Trim((strNodeGFEM))));
			oGFEMNode->setName(CGlobal::Trim((strNodeGFEM)));
			oGFEMNode->setStrIdNode(CGlobal::Trim((strNodeGFEM)));

			MapGFEMNodes::iterator itMap = mapGFEMNodes->begin();
			mapGFEMNodes->insert(itMap, std::pair<int, CGFEMNode *>(oGFEMNode->getIdNode(),oGFEMNode));
		}

		bReturn = RESULT_OK;
	}
	catch(std::exception &exc) {
		CLogger::GetLogger()->Log(" <EXCEPTION>: CCSVReader::AddGFEMNodes " + std::string(exc.what()));
	}

	return bReturn;
}

/**
 *
 * @param dataList
 * @param lstDFEMNodes
 * @return
 */
bool CCSVReader::AddDFEMNodes(std::list<std::string> dataList, MapDFEMNodes *mapDFEMNodes, int dType, int dTieArea) {
	bool bReturn = RESULT_KO;

	try {

		if(dataList.size() <= 0 || mapDFEMNodes == NULL) return bReturn;

		int dNumGFEM = std::stoi(CGlobal::GetItem(dataList, 0));
		int dOFFSet = (dNumGFEM + 2);
		int dNumDFEM = std::stoi(CGlobal::GetItem(dataList, dOFFSet-1));

		if(2 + (dNumGFEM + dNumDFEM) != (int)dataList.size()) {

			cout << "***********************************************************************************************************" << endl;
			cout << "***********************************************************************************************************" << endl;
			cout << "***********************************************************************************************************" << endl;

			cout << " Associativity input data file isn't not correct. It Has incoherent data in same connection data line." << endl;
			CGlobal::GetGlobal()->ShowListData(dataList);

			cout << "***********************************************************************************************************" << endl;
			cout << "***********************************************************************************************************" << endl;
			cout << "***********************************************************************************************************" << endl;
			//return bReturn;
		}

		for(int dInd = dOFFSet; dInd < (int)dataList.size(); dInd++) {

			std::string strNodeDFEM = CGlobal::GetItem(dataList, dInd);

			std::string strPartNode = strNodeDFEM;
			std::string strIdNode = strNodeDFEM;

			std::string composedStrIdNode = strNodeDFEM;

			if(!CGlobal::GetGlobal()->IsNumber(strNodeDFEM)) {

				CGlobal::GetGlobal()->GetTwoParts(strNodeDFEM, ".", strPartNode, strIdNode);
			}

			if(strNodeDFEM == STRING_EMPTY) break;

			CDFEMNode *oDFEMNode = new CDFEMNode();
			oDFEMNode->setNodeType(dType);
			oDFEMNode->setTieArea(dTieArea);
			oDFEMNode->setIdNode(std::stoi(CGlobal::Trim(strIdNode)));
			oDFEMNode->setName(CGlobal::Trim((strNodeDFEM)));

			if(CGlobal::GetGlobal()->getFormatData() == FORMAT_2) {
				oDFEMNode->setStrIdNode(CGlobal::Trim(strNodeDFEM));
			}
			else {
				oDFEMNode->setStrIdNode(CGlobal::Trim(strIdNode));
			}


			MapDFEMNodes::iterator itMap = mapDFEMNodes->begin();
			mapDFEMNodes->insert(itMap, std::pair<std::string, CDFEMNode *>(oDFEMNode->getStrIdNode(),oDFEMNode));
		}

		bReturn = true;
	}
	catch(std::exception &exc) {
		CLogger::GetLogger()->Log(" <EXCEPTION>: CCSVReader::AddDFEMNodes " + std::string(exc.what()));
	}

	return bReturn;
}

