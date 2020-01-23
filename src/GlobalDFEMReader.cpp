/*
 * GlobalDFEMReader.cpp
 *
 *  Created on: 5 dic. 2019
 *      Author: fernando.olivares
 */

#include "../Headers/GlobalDFEMReader.h"
#include "../Headers/Logger.h"
#include "../Headers/Global.h"
#include "../Headers/DFEMGroup.h"
#include "../Headers/Instance.h"
#include "../Headers/SHELLSection.h"
#include "../Headers/ELSETSection.h"
#include "../Headers/ELEMENTSection.h"
#include "../Headers/DFEMReader.h"

CGlobalDFEMReader* CGlobalDFEMReader::m_pThis = NULL;

#pragma GCC diagnostic ignored "-Wunused-variable"

CGlobalDFEMReader::CGlobalDFEMReader() {

	m_lstPathDataFiles = new ListStringData();
	m_lstPathInstanceFiles = new ListStringData();

	m_strDelimiter = ",";
	m_PathFile = STRING_EMPTY;
	m_PathRoot = STRING_EMPTY;

	m_MapDFEmGroups = new MapDFEMGroups();
	m_MapInstances = new MapInstances();

	m_MapGlobalDFEMObjects = new MapDFEMObjects();
	m_MapGlobalDFEMData = new MapDFEMData();

	m_MapGlobalSHELLSections = new MapSHELLSections();;
	m_MapGlobalELSETSections = new MapELSETSections();
	m_MapGlobalELEMENTSections = new MapELEMENTSections();
}

CGlobalDFEMReader::~CGlobalDFEMReader() {
	m_lstPathDataFiles->clear();
	delete m_lstPathDataFiles;
	m_lstPathDataFiles = NULL;

	m_lstPathInstanceFiles->clear();
	delete m_lstPathInstanceFiles;
	m_lstPathInstanceFiles = NULL;

	for (MapDFEMGroups::iterator it=m_MapDFEmGroups->begin(); it != m_MapDFEmGroups->end(); it++)  {
		delete (*it).second;
		it = m_MapDFEmGroups->erase(it);
	}
	delete m_MapDFEmGroups;
	m_MapDFEmGroups = NULL;

	for (MapInstances::iterator it=m_MapInstances->begin(); it != m_MapInstances->end(); it++)  {
		delete (*it).second;
		it = m_MapInstances->erase(it);
	}
	delete m_MapInstances;
	m_MapInstances = NULL;

	for (MapDFEMObjects::iterator it=m_MapGlobalDFEMObjects->begin(); it != m_MapGlobalDFEMObjects->end(); it++)  {
		delete (*it).second;
		it = m_MapGlobalDFEMObjects->erase(it);
	}
	delete m_MapGlobalDFEMObjects;
	m_MapGlobalDFEMObjects = NULL;

	delete m_pThis;
	m_pThis = NULL;


	for (MapDFEMData::iterator it=m_MapGlobalDFEMData->begin(); it != m_MapGlobalDFEMData->end(); it++)  {
		(*it).second.clear();
		it = m_MapGlobalDFEMData->erase(it);
	}
	delete m_MapGlobalDFEMData;
	m_MapGlobalDFEMData = NULL;

	for (MapSHELLSections::iterator it=m_MapGlobalSHELLSections->begin(); it != m_MapGlobalSHELLSections->end(); it++)  {
		delete (*it).second;

		it = m_MapGlobalSHELLSections->erase(it);
	}
	delete m_MapGlobalSHELLSections;
	m_MapGlobalSHELLSections = NULL;

	for (MapELSETSections::iterator it=m_MapGlobalELSETSections->begin(); it != m_MapGlobalELSETSections->end(); it++)  {
		delete (*it).second;
		it = m_MapGlobalELSETSections->erase(it);
	}
	delete m_MapGlobalSHELLSections;
	m_MapGlobalSHELLSections = NULL;

	for (MapELEMENTSections::iterator it=m_MapGlobalELEMENTSections->begin(); it != m_MapGlobalELEMENTSections->end(); it++)  {
		delete (*it).second;
		it = m_MapGlobalELEMENTSections->erase(it);
	}
	delete m_MapGlobalELEMENTSections;
	m_MapGlobalELEMENTSections = NULL;

	delete m_pThis;
	m_pThis = NULL;
}

/**
 *
 * @return
 */
CGlobalDFEMReader* CGlobalDFEMReader::GetCGlobalDFEMReader()
{
    if (m_pThis == NULL)
    {
            m_pThis = new CGlobalDFEMReader;
    }
    return m_pThis;
}

/**
 *
 * @return
 */
bool CGlobalDFEMReader::LoadAllPathsDataFiles() {
	bool bReturn = RESULT_KO;

	ListStringData *lstAuxDataFiles = NULL;
	bool bContinue = true;

	std::string strItem = STRING_EMPTY;
	ListStringData::iterator itAux = m_pThis->getLstPathDataFiles()->begin();

	try {

		while(bContinue) {

			if(strItem != STRING_EMPTY) {

				itAux = std::find(m_pThis->getLstPathDataFiles()->begin(), m_pThis->getLstPathDataFiles()->end(), strItem);
				strItem = STRING_EMPTY;
			}


			for (ListStringData::iterator itLine = itAux; itLine != m_pThis->getLstPathDataFiles()->end();  itLine++) {

				auto nx = std::next(itLine, 1);
				if(nx != m_pThis->getLstPathDataFiles()->end()) {
					strItem = (*nx);
				}

				std::string strFile = (*itLine);
				std::string strPathFile = m_pThis->getPathRoot() + (*itLine);

				CGlobal::Replace(strPathFile, "/cygdrive/c/", "C:/");

				lstAuxDataFiles = CGlobal::GetGlobal()->ReadFileBetweenPatterns(strPathFile,"", "");

				if(lstAuxDataFiles != NULL && lstAuxDataFiles->size() > 0) {

					ListStringData *lstAux = m_pThis->getLstPathDataFiles();
					lstAux->remove(strFile);

					for(ListStringData::iterator it = lstAuxDataFiles->begin(); it != lstAuxDataFiles->end(); it++) {
						ListStringData::iterator itFind = std::find(lstAux->begin(), lstAux->end(), (*it));

						if(itFind == lstAux->end()) {
							lstAux->push_back((*it));
						}
					}
				}

				if(lstAuxDataFiles!= NULL) {
					bContinue = (lstAuxDataFiles->size() > 0);
				}

				if(bContinue) {
					break;
				}
			}
		}

		bReturn = RESULT_OK;
	}
	catch(std::exception &exc) {

		CLogger::GetLogger()->Log(" <EXCEPTION>: CGlobalDFEMReader::LoadPathsDataFiles " + std::string(exc.what()));
	}

	CGlobal::GetGlobal()->ShowListData(*m_pThis->getLstPathDataFiles());

	return bReturn;
}

/**
 *
 * @return
 */
bool CGlobalDFEMReader::LoadAllInstanceDataFiles() {
	bool bReturn = RESULT_KO;

	ListStringData *lstAuxInstanceFiles = NULL;
	bool bContinue = true;

	std::string strItem = STRING_EMPTY;
	ListStringData::iterator itAux = m_pThis->getLstPathInstanceFiles()->begin();
	ListStringData::iterator itProcessor;

	try {

		while(bContinue) {

			if(strItem != STRING_EMPTY) {
				itAux = std::find(m_pThis->getLstPathInstanceFiles()->begin(), m_pThis->getLstPathInstanceFiles()->end(), strItem);
				strItem = STRING_EMPTY;
			}

			for (ListStringData::iterator itLine = itAux; itLine != m_pThis->getLstPathInstanceFiles()->end();  itLine++) {

				/*
				auto nx = std::next(itLine, 1);
				if(nx != m_pThis->getLstPathDataFiles()->end()) {
					strItem = (*nx);
				}
				*/

				std::string strFile = (*itLine);
				std::string strPathFile = m_pThis->getPathRoot() + (*itLine);

				CGlobal::Replace(strPathFile, "/cygdrive/c/", "C:/");
				lstAuxInstanceFiles = CGlobal::GetGlobal()->ReadFileBetweenPatterns(strPathFile,"", "");

				if(lstAuxInstanceFiles != NULL && lstAuxInstanceFiles->size() > 0) {

					ListStringData *lstAux = m_pThis->getLstPathInstanceFiles();
					lstAux->remove(strFile);

					for(ListStringData::iterator it = lstAuxInstanceFiles->begin(); it != lstAuxInstanceFiles->end(); it++) {
						ListStringData::iterator itFind = std::find(lstAux->begin(), lstAux->end(), (*it));

						if(itFind == lstAux->end()) {

							lstAux->push_back((*it));
						}
					}
				}

				if(lstAuxInstanceFiles!= NULL) {
					bContinue = (lstAuxInstanceFiles->size() > 0);
				}

				if(bContinue) break;
			}
		}

		bReturn = RESULT_OK;
	}
	catch(std::exception &exc) {

		CLogger::GetLogger()->Log(" <EXCEPTION>: CGlobalDFEMReader::LoadAllInstanceDataFiles " + std::string(exc.what()));
	}

	CGlobal::GetGlobal()->ShowListData(*m_pThis->getLstPathInstanceFiles());

	return bReturn;
}


/**
 *
 * @return
 */
bool CGlobalDFEMReader::LoadMainDataFile(std::string strDFEMFile) {

	bool bReturn = RESULT_KO;

	std::string strPathFile = m_pThis->getPathRoot() + strDFEMFile;

	CGlobal::Replace(strPathFile, "/cygdrive/c/", "C:/");


	try {
		ListStringData *lstDataFiles = CGlobal::GetGlobal()->ReadFileBetweenPatterns(strPathFile,"", BEGIN_ASSEMBLY);
		m_pThis->setLstPathDataFiles(lstDataFiles);
		//CGlobal::GetGlobal()->ShowListData(*lstDataFiles);

		ListStringData *lstInstanceFiles = CGlobal::GetGlobal()->ReadFileBetweenPatterns(strPathFile,BEGIN_ASSEMBLY, END_ASSEMBLY);
		m_pThis->setLstPathInstanceFiles(lstInstanceFiles);
		CGlobal::GetGlobal()->ShowListData(*lstInstanceFiles);

		bReturn = (lstDataFiles->size() > 0 && lstInstanceFiles->size() > 0);
	}
	catch(std::exception &exc) {

		CLogger::GetLogger()->Log(" <EXCEPTION>: CGlobalDFEMReader::LoadMainDataFile " + std::string(exc.what()));
	}

	return bReturn;
}

/**
 *
 * @param lstDFEMFile
 * @return
 */
bool CGlobalDFEMReader::LoadGlobalDFEMDataFile(std::string strPathFile) {
	bool bReturn = RESULT_KO;

	try {

		ListStringData *lstDFEMFile = CGlobal::GetGlobal()->ReadFile(strPathFile);

		if((lstDFEMFile == NULL) ||
	       (lstDFEMFile != NULL && lstDFEMFile->size() <= 0)) return bReturn;

		CDFEMGroup *oDFEmGroup = new CDFEMGroup();

		std::string strPartName = m_pThis->LoadPartNameSection(lstDFEMFile);
		MapInstances::iterator itInstance = m_pThis->getMapInstances()->find(strPartName);

		oDFEmGroup->setPartName(strPartName);
		oDFEmGroup->setInstanceName((*itInstance).second->getInstanceName());

		m_pThis->LoadGlobalNODESection(lstDFEMFile, *oDFEmGroup);
		m_pThis->LoadGlobalELEMENTSection(lstDFEMFile, *oDFEmGroup);
		m_pThis->LoadGlobalSHELLSection(lstDFEMFile, *oDFEmGroup);
		m_pThis->LoadGlobalELSETSection(lstDFEMFile, *oDFEmGroup);


		MapDFEMGroups::iterator itMap = m_pThis->getMapDFEMGroups()->begin();
		m_pThis->getMapDFEMGroups()->insert(itMap, std::pair<std::string, CDFEMGroup *>(strPartName, oDFEmGroup));


		bReturn = RESULT_OK;

		lstDFEMFile->clear();
		delete lstDFEMFile;
		lstDFEMFile = NULL;
	}
	catch(std::exception &exc) {
		CLogger::GetLogger()->Log(" <EXCEPTION>: CGlobalDFEMReader::LoadGlobalDFEMDataFile " + std::string(exc.what()));
	}

	return bReturn;
}

/**
 *
 * @param lstDFEMFile
 * @return
 */
bool  CGlobalDFEMReader::LoadGlobalNODESection(ListStringData *lstDFEMFile, CDFEMGroup &oDFEMGroup) {

	bool bReturn = RESULT_KO;

	try {

		if((lstDFEMFile == NULL) ||
	       (lstDFEMFile != NULL && lstDFEMFile->size() <= 0)) return bReturn;

		std::string strReadLine = STRING_EMPTY;
		ListStringData dataList;
		bool bIniSectionNode = false;

		MapInstances::iterator itInstance = m_pThis->getMapInstances()->find(oDFEMGroup.getPartName());

		for(ListStringData::iterator itLine = lstDFEMFile->begin(); itLine != lstDFEMFile->end(); itLine++) {

			strReadLine = (*itLine);
			CGlobal::Trim(strReadLine);

			if(CGlobal::NumberOccurrences(strReadLine, '*') > ZERO &&
			  !CGlobal::StartsWithPattern(strReadLine, NODE) &&
			  !CGlobal::StartsWithPattern(strReadLine, NODE_LOW)) {

				bIniSectionNode = false;
				continue;
			}

			if (CGlobal::StartsWithPattern(strReadLine, NODE) || CGlobal::StartsWithPattern(strReadLine, NODE_LOW)) {
				bIniSectionNode = true;
				continue;
			}


			if(CGlobal::NumberOccurrences(strReadLine, '*') == ZERO && bIniSectionNode) {

				ListStringData lstNodeData = CGlobal::ParseDataLine(strReadLine, m_pThis->getDelimiter(), true);

				if (lstNodeData.size() > 0)
				{
					if(itInstance !=  m_pThis->getMapInstances()->end()) {

						ListStringData::iterator it = lstNodeData.begin();

						std::string strIdNode = (*it);
						std::string strKeyDFEMObject = (*itInstance).second->getInstanceName() + "."  + strIdNode;


						CDFEMObject *nodeObject = new CDFEMObject();
						nodeObject->setIdNode((*it++));
						nodeObject->setCoord_X(std::stof((*it++)));
						nodeObject->setCoord_Y(std::stof((*it++)));
						nodeObject->setCoord_Z(std::stof((*it)));

						MapDFEMData::iterator itDEFEMData = oDFEMGroup.getMapDFEMData()->begin();
						oDFEMGroup.getMapDFEMData()->insert(itDEFEMData, std::pair<std::string, ListStringData>(strKeyDFEMObject,lstNodeData));

						MapDFEMData::iterator itGlobalDFEMData = m_pThis->getMapGlobalDFEMData()->begin();
						m_pThis->getMapGlobalDFEMData()->insert(itGlobalDFEMData, std::pair<std::string, ListStringData>(strKeyDFEMObject,lstNodeData));


						MapDFEMObjects::iterator itMapObject = oDFEMGroup.getMapDFEMObjects()->begin();
						oDFEMGroup.getMapDFEMObjects()->insert(itMapObject, std::pair<std::string, CDFEMObject*>(strKeyDFEMObject, nodeObject));

						MapDFEMObjects::iterator itGlobalDFEMObject = m_pThis->getMapGlobalDFEMObjects()->begin();
						m_pThis->getMapGlobalDFEMObjects()->insert(itGlobalDFEMObject, std::pair<std::string, CDFEMObject*>(strKeyDFEMObject,nodeObject));
					}
				}
			}
		}

		bReturn = RESULT_OK;
	}
	catch(std::exception &exc) {

		CLogger::GetLogger()->Log(" <EXCEPTION>: CGlobalDFEMReader::LoadGlobalNODESection " + std::string(exc.what()));
	}

	return bReturn;
}

/**
 *
 * @param lstDFEMFile
 * @return
 */
bool CGlobalDFEMReader::LoadGlobalSHELLSection(ListStringData *lstDFEMFile, CDFEMGroup &oDFEMGroup) {

	bool bReturn = RESULT_KO;

	try {

		if((lstDFEMFile == NULL) ||
	       (lstDFEMFile != NULL && lstDFEMFile->size() <= 0)) return bReturn;


		bool bIniSectionShell = false;
		std::string strSHELLName = STRING_EMPTY;
		std::string strSHELLMaterial = STRING_EMPTY;
		std::string strSHELLValue = STRING_EMPTY;

		for(ListStringData::iterator itLine = lstDFEMFile->begin(); itLine != lstDFEMFile->end(); itLine++) {

			std::string strReadLine = (*itLine);
			CGlobal::GetGlobal()->Trim(strReadLine);

			if(!CGlobal::StartsWithPattern(strReadLine, SHELL) && CGlobal::NumberOccurrences(strReadLine, '*') > ZERO) {
				bIniSectionShell = false;
				continue;
			}

			if (CGlobal::StartsWithPattern(strReadLine, SHELL)) {

				bIniSectionShell = true;
				strSHELLName = CGlobal::GetGlobal()->GetELSETName(strReadLine, m_pThis->getDelimiter());
				ListStringData::iterator itAux = ++itLine;

				if(itAux != lstDFEMFile->end()) {

					strReadLine = (*itAux);
					CGlobal::GetGlobal()->Trim(strReadLine);

					if(strReadLine == STRING_EMPTY) continue;

					if(CGlobal::NumberOccurrences(strReadLine, '*') == ZERO && bIniSectionShell) {

						ListStringData lstValues = CGlobal::GetGlobal()->ParseDataLine(strReadLine, m_pThis->getDelimiter(), true);
						std::string strShellValue = SZERO;

						if(lstValues.size() > 0) {

							strShellValue = CGlobal::GetGlobal()->GetItem(lstValues, 0);
						}

						if(CGlobal::GetGlobal()->IsNumber(strShellValue)) {

							CSHELLSection *shellSection = new CSHELLSection();
							shellSection->setShellName(strSHELLName);
							shellSection->setShellValue(std::stof(strShellValue));

							MapSHELLSections::iterator itShellSections = oDFEMGroup.getMapShellSections()->begin();
							oDFEMGroup.getMapShellSections()->insert(itShellSections, std::pair<std::string, CSHELLSection*>(strSHELLName, shellSection));

							std::string strkeyShell = oDFEMGroup.getInstanceName() + "." + strSHELLName;
							MapSHELLSections::iterator itGlobalMapShell = m_pThis->getMapGlobalShellSections()->begin();
							m_pThis->getMapGlobalShellSections()->insert(itGlobalMapShell, std::pair<std::string, CSHELLSection*>(strkeyShell, shellSection));
						}
					}
				}
			}
		}

		bReturn = RESULT_OK;
	}
	catch(std::exception &exc) {
		CLogger::GetLogger()->Log(" <EXCEPTION>: CGlobalDFEMReader::LoadGlobalSHELLSection " + std::string(exc.what()));
	}

	return bReturn;
}

/**
 *
 * @param lstDFEMFile
 * @return
 */
bool CGlobalDFEMReader::LoadGlobalELSETSection(ListStringData *lstDFEMFile, CDFEMGroup &oDFEMGroup) {

	bool bReturn = RESULT_KO;

	try {

		if((lstDFEMFile == NULL) ||
	       (lstDFEMFile != NULL && lstDFEMFile->size() <= 0)) return bReturn;

		std::string strReadLine = STRING_EMPTY;
		ListStringData dataList;

		bool bIniSectionElset = false;
		std::string strElsetName = STRING_EMPTY;

		CELSETSection *elsetSection = NULL;

		MapInstances::iterator itInstance = m_pThis->getMapInstances()->find(oDFEMGroup.getPartName());

		for(ListStringData::iterator itLine = lstDFEMFile->begin(); itLine != lstDFEMFile->end(); itLine++) {

			std::string strReadLine = (*itLine);
			CGlobal::GetGlobal()->Trim(strReadLine);

			if(strReadLine == STRING_EMPTY) continue;

			if (CGlobal::StartsWithPattern(strReadLine, ELSET) && !bIniSectionElset) {

				bIniSectionElset = true;

				strElsetName = CGlobal::GetGlobal()->GetELSETName(strReadLine, m_pThis->getDelimiter());

				if(itInstance !=  m_pThis->getMapInstances()->end()) {

					elsetSection = new CELSETSection();
					elsetSection->setElsetName(strElsetName);
					elsetSection->setInstanceName((*itInstance).second->getInstanceName());
				}

				continue;
			}

			if(CGlobal::NumberOccurrences(strReadLine, '*') > ZERO)   {
				if(bIniSectionElset && elsetSection != NULL) {

					MapELSETSections::iterator itElsetSections = oDFEMGroup.getMapElsetSections()->begin();
					oDFEMGroup.getMapElsetSections()->insert(itElsetSections, std::pair<std::string, CELSETSection*>(strElsetName, elsetSection));

					std::string strKeyElset = oDFEMGroup.getInstanceName() + "." + strElsetName;
					MapELSETSections::iterator itGlobalMapElset = m_pThis->getMapGlobalElsetSections()->begin();
					m_pThis->getMapGlobalElsetSections()->insert(itGlobalMapElset, std::pair<std::string, CELSETSection*>(strKeyElset, elsetSection));

					//Goto Prev position to process
					itLine--;
				}

				bIniSectionElset = false;
				continue;
			}

			if(CGlobal::NumberOccurrences(strReadLine, '*') == ZERO && bIniSectionElset) {

				ListStringData *lstNodeData = CGlobal::ParseDataLine(strReadLine, m_pThis->getDelimiter(), INFINITE, true);

				if (lstNodeData->size() > 0) {

					elsetSection->getListNodes()->splice(elsetSection->getListNodes()->end(), *lstNodeData);
				}
			}
		}

		bReturn = RESULT_OK;
	}
	catch(std::exception &exc) {
		CLogger::GetLogger()->Log(" <EXCEPTION>: CGlobalDFEMReader::LoadGlobalELSETSection " + std::string(exc.what()));
	}

	return bReturn;
}

/**
 *
 * @param lstDFEMFile
 * @return
 */
bool CGlobalDFEMReader::LoadGlobalELEMENTSection(ListStringData *lstDFEMFile, CDFEMGroup &oDFEMGroup) {

	bool bReturn = RESULT_KO;

	try {

		if((lstDFEMFile == NULL) ||
	       (lstDFEMFile != NULL && lstDFEMFile->size() <= 0)) return bReturn;

		std::string strReadLine = STRING_EMPTY;
		ListStringData dataList;
		bool bIniSectionElement = false;
		std::string strElementName = STRING_EMPTY;
		CELEMENTSection *elementSection = NULL;

		MapInstances::iterator itInstance = m_pThis->getMapInstances()->find(oDFEMGroup.getPartName());

		for(ListStringData::iterator itLine = lstDFEMFile->begin(); itLine != lstDFEMFile->end(); itLine++) {

			std::string strReadLine = (*itLine);
			CGlobal::GetGlobal()->Trim(strReadLine);

			if(strReadLine == STRING_EMPTY) continue;

			if(!CGlobal::StartsWithPattern(strReadLine, ELEMENTS) &&
			   !CGlobal::StartsWithPattern(strReadLine, ELEMENTS_LOW) &&
			   CGlobal::NumberOccurrences(strReadLine, '*') > ZERO) {

				if(bIniSectionElement && elementSection != NULL) {

					MapELEMENTSections::iterator itElementSections = oDFEMGroup.getMapElementSections()->begin();
					oDFEMGroup.getMapElementSections()->insert(itElementSections, std::pair<std::string, CELEMENTSection*>(strElementName, elementSection));


					std::string strKeyElement = oDFEMGroup.getInstanceName() + "." + strElementName;
					MapELEMENTSections::iterator itGlobalMapElements = m_pThis->getMapGlobalElementSections()->begin();

					MapELEMENTSections::iterator itFind = m_pThis->getMapGlobalElementSections()->find(strKeyElement);
					if(itFind == m_pThis->getMapGlobalElementSections()->end()) {
						m_pThis->getMapGlobalElementSections()->insert(itGlobalMapElements, std::pair<std::string, CELEMENTSection*>(strKeyElement, elementSection));
					}
					else {

						(*itFind).second->getListNodes()->splice((*itFind).second->getListNodes()->end(), *elementSection->getListNodes());
					}


				}

				bIniSectionElement = false;
				continue;
			}

			if (CGlobal::StartsWithPattern(strReadLine, ELEMENTS) ||
				CGlobal::StartsWithPattern(strReadLine, ELEMENTS_LOW)) {

				if(bIniSectionElement && strElementName != STRING_EMPTY) {

					//CELEMENTSection *oSection = elementSection;
					//std::string strName = strElementName;

					MapELEMENTSections::iterator itElementSections = oDFEMGroup.getMapElementSections()->begin();
					oDFEMGroup.getMapElementSections()->insert(itElementSections, std::pair<std::string, CELEMENTSection*>(strElementName, elementSection));

					std::string strKeyElement = oDFEMGroup.getInstanceName() + "." + strElementName;
					MapELEMENTSections::iterator itGlobalMapElements = m_pThis->getMapGlobalElementSections()->begin();

					MapELEMENTSections::iterator itFind = m_pThis->getMapGlobalElementSections()->find(strKeyElement);
					if(itFind == m_pThis->getMapGlobalElementSections()->end()) {
						m_pThis->getMapGlobalElementSections()->insert(itGlobalMapElements, std::pair<std::string, CELEMENTSection*>(strKeyElement, elementSection));
					}
					else {

						(*itFind).second->getListNodes()->splice((*itFind).second->getListNodes()->end(), *elementSection->getListNodes());
					}
				}

				bIniSectionElement = true;
				elementSection = NULL;

				strElementName = CGlobal::GetGlobal()->GetELSETName(strReadLine, m_pThis->getDelimiter());

				if(itInstance !=  m_pThis->getMapInstances()->end()) {

					elementSection = new CELEMENTSection();
					elementSection->setElementName(strElementName);
					elementSection->setInstanceName((*itInstance).second->getInstanceName());
				}

				continue;
			}

			if(bIniSectionElement && CGlobal::NumberOccurrences(strReadLine, '*') == ZERO) {

				ListStringData *lstNodeData = CGlobal::ParseDataLine(strReadLine, m_pThis->getDelimiter(), 1, true);

				if (lstNodeData->size() > 0 && elementSection != NULL) {

					elementSection->getListNodes()->splice(elementSection->getListNodes()->end(), *lstNodeData);
				}
			}
		}

		bReturn = RESULT_OK;
	}
	catch(std::exception &exc) {
		CLogger::GetLogger()->Log(" <EXCEPTION>: CGlobalDFEMReader::LoadGlobalELEMENTSection " + std::string(exc.what()));
	}

	return bReturn;
}

/**
 *
 * @param lstDFEMFile
 * @return
 */
bool CGlobalDFEMReader::LoadGlobalInstanceData(std::string strPathFile) {
	bool bReturn = RESULT_KO;

	try {

		ListStringData *lstInstanceFile = CGlobal::GetGlobal()->ReadFile(strPathFile);

		if((lstInstanceFile == NULL) ||
	       (lstInstanceFile != NULL && lstInstanceFile->size() <= 0)) return bReturn;

		std::string strReadLine = STRING_EMPTY;
		ListStringData dataList;
		bool bIniSectionInstance = false;

		for(ListStringData::iterator itLine = lstInstanceFile->begin(); itLine != lstInstanceFile->end(); itLine++) {

			strReadLine = (*itLine);
			CGlobal::Trim(strReadLine);

			if(!CGlobal::StartsWithPattern(strReadLine, INSTANCE) &&
			   !CGlobal::StartsWithPattern(strReadLine, INSTANCE_UPP) &&
				CGlobal::NumberOccurrences(strReadLine, '*') > ZERO) {
				bIniSectionInstance = false;
				continue;
			}

			if (CGlobal::StartsWithPattern(strReadLine, INSTANCE) || CGlobal::StartsWithPattern(strReadLine, INSTANCE_UPP)) {

				bIniSectionInstance = true;

				CInstance *oInstance = new CInstance();

				oInstance->setInstanceName(CGlobal::GetGlobal()->GetInstanceName(strReadLine, m_pThis->getDelimiter()));
				oInstance->setPartName(CGlobal::GetGlobal()->GetInstancePart(strReadLine, m_pThis->getDelimiter()));

				ListStringData::iterator itAux = ++itLine;

				strReadLine = (*itAux);
				CGlobal::GetGlobal()->Trim(strReadLine);
				if(strReadLine == STRING_EMPTY) continue;

				if(CGlobal::NumberOccurrences(strReadLine, '*') == ZERO && bIniSectionInstance) {

					ListStringData lstValues = CGlobal::GetGlobal()->ParseDataLine(strReadLine, m_pThis->getDelimiter(), true);

					if(lstValues.size() > 0) {

						ListStringData::iterator itValue = lstValues.begin();

						oInstance->setValue1(std::stof((*itValue++)));
						oInstance->setValue2(std::stof((*itValue++)));
						oInstance->setValue3(std::stof((*itValue)));
					}
				}

				MapInstances::iterator itMap = m_pThis->getMapInstances()->begin();
				m_pThis->getMapInstances()->insert(itMap, std::pair<std::string, CInstance *>(oInstance->getPartName(),oInstance));
			}
		}

		lstInstanceFile->clear();
		delete lstInstanceFile;
		lstInstanceFile = NULL;
	}
	catch(std::exception &exc) {
		CLogger::GetLogger()->Log(" <EXCEPTION>: CGlobalDFEMReader::LoadGlobalInstanceData " + std::string(exc.what()));
	}

	return bReturn;
}

/**
 *
 * @param lstDFEMFile
 * @return
 */
std::string CGlobalDFEMReader::LoadPartNameSection(ListStringData *lstDFEMFile) {

	std::string strPartName = STRING_EMPTY;

	try {

		if((lstDFEMFile == NULL) ||
	       (lstDFEMFile != NULL && lstDFEMFile->size() <= 0)) return strPartName;

		std::string strReadLine = STRING_EMPTY;

		for(ListStringData::iterator itLine = lstDFEMFile->begin(); itLine != lstDFEMFile->end(); itLine++) {

			std::string strReadLine = (*itLine);
			CGlobal::GetGlobal()->Trim(strReadLine);

			if(strReadLine == STRING_EMPTY) continue;

			if(CGlobal::StartsWithPattern(strReadLine, PART_DFEM)) {

				CGlobal::GetGlobal()->RemoveString(strReadLine, PART_DFEM);
				strPartName = strReadLine;

				break;
			}
			else
				continue;
		}
	}
	catch(std::exception &exc) {
		CLogger::GetLogger()->Log(" <EXCEPTION>: CGlobalDFEMReader::LoadPartNameSection " + std::string(exc.what()));
	}

	return strPartName;
}

/**
 *
 * @return
 */
MapDFEMObjects * CGlobalDFEMReader::LoadGlobalMapDFEMObjects() {

	MapDFEMObjects  *mapReturn = new MapDFEMObjects();

	try {

		for(MapDFEMGroups::iterator itDFEMGroup = m_pThis->getMapDFEMGroups()->begin();
									itDFEMGroup != m_pThis->getMapDFEMGroups()->end();
									itDFEMGroup++) {

			for(MapDFEMObjects::iterator itDFEMObject = (*itDFEMGroup).second->getMapDFEMObjects()->begin();
										 itDFEMObject != (*itDFEMGroup).second->getMapDFEMObjects()->end();
										 itDFEMObject++) {


				MapDFEMObjects::iterator itGlobalDFEMObject = mapReturn->begin();
				mapReturn->insert(itGlobalDFEMObject, std::pair<std::string, CDFEMObject*>((*itDFEMObject).second->getIdNode(),(*itDFEMObject).second));


				/*
				MapInstances::iterator itInstance = m_pThis->getMapInstances()->find((*itDFEMGroup).second->getPartName());

				if(itInstance !=  m_pThis->getMapInstances()->end()) {

					std::string strKeyDFEMObject = (*itInstance).second->getInstanceName() + "."  +
												   (*itDFEMObject).second->getIdNode();

					MapDFEMObjects::iterator itGlobalDFEMObject = mapReturn->begin();
					mapReturn->insert(itGlobalDFEMObject, std::pair<std::string, CDFEMObject*>(strKeyDFEMObject,(*itDFEMObject).second));
				}
				*/
			}
		}
	}
	catch(std::exception &exc) {
		CLogger::GetLogger()->Log(" <EXCEPTION>: CGlobalDFEMReader::LoadGlobalMapDFEMObjects " + std::string(exc.what()));
	}

	return mapReturn;
}

/**
 *
 * @return
 */
bool CGlobalDFEMReader::LoadGlobalDFEMObjects() {

	bool bReturn = RESULT_KO;

	try {

		MapDFEMObjects *mapGlobalDFEMObjects = m_pThis->LoadGlobalMapDFEMObjects();

		m_pThis->setMapGlobalDFEMObjects(mapGlobalDFEMObjects);

	}
	catch(std::exception &exc) {
		CLogger::GetLogger()->Log(" <EXCEPTION>: CGlobalDFEMReader::LoadGlobalDFEMObjects " + std::string(exc.what()));
	}

	return true;
}

/**
 *
 * @return
 */
MapDFEMData * CGlobalDFEMReader::GetGlobalMapDFEMData() {

	MapDFEMData  *mapReturn = new MapDFEMData;

	try {

		for(MapDFEMGroups::iterator itDFEMGroup = m_pThis->getMapDFEMGroups()->begin();
									itDFEMGroup != m_pThis->getMapDFEMGroups()->end();
									itDFEMGroup++) {

			for(MapDFEMObjects::iterator itDFEMObject = (*itDFEMGroup).second->getMapDFEMObjects()->begin();
										 itDFEMObject != (*itDFEMGroup).second->getMapDFEMObjects()->end();
										 itDFEMObject++) {

				MapInstances::iterator itInstance = m_pThis->getMapInstances()->find((*itDFEMGroup).second->getPartName());

				if(itInstance !=  m_pThis->getMapInstances()->end()) {

					ListStringData lstDFEMData;

					std::string strKeyDFEMData = (*itInstance).second->getInstanceName() + "."  +
												   (*itDFEMObject).second->getIdNode();

					lstDFEMData.push_back(strKeyDFEMData);
					lstDFEMData.push_back(std::to_string((*itDFEMObject).second->getCoord_X()));
					lstDFEMData.push_back(std::to_string((*itDFEMObject).second->getCoord_Y()));
					lstDFEMData.push_back(std::to_string((*itDFEMObject).second->getCoord_Z()));

					MapDFEMData::iterator itGlobalDFEMData = mapReturn->begin();
					mapReturn->insert(itGlobalDFEMData, std::pair<std::string, ListStringData>(strKeyDFEMData,lstDFEMData));
				}
			}
		}
	}
	catch(std::exception &exc) {
		CLogger::GetLogger()->Log(" <EXCEPTION>: CGlobalDFEMReader::GetGlobalMapDFEMData " + std::string(exc.what()));
	}

	return mapReturn;
}

/**
 *
 * @return
 */
bool CGlobalDFEMReader::LoadGlobalDFEMData() {

	bool bReturn = RESULT_KO;

	try {
		for(MapDFEMGroups::iterator itGroup = m_pThis->getMapDFEMGroups()->begin();
									itGroup != m_pThis->getMapDFEMGroups()->end();
									itGroup++) {

			CDFEMGroup *oDFEMGroup = (*itGroup).second;
		}

		MapDFEMData *mapGlobalDFEMData = m_pThis->GetGlobalMapDFEMData();

		m_pThis->setMapGlobalDFEMData(mapGlobalDFEMData);

	}
	catch(std::exception &exc) {
		CLogger::GetLogger()->Log(" <EXCEPTION>: CGlobalDFEMReader::LoadGlobalDFEMData " + std::string(exc.what()));
	}

	return true;
}
