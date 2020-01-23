/*
 * DFEMReader.cpp
 *
 *  Created on: 13 nov. 2019
 *      Author: fernando.olivares
 */

#include "../Headers/DFEMReader.h"

#include <stddef.h>
#include <fstream>
#include <iostream>

#include "../Headers/Global.h"
#include "../Headers/Logger.h"
#include "../Headers/DFEMObject.h"
#include "../Headers/SHELLSection.h"
#include "../Headers/ELSETSection.h"
#include "../Headers/ELEMENTSection.h"


CDFEMReader* CDFEMReader::m_pThis = NULL;

#pragma GCC diagnostic ignored "-Wunused-variable"

using namespace std;

CDFEMReader::CDFEMReader() {
	m_strDelimiter = ",";

	m_MapDFEMData = new MapDFEMData();
	m_MapDFEMObjects = new MapDFEMObjects();
	m_MapSHELLSections = new MapSHELLSections();
	m_MapELSETSections = new MapELSETSections();
	m_MapELEMENTSections = new MapELEMENTSections();
}

CDFEMReader::~CDFEMReader() {

	for (MapDFEMData::iterator it=m_MapDFEMData->begin(); it != m_MapDFEMData->end(); it++)  {
		(*it).second.clear();
		it = m_MapDFEMData->erase(it);
	}
	delete m_MapDFEMData;
	m_MapDFEMData = NULL;

	for (MapDFEMObjects::iterator it=m_MapDFEMObjects->begin(); it != m_MapDFEMObjects->end(); it++)  {
		delete (*it).second;
		it = m_MapDFEMObjects->erase(it);
	}
	delete m_MapDFEMObjects;
	m_MapDFEMObjects = NULL;

	for (std::map<std::string, CSHELLSection*>::iterator it=m_MapSHELLSections->begin(); it != m_MapSHELLSections->end(); it++)  {
		delete (*it).second;

		it = m_MapSHELLSections->erase(it);
	}
	delete m_MapSHELLSections;
	m_MapSHELLSections = NULL;

	for (MapELSETSections::iterator it=m_MapELSETSections->begin(); it != m_MapELSETSections->end(); it++)  {
		delete (*it).second;
		it = m_MapELSETSections->erase(it);
	}
	delete m_MapELSETSections;
	m_MapELSETSections = NULL;

	for (MapELEMENTSections::iterator it=m_MapELEMENTSections->begin(); it != m_MapELEMENTSections->end(); it++)  {
		delete (*it).second;
		it = m_MapELEMENTSections->erase(it);
	}
	delete m_MapELEMENTSections;
	m_MapELEMENTSections = NULL;

	delete m_pThis;
}

/**
 *
 * @return
 */
CDFEMReader* CDFEMReader::GetDFEMReader()
{
    if (m_pThis == NULL)
    {
            m_pThis = new CDFEMReader;
    }
    return m_pThis;
}

/**
 *
 * @param lstDFEMFile
 * @return
 */
bool CDFEMReader::LoadDFEMData(std::string strPathFile) {
	bool bReturn = RESULT_KO;

	try {

		ListStringData *lstDFEMFile = CGlobal::GetGlobal()->ReadFile(strPathFile);

		if((lstDFEMFile == NULL) ||
	       (lstDFEMFile != NULL && lstDFEMFile->size() <= 0)) return bReturn;

		m_pThis->LoadNODESection(lstDFEMFile);

		m_pThis->LoadSHELLSection(lstDFEMFile);
		m_pThis->LoadELSETSection(lstDFEMFile);
		m_pThis->LoadELEMENTSection(lstDFEMFile);

		bReturn = RESULT_OK;

		lstDFEMFile->clear();
		delete lstDFEMFile;
		lstDFEMFile = NULL;
	}
	catch(std::exception &exc) {
		CLogger::GetLogger()->Log(" <EXCEPTION>: CDFEMReader::LoadDFEMData " + std::string(exc.what()));
	}

	return bReturn;
}

/**
 *
 * @param lstDFEMFile
 * @return
 */
bool  CDFEMReader::LoadNODESection(ListStringData *lstDFEMFile) {

	bool bReturn = RESULT_KO;

	try {

		if((lstDFEMFile == NULL) ||
	       (lstDFEMFile != NULL && lstDFEMFile->size() <= 0)) return bReturn;

		std::string strReadLine = STRING_EMPTY;
		ListStringData dataList;
		bool bIniSectionNode = false;

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
					ListStringData::iterator it = lstNodeData.begin();
					MapDFEMData::iterator itMap = m_pThis->getMapDFEMData()->begin();

					m_pThis->getMapDFEMData()->insert(itMap, std::pair<std::string, ListStringData>((*it),lstNodeData));

					CDFEMObject *nodeObject = new CDFEMObject();
					nodeObject->setIdNode((*it++));
					nodeObject->setCoord_X(std::stof((*it++)));
					nodeObject->setCoord_Y(std::stof((*it++)));
					nodeObject->setCoord_Z(std::stof((*it)));

					MapDFEMObjects::iterator itMapObjects = m_pThis->getMapDFEMObjects()->begin();
					m_pThis->getMapDFEMObjects()->insert(itMapObjects, std::pair<std::string, CDFEMObject*>(nodeObject->getIdNode(), nodeObject));
				}
			}
		}

		bReturn = RESULT_OK;
	}
	catch(std::exception &exc) {

		CLogger::GetLogger()->Log(" <EXCEPTION>: CDFEMReader::LoadNODESection " + std::string(exc.what()));
	}

	return bReturn;
}

/**
 *
 * @param lstDFEMFile
 * @return
 */
bool CDFEMReader::LoadSHELLSection(ListStringData *lstDFEMFile) {

	bool bReturn = RESULT_KO;

	try {

		if((lstDFEMFile == NULL) ||
	       (lstDFEMFile != NULL && lstDFEMFile->size() <= 0)) return bReturn;


		bool bIniSectionShell = false;
		std::string strSHELLName = STRING_EMPTY;
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

						//CGlobal::GetGlobal()->RemoveString(strReadLine, m_pThis->getDelimiter());
						CGlobal::GetGlobal()->Trim(strReadLine);

						ListStringData lstValues = CGlobal::GetGlobal()->ParseDataLine(strReadLine, m_pThis->getDelimiter(), true);
						std::string strShellValue = SZERO;

						if(lstValues.size() > 0) {

							strShellValue = CGlobal::GetGlobal()->GetItem(lstValues, 0);
						}

						if(CGlobal::GetGlobal()->IsNumber(strShellValue)) {

							CSHELLSection *shellSection = new CSHELLSection();
							shellSection->setShellName(strSHELLName);
							shellSection->setShellValue(std::stof(strReadLine));

							MapSHELLSections::iterator itShellSections = m_pThis->getMapShellSections()->begin();
							m_pThis->getMapShellSections()->insert(itShellSections, std::pair<std::string, CSHELLSection*>(strSHELLName, shellSection));
						}
					 }
				 }
			}
		}

		bReturn = RESULT_OK;
	}
	catch(std::exception &exc) {
		CLogger::GetLogger()->Log(" <EXCEPTION>: CDFEMReader::LoadSHELLSection " + std::string(exc.what()));
	}

	return bReturn;
}


/**
 *
 * @param lstDFEMFile
 * @return
 */
bool CDFEMReader::LoadELSETSection(ListStringData *lstDFEMFile) {

	bool bReturn = RESULT_KO;

	try {

		if((lstDFEMFile == NULL) ||
	       (lstDFEMFile != NULL && lstDFEMFile->size() <= 0)) return bReturn;

		std::string strReadLine = STRING_EMPTY;
		ListStringData dataList;

		bool bIniSectionElset = false;
		std::string strElsetName = STRING_EMPTY;

		CELSETSection *elsetSection = NULL;

		for(ListStringData::iterator itLine = lstDFEMFile->begin(); itLine != lstDFEMFile->end(); itLine++) {

			std::string strReadLine = (*itLine);
			CGlobal::GetGlobal()->Trim(strReadLine);

			if(strReadLine == STRING_EMPTY) continue;

			if(!CGlobal::StartsWithPattern(strReadLine, ELSET) && CGlobal::NumberOccurrences(strReadLine, '*') > ZERO) {
				if(bIniSectionElset && elsetSection != NULL) {
					MapELSETSections::iterator itElsetSections = m_pThis->getMapElsetSections()->begin();

					m_pThis->getMapElsetSections()->insert(itElsetSections, std::pair<std::string, CELSETSection*>(strElsetName, elsetSection));
				}

				bIniSectionElset = false;
				continue;
			}

			if (CGlobal::StartsWithPattern(strReadLine, ELSET)) {

				bIniSectionElset = true;

				strElsetName = CGlobal::GetGlobal()->GetELSETName(strReadLine, m_pThis->getDelimiter());

				elsetSection = new CELSETSection();
				elsetSection->setElsetName(strElsetName);

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
		CLogger::GetLogger()->Log(" <EXCEPTION>: CDFEMReader::LoadELSETSection " + std::string(exc.what()));
	}

	return bReturn;
}


/**
 *
 * @param lstDFEMFile
 * @return
 */
bool CDFEMReader::LoadELEMENTSection(ListStringData *lstDFEMFile) {

	bool bReturn = RESULT_KO;

	try {

		if((lstDFEMFile == NULL) ||
	       (lstDFEMFile != NULL && lstDFEMFile->size() <= 0)) return bReturn;

		std::string strReadLine = STRING_EMPTY;
		ListStringData dataList;

		bool bIniSectionElement = false;
		std::string strElementName = STRING_EMPTY;

		CELEMENTSection *elementSection = NULL;

		for(ListStringData::iterator itLine = lstDFEMFile->begin(); itLine != lstDFEMFile->end(); itLine++) {

			std::string strReadLine = (*itLine);
			CGlobal::GetGlobal()->Trim(strReadLine);

			if(strReadLine == STRING_EMPTY) continue;

			if(!CGlobal::StartsWithPattern(strReadLine, ELEMENTS) &&
			   !CGlobal::StartsWithPattern(strReadLine, ELEMENTS_LOW) &&
			   CGlobal::NumberOccurrences(strReadLine, '*') > ZERO) {

				if(bIniSectionElement && elementSection != NULL) {

					MapELEMENTSections::iterator itElementSections = m_pThis->getMapElementSections()->begin();

					MapELEMENTSections::iterator itElementFind = m_pThis->getMapElementSections()->find(strElementName);

					if(itElementFind == m_pThis->getMapElementSections()->end())
					{
						m_pThis->getMapElementSections()->insert(itElementSections, std::pair<std::string, CELEMENTSection*>(strElementName, elementSection));
					}
					else {
						(*itElementFind).second->getListNodes()->splice((*itElementFind).second->getListNodes()->end(), *elementSection->getListNodes());
					}

					cout << "strElementName: " << strElementName << endl;
				}

				bIniSectionElement = false;
				continue;
			}

			if (CGlobal::StartsWithPattern(strReadLine, ELEMENTS) ||
				CGlobal::StartsWithPattern(strReadLine, ELEMENTS_LOW)) {

				if(bIniSectionElement && strElementName != STRING_EMPTY) {

					CELEMENTSection *oSection = elementSection;
					std::string strName = strElementName;

					MapELEMENTSections::iterator itElementSections = m_pThis->getMapElementSections()->begin();
					MapELEMENTSections::iterator itElementFind = m_pThis->getMapElementSections()->find(strElementName);

					if(itElementFind == m_pThis->getMapElementSections()->end())
					{
						m_pThis->getMapElementSections()->insert(itElementSections, std::pair<std::string, CELEMENTSection*>(strElementName, elementSection));
					}
					else {
						(*itElementFind).second->getListNodes()->splice((*itElementFind).second->getListNodes()->end(), *elementSection->getListNodes());
					}
				}

				bIniSectionElement = true;
				elementSection = NULL;

				strElementName = CGlobal::GetGlobal()->GetELSETName(strReadLine, m_pThis->getDelimiter());

				elementSection = new CELEMENTSection();
				elementSection->setElementName(strElementName);

				continue;
			}

			if(bIniSectionElement && CGlobal::NumberOccurrences(strReadLine, '*') == ZERO) {

				ListStringData *lstNodeData = CGlobal::ParseDataLine(strReadLine, m_pThis->getDelimiter(), 1, true);

				if (lstNodeData->size() > 0) {

					elementSection->getListNodes()->splice(elementSection->getListNodes()->end(), *lstNodeData);
				}
			}
		}

		bReturn = RESULT_OK;
	}
	catch(std::exception &exc) {
		CLogger::GetLogger()->Log(" <EXCEPTION>: CDFEMReader::LoadELEMENTSection " + std::string(exc.what()));
	}

	return bReturn;
}

