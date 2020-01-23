/*
 * Global.cpp
 *
 *  Created on: 12 nov. 2019
 *      Author: fernando.olivares
 */


#include "../Headers/Global.h"
#include <iostream>


#include <stdarg.h> // includes va_list
#include <stddef.h>
#include <sstream> // for istringstream

#include <sys/stat.h>
#include <algorithm>
#include <fstream>
#include <iostream>
#include <iterator>
#include <string>
#include <dirent.h>
#include <cstring>
#include <cctype>


#include <bits/stdc++.h>

#include "../Headers/Logger.h"
#include "../Headers/Node.h"
#include "../Headers/Vector3D.h"
#include "../Headers/Coordinate3D.h"

//#define		PRINT_TRACES


CGlobal* CGlobal::m_pThis = NULL;

#pragma GCC diagnostic ignored "-Wunused-variable"

/**
 * Default contructor
 */
CGlobal::CGlobal() 
{
	m_OFFSET_NODE2_ID_GFEM 	= 10000000;
	m_OFFSET_NODE3_ID_GFEM 	= 20000000;

	m_SOLIDSECTION_Tie 		= ZERO;

	m_MainDFEMFile = STRING_EMPTY;
}

CGlobal::~CGlobal() {
}

/**
 * Return a CGlobal instance
 * @return: CGlobal instance
 */
CGlobal* CGlobal::GetGlobal()
{
    if (m_pThis == NULL)
    {
            m_pThis = new CGlobal();
    }
    return m_pThis;
}

/**
 * Method that return the current date time in string format
 * @return: DateTime in string format
 */ 
const std::string CGlobal::CurrentDateTime()
{
    time_t     now = time(0);
    struct tm  tstruct;
    char       buf[80];
    tstruct = *localtime(&now);
    strftime(buf, sizeof(buf), "%Y-%m-%d.%X", &tstruct);

    return buf;
}
    
/**
 * Method to compose a message with a formtar
 * @param format: Format to apply to the message
 * @param pargs: params of the message
 * @return: result of the operation
 */
const int CGlobal::_vscprintf (const char * format, va_list pargs)
{
    int retval;
    va_list argcopy;
    va_copy(argcopy, pargs);
    retval = vsnprintf(NULL, 0, format, argcopy);
    va_end(argcopy);

    return retval;
}

/**
 * Check ia a file exist.
 * @param name: name of the file
 * @return: Result of the operation: RESULT_KO or RESULT_OK
 */
bool CGlobal::FileExist(const std::string& name) {

	 bool bReturn = RESULT_KO;

	 try {

		 struct stat buffer;
		 bReturn = (stat (name.c_str(), &buffer) == 0);
	 }
	 catch(std::exception &exc) {

		 CLogger::GetLogger()->Log(" <EXCEPTION>: CGlobal::FileExist " + std::string(exc.what()));
	 }

	 return bReturn;
}

/**
 * Return the current directory where the aplication is running
 * @return
 */
std::string CGlobal::getCurrentDir() {

	std::string strPath = "";
	char cCurrentPath[FILENAME_MAX] = {0};

	try {
		if (!GetCurrentDir(cCurrentPath, sizeof(cCurrentPath))) {
			return strPath;
		}

		cCurrentPath[sizeof(cCurrentPath) - 1] = '\0'; /* not really required */
	}
	catch(std::exception &exc) {
		CLogger::GetLogger()->Log(" <EXCEPTION>: CGlobal::getCurrentDir " + std::string(exc.what()));
	}
	return cCurrentPath;
}

/**
 *
 * @param str
 * @param from
 * @param to
 * @return
 */
bool CGlobal::Replace(std::string& strSource, const std::string& toSearch, const std::string& replaceStr) {

    try {

    	size_t pos = strSource.find(toSearch);

    	// Repeat till end is reached
    	while( pos != std::string::npos)
    	{
    		// Replace this occurrence of Sub String
    		strSource.replace(pos, toSearch.size(), replaceStr);
    		// Get the next occurrence from the current position
    		pos = strSource.find(toSearch, pos + replaceStr.size());
    	}
    }
	catch(std::exception &exc) {
		return false;
		CLogger::GetLogger()->Log(" <EXCEPTION>: CGlobal::Replace " + std::string(exc.what()));
	}

    return true;
}

/**
 *
 * @param lstDataList
 * @param dPos
 * @return
 */
std::string CGlobal::GetItem(std::list<std::string>lstDataList, int dPos) {

	std::string strReturn = STRING_EMPTY;

	try {

		if ((int)lstDataList.size() > dPos)
		{
		    std::list<std::string>::iterator it = lstDataList.begin();
		    std::advance(it, dPos);
		    // 'it' points to the element at index 'N'

		    strReturn = (*it);
		}
	}
	catch(std::exception &exc) {

		CLogger::GetLogger()->Log(" <EXCEPTION>: CGlobal::GetItem " + std::string(exc.what()));
	}

	return strReturn;
}

/**
 *
 * @param str
 * @return
 */
std::string& CGlobal::Ltrim(std::string& str)
{
	try {
		auto it = std::find_if(str.begin(), str.end(),
								[](char c) {
									return !std::isspace<char>(c, std::locale::classic());
								});
		str.erase(str.begin(), it);
	}
	catch(std::exception &exc) {

		str = STRING_EMPTY;

		CLogger::GetLogger()->Log(" <EXCEPTION>: CGlobal::Ltrim " + std::string(exc.what()));
	}

	return str;
}

/**
 *
 * @param str
 * @return
 */
std::string& CGlobal::Rtrim(std::string& str)
{
	try {
		auto it = std::find_if(str.rbegin(), str.rend(),
							[](char c) {
								return !std::isspace<char>(c, std::locale::classic());
							});
		str.erase(it.base(), str.end());
	}
	catch(std::exception &exc) {

		str = STRING_EMPTY;

		CLogger::GetLogger()->Log(" <EXCEPTION>: CGlobal::Rtrim " + std::string(exc.what()));
	}

	return str;
}

/**
 *
 * @param str
 * @return
 */
std::string& CGlobal::Trim(std::string& str)
{
	return Ltrim(Rtrim(str));
}

void CGlobal::ShowListData(std::list<int> lstNodes) {

//#define PRINT_TRACES

#ifdef PRINT_TRACES
	try {
		cout << "[Node List] Size: " <<  lstNodes.size() << "   Datos: ";

		for (auto it = lstNodes.cbegin(); it != lstNodes.cend(); it++)
		{
			std::cout << m_pThis->PadLeft(std::to_string((*it)), 6, ' ') << "  ";
		}

		std::cout << endl;
	}
	catch(std::exception &exc) {
		CLogger::GetLogger()->Log(" <EXCEPTION>: CGlobal::ShowListData (int) " + std::string(exc.what()));
	}
#endif
}

void CGlobal::ShowListData(ListStringData lstNodes) {

#define PRINT_TRACES

#ifdef PRINT_TRACES

	try {
		cout << "[Node List] Size: " <<  lstNodes.size() << endl;
		for (auto it = lstNodes.cbegin(); it != lstNodes.cend(); it++)
		{
			std::cout << "\t " << (*it) << endl;
		}

		std::cout << endl;
	}
	catch(std::exception &exc) {
		CLogger::GetLogger()->Log(" <EXCEPTION>: CGlobal::ShowListData (string) " + std::string(exc.what()));
	}

#endif
}

/**
 *
 * @param lstGFEMNodes
 */
void CGlobal::ShowListData(ListGFEMNodes *lstGFEMNodes) {

#ifdef PRINT_TRACES
	int dSize = lstGFEMNodes->size();

	try {
		cout << "[GFEMNodes] Size: " <<  lstGFEMNodes->size();
		for (auto it = lstGFEMNodes->cbegin(); it != lstGFEMNodes->cend(); it++)
		{
			std::cout << "Node: " << (*it)->getName() << "  ";
		}

		std::cout << endl;
	}
	catch(std::exception &exc) {
		CLogger::GetLogger()->Log(" <EXCEPTION>: CGlobal::ShowListData " + std::string(exc.what()));
	}
#endif
}

/**
 *
 * @param lstDFEMNodes
 */
void CGlobal::ShowListData(ListDFEMNodes *lstDFEMNodes) {

#ifdef PRINT_TRACES
	try {
		cout << "[DFEMNodes] Size: " <<  lstDFEMNodes->size() << "   Datos: ";
		for (auto it = lstDFEMNodes->cbegin(); it != lstDFEMNodes->cend(); it++)
		{
			std::cout << (*it)->getName() << "  ";
		}

		std::cout << endl;
	}
	catch(std::exception & exc) {
		CLogger::GetLogger()->Log(" <EXCEPTION>: CGlobal::ShowListData " + std::string(exc.what()));
	}
#endif
}

/**
 *
 * @param lstDFEMNodes
 * @return
 */
bool CGlobal::IsNumber(const std::string& str){

	istringstream iss( str.c_str() );

	double dTestSink;
	iss >> dTestSink;

	// was any input successfully consumed/converted?
	if ( ! iss )
		return false;

	// was all the input successfully consumed/converted?
	return ( iss.rdbuf()->in_avail() == 0 );
}



/**
 *
 * @param str
 * @param dSize
 * @param paddingChar
 * @return
 */
std::string CGlobal::PadRight(std::string const& str, size_t dSize, const char paddingChar)
{
    try {
    	if ( str.size() < dSize )
            return str + std::string(dSize-str.size(), paddingChar);
        else
            return str;
    }
    catch(std::exception &exc) {
    	CLogger::GetLogger()->Log(" <EXCEPTION>: CGlobal::PadRight " + std::string(exc.what()));

    	return STRING_EMPTY;

    }
}

/**
 *
 * @param str
 * @param dSize
 * @param paddingChar
 * @return
 */
std::string CGlobal::PadLeft(std::string const& str, size_t dSize, const char paddingChar)
{
    try {
    	if ( str.size() < dSize )
            return std::string(dSize-str.size(), paddingChar) + str;
        else
            return str;

    }
    catch(std::exception &exc) {
    	CLogger::GetLogger()->Log(" <EXCEPTION>: CGlobal::PadLeft " + std::string(exc.what()));

    	return STRING_EMPTY;
    }
}

/**
 *
 * @param dType
 * @param sNode
 * @return
 */
int CGlobal::GetNodeType(int dType, std::string sNode) {

	int dReturn = UNDEFINED;

	switch(dType)
	{
		case TYPE_1D2D:
			if(sNode == "D")
				dReturn = TYPE_DFEM_1D;
			else
				dReturn = TYPE_GFEM_1D;
			break;
		default:
			if(sNode == "D")
				dReturn = TYPE_DFEM_2D;
			else
				dReturn = TYPE_GFEM_2D;
			break;
	}

	return dReturn;
}


/**
 *
 * @param lstSource
 * @param dPosition
 * @return
 */
int	CGlobal::GetItemAtPosition( std::list<int> lstSource, int dPosition) {

	int dReturn = ZERO;

	try {

		if((int)lstSource.size() > dPosition) {
			std::list<int>::iterator it = lstSource.begin();
			std::advance(it, dPosition);

			dReturn = (*it);
		}
	}
	catch(std::exception &exc) {
		CLogger::GetLogger()->Log(" <EXCEPTION>: CGlobal::GetItemAtPosition " + std::string(exc.what()));
	}

	return dReturn;
}

/**
 *
 * @param lstSource
 * @param dPosition
 * @return
 */
std::string	CGlobal::GetItemAtPosition( std::list<std::string> lstSource, int dPosition) {

	std::string strReturn = STRING_EMPTY;

	try {

		if((int)lstSource.size() > dPosition) {
			std::list<std::string>::iterator it = lstSource.begin();
			std::advance(it, dPosition);

			strReturn = (*it);
		}

	}
	catch(std::exception &exc) {
		CLogger::GetLogger()->Log(" <EXCEPTION>: CGlobal::GetItemAtPosition " + std::string(exc.what()));
	}

	return strReturn;
}

/**
 *
 * @param strSource
 * @param strChar
 * @return
 */
bool	CGlobal::StartsWithPattern(std::string strSource, std::string strPattern) {

	bool bReturn = false;

	try {

		if (strSource.find(strPattern) == 0)
		{
			bReturn = true;

			return bReturn;
		}

		std::string strFind = strPattern;
		m_pThis->ToLower(strFind);

		if (strSource.find(strFind) == 0)
		{
			bReturn = true;
			return bReturn;
		}

		m_pThis->ToUpper(strFind);
		if (strSource.find(strFind) == 0)
		{
			bReturn = true;
			return bReturn;
		}
	}
	catch(std::exception &exc) {

		bReturn = false;
		CLogger::GetLogger()->Log(" <EXCEPTION>: CGlobal::StartsWithPattern " + std::string(exc.what()));
	}

	return bReturn;
}

/**
 *
 * @param strSource
 * @param chFind
 * @return
 */
int CGlobal::NumberOccurrences(std::string strSource, char chFind) {

	int dReturn = 0;

	try {
		dReturn = std::count(strSource.begin(), strSource.end(), chFind);
	}
	catch(std::exception &exc) {

		CLogger::GetLogger()->Log(" <EXCEPTION>: CGlobal::NumberOccurrecnces " + std::string(exc.what()));
	}

	return dReturn;
}

/**
 *
 * @param strGridLine
 * @param dFieldSize
 * @return
 */
ListStringData CGlobal::ParseDataLine(std::string strGridLine, int dFieldSize, std::string strPattern) {

	std::list<std::string> lstReturn;

	int dBegin = 0;
	int dEnd = 0;

	try {

		while((int)strGridLine.length() >= (dBegin + dFieldSize)) {

			std::string strPart = strGridLine.substr(dBegin, dFieldSize);
			strGridLine.erase(dBegin, dFieldSize);


			if(CGlobal::Trim(strPart) == strPattern) continue;

			lstReturn.push_back(strPart);

		}
	}
	catch(std::exception &exc) {
		CLogger::GetLogger()->Log(" <EXCEPTION>: CGFEMReader::ParseDataLine " + std::string(exc.what()));
	}

	return lstReturn;

}

/**
 *
 * @param strGridLine
 * @param dFieldSize
 * @return
 */
ListStringData CGlobal::ParseDataLine(std::string strDataLine, std::string strDelimiter) {

	std::list<std::string> lstReturn;

	try {

		size_t pos = 0;

		while ((pos = strDataLine.find(strDelimiter)) != std::string::npos) {

			std::string strTok = strDataLine.substr(0, pos);
			CGlobal::Trim(strTok);

			if(strTok != STRING_EMPTY && CGlobal::IsNumber(strTok)) {
				lstReturn.push_back(strTok);
			}

			strDataLine.erase(0, pos + strDelimiter.length());
		}

		CGlobal::Trim(strDataLine);

		if(!strDataLine.empty() && CGlobal::IsNumber(strDataLine)) {
			lstReturn.push_back(strDataLine);
		}
	}
	catch(std::exception &exc) {
		CLogger::GetLogger()->Log(" <EXCEPTION>: CGlobal::ParseDataLine " + std::string(exc.what()));
	}

	return lstReturn;
}

/**
 *
 * @param strGridLine
 * @param dFieldSize
 * @return
 */
ListStringData CGlobal::ParseDataLine(std::string strDataLine, std::string strDelimiter, bool bCheckIsNumber) {

	std::list<std::string> lstReturn;

	try {

		size_t pos = 0;

		while ((pos = strDataLine.find(strDelimiter)) != std::string::npos) {

			std::string strTok = strDataLine.substr(0, pos);
			CGlobal::Trim(strTok);

			if(bCheckIsNumber) {
				if(strTok != STRING_EMPTY && CGlobal::IsNumber(strTok)) {

					lstReturn.push_back(strTok);
				}
			}
			else {
				if(!strTok.empty()) {
					lstReturn.push_back(strTok);
				}
			}

			strDataLine.erase(0, pos + strDelimiter.length());
		}

		CGlobal::Trim(strDataLine);

		if(bCheckIsNumber) {
			if(!strDataLine.empty() && CGlobal::IsNumber(strDataLine)) {
				lstReturn.push_back(strDataLine);
			}

		}
		else {
			if(!strDataLine.empty()) {
				lstReturn.push_back(strDataLine);
			}
		}
	}
	catch(std::exception &exc) {
		CLogger::GetLogger()->Log(" <EXCEPTION>: CGlobal::ParseDataLine " + std::string(exc.what()));
	}

	return lstReturn;
}

/**
 *
 * @param strGridLine
 * @param dFieldSize
 * @return
 */
ListStringData CGlobal::ParseDataLineStrings(std::string strDataLine, std::string strDelimiter) {

	std::list<std::string> lstReturn;

	try {

		size_t pos = 0;

		while ((pos = strDataLine.find(strDelimiter)) != std::string::npos) {

			std::string strTok = strDataLine.substr(0, pos);
			CGlobal::Trim(strTok);

			if(strTok != STRING_EMPTY) {
				lstReturn.push_back(strTok);
			}

			strDataLine.erase(0, pos + strDelimiter.length());
		}

		CGlobal::Trim(strDataLine);

		if(!strDataLine.empty()) {
			lstReturn.push_back(strDataLine);
		}
	}
	catch(std::exception &exc) {
		CLogger::GetLogger()->Log(" <EXCEPTION>: CGlobal::ParseDataLineStrings " + std::string(exc.what()));
	}

	return lstReturn;
}

/**
 *
 * @param strGridLine
 * @param dFieldSize
 * @param NElements
 * @return
 */
std::list<std::string> * CGlobal::ParseDataLine(std::string strDataLine, std::string strDelimiter, long NElements, bool NOZERO) {

	std::list<std::string> *lstReturn = new std::list<std::string>();
	int nElementsAdded = 0;

	try {

		size_t pos = 0;

		while ((pos = strDataLine.find(strDelimiter)) != std::string::npos && nElementsAdded < NElements) {

			CGlobal::Trim(strDataLine);

			std::string strTok = strDataLine.substr(0, pos);

			if(strTok == STRING_EMPTY) {
				strDataLine.erase(0, pos + strDelimiter.length());
				continue;
			}

			CGlobal::Trim(strTok);

			if(NOZERO && strTok == STRING_EMPTY) continue;

			if(strTok == STRING_EMPTY) {
				strTok = SZERO;
			}

			if(strTok != STRING_EMPTY) {

				lstReturn->push_back(strTok);
				nElementsAdded++;
			}

			strDataLine.erase(0, pos + strDelimiter.length());
		}

		if(nElementsAdded < NElements) {
			CGlobal::Trim(strDataLine);

			if(NOZERO == false && strDataLine == STRING_EMPTY) {
				strDataLine = SZERO;

				if(!strDataLine.empty()) {

					lstReturn->push_back(strDataLine);
				}
			}

		}
	}
	catch(std::exception &exc) {
		CLogger::GetLogger()->Log(" <EXCEPTION>: CGlobal::ParseDataLineToInt " + std::string(exc.what()));
	}

	return lstReturn;
}

/**
 *
 * @param strGridLine
 * @param dFieldSize
 * @param NElements
 * @return
 */
std::list<int> * CGlobal::ParseDataLineToInt(std::string strDataLine, std::string strDelimiter, long NElements, bool NOZERO) {

	std::list<int> *lstReturn = new std::list<int>();
	int nElementsAdded = 0;

	try {

		size_t pos = 0;

		while ((pos = strDataLine.find(strDelimiter)) != std::string::npos && nElementsAdded < NElements) {

			std::string strTok = strDataLine.substr(0, pos);
			CGlobal::Trim(strTok);

			if(NOZERO && strTok == STRING_EMPTY) continue;

			if(strTok == STRING_EMPTY) {
				strTok = SZERO;
			}

			if(strTok != STRING_EMPTY && CGlobal::IsNumber(strTok)) {

				lstReturn->push_back(std::stoi(strTok));
				nElementsAdded++;
			}

			strDataLine.erase(0, pos + strDelimiter.length());
		}

		if(nElementsAdded < NElements) {
			CGlobal::Trim(strDataLine);

			if(NOZERO == false && strDataLine == STRING_EMPTY) {
				strDataLine = SZERO;

				if(!strDataLine.empty() && CGlobal::IsNumber(strDataLine)) {

					lstReturn->push_back(std::stoi(strDataLine));
				}
			}

		}
	}
	catch(std::exception &exc) {
		CLogger::GetLogger()->Log(" <EXCEPTION>: CGlobal::ParseDataLineToInt " + std::string(exc.what()));
	}

	return lstReturn;
}


/**
 *
 * @param strGridLine
 * @param dFieldSize
 * @param NElements
 * @param EmptyIsZERO
 * @return
 */
ListStringData * CGlobal::ParseDataLine(std::string strDataLine, std::string strDelimiter, int NElements) {

	ListStringData *lstReturn = new ListStringData();
	int nElementsAdded = 0;

	try {

		size_t pos = 0;

		while ((pos = strDataLine.find(strDelimiter)) != std::string::npos && nElementsAdded < NElements) {

			std::string strTok = strDataLine.substr(0, pos);
			CGlobal::Trim(strTok);

			if(strTok == STRING_EMPTY) {
				strTok = SZERO;
			}

			if(strTok != STRING_EMPTY && CGlobal::IsNumber(strTok)) {

				lstReturn->push_back(strTok);
				nElementsAdded++;
			}

			strDataLine.erase(0, pos + strDelimiter.length());
		}

		if(nElementsAdded < NElements) {
			CGlobal::Trim(strDataLine);

			if(strDataLine == STRING_EMPTY) {
				strDataLine = SZERO;
			}

			if(!strDataLine.empty() && CGlobal::IsNumber(strDataLine)) {

				lstReturn->push_back(strDataLine);
			}
		}

	}
	catch(std::exception &exc) {
		CLogger::GetLogger()->Log(" <EXCEPTION>: CGlobal::ParseDataLine " + std::string(exc.what()));
	}

	return lstReturn;
}

/**
 *
 * @param strGridLine
 * @param dFieldSize
 * @param NElements
 * @param EmptyIsZERO
 * @return
 */
ListStringData * CGlobal::ParseDataLineNotNumber(std::string strDataLine, std::string strDelimiter, int NElements) {

	ListStringData *lstReturn = new ListStringData();
	int nElementsAdded = 0;

	try {

		size_t pos = 0;

		while ((pos = strDataLine.find(strDelimiter)) != std::string::npos && nElementsAdded < NElements) {

			std::string strTok = strDataLine.substr(0, pos);
			CGlobal::Trim(strTok);

			if(strTok == STRING_EMPTY) {
				strTok = SZERO;
			}

			if(strTok != STRING_EMPTY) {

				lstReturn->push_back(strTok);
				nElementsAdded++;
			}

			strDataLine.erase(0, pos + strDelimiter.length());
		}

		if(nElementsAdded < NElements) {
			CGlobal::Trim(strDataLine);

			if(strDataLine == STRING_EMPTY) {
				strDataLine = SZERO;
			}

			if(!strDataLine.empty() ) {

				lstReturn->push_back(strDataLine);
			}
		}

	}
	catch(std::exception &exc) {
		CLogger::GetLogger()->Log(" <EXCEPTION>: CGlobal::ParseDataLineNotNumber " + std::string(exc.what()));
	}

	return lstReturn;
}

/**
 *
 * @param dIdGFEM
 * @param *mapCQUAD4
 * @return
 */
CCQUAD4Node * CGlobal::FindAssociatedNodeToGFEM(int dIdGFEM, MapCQUAD4Data *mapCQUAD4, std::list<int> lstExcluded) {

	CCQUAD4Node *nodeReturn = NULL;

	try {
		//CGlobal::ShowListData(lstExcluded);

		for (MapCQUAD4Data::iterator itMap = mapCQUAD4->begin(); itMap != mapCQUAD4->end(); itMap++)
		{
			CCQUAD4Node *oNode = (*itMap).second;

			bool bProcessed = NodeInList(oNode->getEID(), lstExcluded);

			if(!bProcessed) {
				bool bResult = 	((oNode->getG1() == dIdGFEM) ||
								 (oNode->getG2() == dIdGFEM) ||
								 (oNode->getG3() == dIdGFEM) ||
								 (oNode->getG4() == dIdGFEM));

				if(bResult) {
					nodeReturn = oNode;
					break;
				}
			}
		}
	}
	catch(std::exception &exc) {
		CLogger::GetLogger()->Log(" <EXCEPTION>: CGlobal::FindAssociatedNodeToGFEM(CQUAD4) -> " + std::string(exc.what()));
	}

	return nodeReturn;
}

/**
 *
 * @param dIdGFEM
 * @param *mapCTRIA3
 * @return
 */
CCTRIA3Node* CGlobal::FindAssociatedNodeToGFEM(int dIdGFEM, MapCTRIA3Data *mapCTRIA3, std::list<int> lstExcluded) {

	CCTRIA3Node *nodeReturn = NULL;

	CGlobal::ShowListData(lstExcluded);

	try {

		for (MapCTRIA3Data::iterator itMap = mapCTRIA3->begin(); itMap != mapCTRIA3->end(); itMap++)
		{
			CCTRIA3Node *oNode = (*itMap).second;

			bool bProcessed = NodeInList(oNode->getEID(), lstExcluded);

			if(!bProcessed) {
				bool bResult = 	((oNode->getG1() == dIdGFEM) ||
								 (oNode->getG2() == dIdGFEM) ||
								 (oNode->getG3() == dIdGFEM));

				if(bResult) {
					nodeReturn = oNode;
					break;
				}
			}
		}
	}
	catch(std::exception &exc) {
		CLogger::GetLogger()->Log(" <EXCEPTION>: CGlobal::FindAssociatedNodeToGFEM(CTRIA3) -> " + std::string(exc.what()));
	}

	return nodeReturn;
}

/**
 *
 * @param dIdNode
 * @param *lstSource
 * @return
 */
bool CGlobal::NodeInList(int dIdNode, ListIntegerData lstSource) {

	bool bReturn = false;

	if(lstSource.size() > 0) {

		bReturn = (std::find(lstSource.begin(), lstSource.end(), dIdNode) != lstSource.end());
	}

	return bReturn;
}

/**
 *
 * @param dIdNode
 * @param *lstSource
 * @return
 */
bool CGlobal::NodeInList(std::string IdNode, ListStringData lstSource) {

	bool bReturn = false;

	if(lstSource.size() > 0) {
		bReturn = (std::find(lstSource.begin(), lstSource.end(), IdNode) != lstSource.end());
	}

	return bReturn;
}

/**
 *	Show a map data into the console. For debug utility
 * @param oMap
 */
void CGlobal::ShowMap(MapDFEMObjects *oMap) {

#ifdef PRINT_TRACES
	std::map<std::string, CDFEMObject *>::iterator it;

	try {
		for ( it = oMap->begin(); it != oMap->end(); it++ )
		{
		    std::cout << it->first  << std::endl ;
		}
	}
	catch(std::exception &exc) {
		CLogger::GetLogger()->Log(" <EXCEPTION>: CGlobal::ShowMap " + std::string(exc.what()));

	}
#endif
}


/**
 *
 * @param strMessage
 * @param *oGFEMNode
 * @param *oNode
 * @return
 */
void CGlobal::ShowGridNode(std::string strMessage, CGFEMNode *oGFEMNode, CGridNode *oNode) {

#ifdef PRINT_TRACES
	cout << strMessage
		 << oGFEMNode->getG1_1()
	     << " :: CP: "  		<< oNode->getCP()
		 << " :: X1: " 		<< oNode->getCoord_X1()
		 << " :: X2: " 		<< oNode->getCoord_X2()
		 << " :: X3: " 		<< oNode->getCoord_X3() << endl;
#endif
}

/**
 *
 * @param strMessage
 * @param *oVector
 * @return
 */
void CGlobal::ShowVector3D(std::string strMessage, CVector3D *oVector) {

#ifdef PRINT_TRACES
	cout << strMessage
		 << " :: CP: " << oVector->getCP()
		 << " :: X1: " << oVector->getV_X1()
		 << " :: X2: " << oVector->getV_X2()
		 << " :: X3: " << oVector->getV_X3() << endl;
#endif
}

/**
 * Method to show an CGFEmNode fields and values
 * @param strMessage: Header of the message to show.
 * @param *oNode: Object to show in the console window
  */
void CGlobal::ShowNodeData(std::string strMessage, CGFEMNode *oNode) {

#define PRINT_TRACES

#ifdef PRINT_TRACES
	cout << strMessage 																		<< endl
		 << " Id. Node:   "						<< oNode->getIdNode() 						<< endl
		 << " EID-1: 	  " 					<< oNode->getEid_1()  						<< endl
		 << " ZOFFS 1: 	  "						<< oNode->getZOFFS_1() 						<< endl
		 << " G1.1: 	  " 					<< oNode->getG1_1() 						<< endl
		 << " G2.1: 	  "						<< oNode->getG2_1() 						<< endl
		 << " G3.1: 	  " 					<< oNode->getG3_1() 						<< endl
		 << " G4.1: 	  "						<< oNode->getG4_1() 						<< endl
		 << " EID 2: 	  " 					<< oNode->getEid_2() 						<< endl
		 << " ZOFFS 2: 	  "						<< oNode->getZOFFS_2() 						<< endl
		 << " G1.2: 	  " 					<< oNode->getG1_2() 						<< endl
		 << " G2.2: 	  "						<< oNode->getG2_2() 						<< endl
		 << " G3.2: 	  " 					<< oNode->getG3_2()  						<< endl
		 << " G4.2: 	  "						<< oNode->getG4_2() 						<< endl
		 << " ZOFFS: 	  " 					<< oNode->getZOFFS() 						<< endl
		 << " G1.1 CP:	  "						<< oNode->getG1_1_CP()						<< endl
		 << " G1.1 X1: 	  " 					<< oNode->getG1_1_X1()						<< endl
		 << " G1.1 X2: 	  "						<< oNode->getG1_1_X2()						<< endl
		 << " G1.1 X3: 	  " 					<< oNode->getG1_1_X3()						<< endl
		 << " G2.1 CP:    "						<< oNode->getG2_1_CP()						<< endl
		 << " G2.1 X1: 	  " 					<< oNode->getG2_1_X1()						<< endl
		 << " G2.1 X2: 	  "						<< oNode->getG2_1_X2()						<< endl
		 << " G2.1 X3: 	  " 					<< oNode->getG2_1_X3()						<< endl
		 << " G3.1 CP:    "						<< oNode->getG3_1_CP()						<< endl
		 << " G3.1 X1: 	  "						<< oNode->getG3_1_X1()						<< endl
		 << " G3.1 X2: 	  "						<< oNode->getG3_1_X2()						<< endl
		 << " G3.1 X3: 	  " 					<< oNode->getG3_1_X3()						<< endl
		 << " G1.2 CP:    "						<< oNode->getG1_2_CP()						<< endl
		 << " G1.2 X1: 	  " 					<< oNode->getG1_2_X1()						<< endl
		 << " G1.2 X2: 	  "						<< oNode->getG1_2_X2()						<< endl
		 << " G1.2 X3: 	  " 					<< oNode->getG1_2_X3()						<< endl
		 << " G2.2 CP:    "						<< oNode->getG2_2_CP()						<< endl
		 << " G2.2 X1: 	  " 					<< oNode->getG2_2_X1()						<< endl
		 << " G2.2 X2: 	  "						<< oNode->getG2_2_X2()						<< endl
		 << " G2.2 X3: 	  "						<< oNode->getG2_2_X3()						<< endl
		 << " G3.2 CP :   " 					<< oNode->getG3_2_CP()						<< endl
		 << " G3.2 X1: 	  " 					<< oNode->getG3_2_X1()						<< endl
		 << " G3.2 X2: 	  "						<< oNode->getG3_2_X2()						<< endl
		 << " G3.2 X3:    "						<< oNode->getG3_2_X3()   					<< endl
		 << " V3 X1 NORM: " 					<< oNode->getV3_X1_Norm()					<< endl
		 << " V3 X2 NORM: " 					<< oNode->getV3_X2_Norm()					<< endl
		 << " V3 X3 NORM: " 					<< oNode->getV3_X3_Norm() 					<< endl
		 << " NODE 2 ID:  " 					<< oNode->getNode_2_ID() 					<< endl
		 << " NODE 2 CP:  " 					<< oNode->getNode_2_CP() 					<< endl
		 << " NODE 2 X1:  " 					<< oNode->getNode_2_X1() 					<< endl
		 << " NODE 2 X2:  " 					<< oNode->getNode_2_X2() 					<< endl
		 << " NODE 2 X3:  " 					<< oNode->getNode_2_X3() 					<< endl
		 << " NODE 2 CD:  " 					<< oNode->getNode_2_CD() 					<< endl
		 << " X0:  		  " 					<< oNode->getX0() 							<< endl
		 << " Y0:  		  " 					<< oNode->getY0() 							<< endl
		 << " Z0:  		  " 					<< oNode->getZ0() 							<< endl
		 << " D:  		  " 					<< oNode->getD() 							<< endl
		 << " NODE 3 ID:  " 					<< oNode->getNode_3_ID() 					<< endl
		 << " NODE 3 CP:  " 					<< oNode->getNode_3_CP() 					<< endl
		 << " NODE 3 X1:  " 					<< oNode->getNode_3_X1() 					<< endl
		 << " NODE 3 X2:  " 					<< oNode->getNode_3_X2() 					<< endl
		 << " NODE 3 X3:  " 					<< oNode->getNode_3_X3() 					<< endl
		 << " NODE 3 CD:  " 					<< oNode->getNode_3_CD() 					<< endl
		 << " NODE_1_CARD: " 					<< oNode->getNODE_1_CARD() 					<< endl
		 << " NODE_2_CARD: " 					<< oNode->getNODE_2_CARD() 					<< endl
		 << " KINEMATIC COUPLING 1-2 CARD: \n" 	<< oNode->getKINEMATIC_COUPLING_1_2_CARD() 	<< endl
		 << " NODE_3_CARD: " 					<< oNode->getNODE_3_CARD() 					<< endl
		 << " EQUATION CARD: " 					<< oNode->getEQUATION_CARD() 				<< endl;

#endif

}


/**
 * Function to return the distance between two 3D points passed as parameter
 * @param coord1: Coordinate 1 value
 * @param coord2: Coordinate 2 value
 * @return: The distance calculated between the two coordinates passed as parameter
 */
float CGlobal::GetDistance(CCoordinate3D *coord1, CCoordinate3D *coord2) {
    float dResult = sqrt(pow(coord2->getX() - coord1->getX(), 2) +
                		 pow(coord2->getY() - coord1->getY(), 2) +
						 pow(coord2->getZ() - coord1->getZ(), 2)) ;

    return dResult;
}

/**
 * Function to return the distance between two 3D points passed as parameter
 * @param coord1: Coordinate 1 value
 * @param coord2: Coordinate 2 value*
 * @return: The string result by the lines concatenation
 */
bool CGlobal::AdjacentPoitns(CCoordinate3D *coord1, CCoordinate3D *coord2) {

	double diff = abs(coord1->getX() - coord2->getX()) +
		   abs(coord1->getY() - coord2->getY()) +
		   abs(coord1->getZ() - coord2->getZ());

	return (diff == 1);
}

/**
 * Function to return the distance between two 3D points passed as parameter
 * @return: The string result by the lines concatenation
 */
std::string CGlobal::LoadT3D2ElementBetweenGFEMProjectedNodes() {

	std::string strT2D3Composed = STRING_EMPTY;


	try {
		int nLines = std::stoi(m_pThis->getIniFile().get("T3D2_BETWEEN_GFEM_PROJECTED_NODES").get("n_lines"));

		for(int dNLine = 0; dNLine < nLines; dNLine++) {

			std::string strLineReaded = m_pThis->getIniFile().get("T3D2_BETWEEN_GFEM_PROJECTED_NODES").get("Line_" + std::to_string(dNLine));

			if(dNLine == (nLines-1)) {
				strT2D3Composed = strT2D3Composed + strLineReaded;
			}
			else {
				strT2D3Composed = strT2D3Composed + strLineReaded + "\n";
			}
		}
	}
	catch(std::exception &exc) {
		strT2D3Composed = STRING_EMPTY;

		CLogger::GetLogger()->Log(" <EXCEPTION>: CGlobal::LoadT3D2ElementBetweenGFEMProjectedNodes " + std::string(exc.what()));
	}

	return strT2D3Composed;

}


/**
 * Function to return the distance between two 3D points passed as parameter
 * @param: dTie
 * @return: The string result by the lines concatenation
 */
std::string CGlobal::Create_SOLIDSECTION_Card(int dTieValue) {

	std::string strSOLIDSECTIONComposed = STRING_EMPTY;
	std::string strLineReaded = STRING_EMPTY;
	std::string strLine_1 = STRING_EMPTY;

	try {

		strLineReaded = m_pThis->getIniFile().get("SOLID_SECTION_CARD").get("line_0");
		strLine_1 = m_pThis->getIniFile().get("SOLID_SECTION_CARD").get("line_1");

		m_pThis->Replace(strLineReaded, "%TIE%", std::to_string(dTieValue));

		strSOLIDSECTIONComposed = strLineReaded + "\n" + strLine_1;
	}
	catch(std::exception &exc) {
		strSOLIDSECTIONComposed = STRING_EMPTY;

		CLogger::GetLogger()->Log(" <EXCEPTION>: CGlobal::Create_SOLIDSECTION_Card " + std::string(exc.what()));
	}

	return strSOLIDSECTIONComposed;
}

/**
 * Function to load OFFSET for NODE2 and NODE3
  * @return: void
 */
void CGlobal::LoadOFFSETNODE2_NODE3() {

	long lOFFSET_NODE2 = ZERO;
	long lOFFSET_NODE3 = ZERO;

	try {

		lOFFSET_NODE2 = std::stol(m_pThis->getIniFile().get("GFEM_PARSER").get("offset_id_node2"));
		m_pThis->setOFFSET_NODE2_ID_GFEM(lOFFSET_NODE2);

		lOFFSET_NODE3 = std::stol(m_pThis->getIniFile().get("GFEM_PARSER").get("offset_id_node3"));
		m_pThis->setOFFSET_NODE3_ID_GFEM(lOFFSET_NODE3);
	}
	catch(std::exception &exc) {

		lOFFSET_NODE2 = ZERO;
		lOFFSET_NODE3 = ZERO;

		CLogger::GetLogger()->Log(" <EXCEPTION>: CGlobal::GetOFFSETNODE2_NODE3 " + std::string(exc.what()));
	}
}

/**
 * Function to swap two values
 * @param: dValueA
 * @param: dValueB
 * @return: void
 */
void CGlobal::Swap(int &dValueA, int &dValueB) {
	int dAuxValue;

	if(dValueB < dValueA) {
		dAuxValue = dValueA;
		dValueA = dValueB;
		dValueB = dAuxValue;
	}
}

/**
 * Function to check if a pair node exist in a list of pair's nodes
 * @param: lstPairs
 * @param: oPairNode
 * @return: result of the operation
 */
bool CGlobal::ExistInList(ListPairNodes *lstPairs, PairNodes *oPairNode) {
	bool bReturn = RESULT_KO;

	try {
		for (list<PairNodes *>::iterator it=lstPairs->begin(); it != lstPairs->end(); it++)  {
			PairNodes *obj= *it;

			if(((*it)->first == oPairNode->first) && ((*it)->second == oPairNode->second)) {
				bReturn = true;
				break;
			}
		}
	}
	catch(std::exception &exc) {
		bReturn = RESULT_KO;
		CLogger::GetLogger()->Log(" <EXCEPTION>: CGlobal::ExistInList " + std::string(exc.what()));
	}

	return bReturn;
}

/**
 * Function to free memory used
 * @param: lstToFree
 */
void CGlobal::FreeMemory(ListPairNodes *lstToFree) {
	for (list<PairNodes *>::iterator it=lstToFree->begin(); it != lstToFree->end(); it++)  {
		PairNodes *obj= *it;
		delete obj;              //error
		it = lstToFree->erase(it);
	}
}

/**
 * Function to return the distance between two 3D points passed as parameter
 * @param: dTie
 * @return: The string result by the lines concatenation
 */
std::string CGlobal::Create_Surface_T3D2(int dTieValue) {

	std::string strReturn = STRING_EMPTY;
	std::string strLineReaded = STRING_EMPTY;
	std::string strLine_1 = STRING_EMPTY;


	try {

		strLineReaded = m_pThis->getIniFile().get("SURFACE_T3D2_CARD").get("line_0");
		strLine_1 = m_pThis->getIniFile().get("SURFACE_T3D2_CARD").get("line_1");

		m_pThis->Replace(strLineReaded, "%TIE%", std::to_string(dTieValue));
		m_pThis->Replace(strLine_1, "%TIE%", std::to_string(dTieValue));

		strReturn = strLineReaded + "\n" + strLine_1;
	}
	catch(std::exception &exc) {
		strReturn = STRING_EMPTY;

		CLogger::GetLogger()->Log(" <EXCEPTION>: CGlobal::Create_Surface_T3D2 " + std::string(exc.what()));
	}

	return strReturn;
}

/**
 * Function to return the distance between two 3D points passed as parameter
 * @param: dTie
 * @return: The string result by the lines concatenation
 */
std::string CGlobal::Create_Surface_DFEM_Nodes(CConnection *oConnection) {

	std::string strReturn = STRING_EMPTY;
	std::string strLineReaded = STRING_EMPTY;

	try {

		strLineReaded = "\n" + m_pThis->getIniFile().get("SURFACE_DFEM_CARD").get("line_0");

		m_pThis->Replace(strLineReaded, "%TIE%", std::to_string(oConnection->getTieArea()));
		strReturn = strLineReaded + "\n";

		MapDFEMNodes *mapDFEMNodes = oConnection->GetDFEMNodes();
		int nNodesAdded = 0;

		for(MapDFEMNodes::iterator itDFEM = oConnection->GetDFEMNodes()->begin(); itDFEM != oConnection->GetDFEMNodes()->end(); ++itDFEM) {

			nNodesAdded++;
			strReturn += std::to_string((*itDFEM).second->getIdNode()) + ",";

			if(nNodesAdded >= 6) {
				strReturn += "\n";
				nNodesAdded = 0;
			}
		}
	}
	catch(std::exception &exc) {
		strReturn = STRING_EMPTY;

		CLogger::GetLogger()->Log(" <EXCEPTION>: CGlobal::Create_Surface_DFEM_Nodes " + std::string(exc.what()));
	}

	return strReturn;
}

/**
 * Function to return the
 * @param: dTie
 * @return: The string result by the lines concatenation
 */
std::string CGlobal::Create_Surface_NSET(CConnection *oConnection) {

	std::string strReturn = STRING_EMPTY;
	std::string strLineReaded = STRING_EMPTY;
	std::string strLine_1 = STRING_EMPTY;

	try {

		strLineReaded = m_pThis->getIniFile().get("SURFACE_NSET_CARD").get("line_0");
		strLine_1 = m_pThis->getIniFile().get("SURFACE_NSET_CARD").get("line_1");

		m_pThis->Replace(strLineReaded, "%TIE%", std::to_string(oConnection->getTieArea()));
		m_pThis->Replace(strLine_1, "%TIE%", std::to_string(oConnection->getTieArea()));

		strReturn = strLineReaded + "\n" + strLine_1;
	}
	catch(std::exception &exc) {
		strReturn = STRING_EMPTY;

		CLogger::GetLogger()->Log(" <EXCEPTION>: CGlobal::Create_Surface_NSET " + std::string(exc.what()));
	}

	return strReturn;
}

/**
 * Function to return the TIE string data associated to a GFEM Node
 * @param: oConnection: Connection to process
 * @return: The string result by the lines concatenation
 */
std::string CGlobal::Create_TIE(CConnection *oConnection) {

	std::string strReturn = STRING_EMPTY;
	std::string strLineReaded = STRING_EMPTY;
	std::string strLine_1 = STRING_EMPTY;

	try {

		strLineReaded = m_pThis->getIniFile().get("TIE_CARD").get("line_0");
		strLine_1 = m_pThis->getIniFile().get("TIE_CARD").get("line_1");

		m_pThis->Replace(strLineReaded, "%TIE%", std::to_string(oConnection->getTieArea()));
		m_pThis->Replace(strLine_1, "%TIE%", std::to_string(oConnection->getTieArea()));

		strReturn = strLineReaded + "\n" + strLine_1;
	}
	catch(std::exception &exc) {
		strReturn = STRING_EMPTY;

		CLogger::GetLogger()->Log(" <EXCEPTION>: CGlobal::Create_TIE " + std::string(exc.what()));
	}

	return strReturn;
}

/**
 * Function to a text file and store the result in a List of lines
 * @param: strPathFile: Parh where the file is located
 * @return: std:list with the lines of the text file.
 */
ListStringData * CGlobal::ReadFile(std::string strPathFile, bool WithComments) {

	ListStringData *lstLinesReturn = NULL;

	try {

		if(m_pThis->FileExist(strPathFile)) {

			lstLinesReturn = new ListStringData();

			ifstream oCSVFile;
			oCSVFile.open(strPathFile.c_str());
			std::string strReadLine = STRING_EMPTY;

		    while(getline(oCSVFile, strReadLine)) {
		    	CGlobal::Trim(strReadLine);

		    	if(m_pThis->StartsWithPattern(strReadLine, COMMENTS) && !WithComments) {
		    		continue;
		    	}

		    	lstLinesReturn->push_back(strReadLine);
		    }

		    oCSVFile.close();
		}
	}
	catch(std::exception &exc) {
		lstLinesReturn = NULL;
		CLogger::GetLogger()->Log(" <EXCEPTION>: CGlobal::ReadFile " + std::string(exc.what()));
	}

	return lstLinesReturn;
}

/**
 * Function to a text file and store the result in a List of lines
 * @param: strPathFile: Parh where the file is located
 * @return: std:list with the lines of the text file.
 */
ListStringData * CGlobal::ReadFileOutput(std::string strPathFile) {

	ListStringData *lstLinesReturn = NULL;

	std::string strLineBefore = STRING_EMPTY;

	try {

		if(m_pThis->FileExist(strPathFile)) {

			lstLinesReturn = new ListStringData();

			ifstream oCSVFile;
			oCSVFile.open(strPathFile.c_str());
			std::string strReadLine = STRING_EMPTY;

		    while(getline(oCSVFile, strReadLine)) {
		    	CGlobal::Trim(strReadLine);

		    	if(!m_pThis->StartsWithPattern(strReadLine, COMMENTS) &&
		    		!CGlobal::GetGlobal()->FindString(strLineBefore,"*SOLID SECTION, ELSET=Integr_elms_truss_Tie_Area_") ) {
		    		if(m_pThis->NodeInList(strReadLine, *lstLinesReturn)) continue;
		    	}


		    	lstLinesReturn->push_back(strReadLine);

		    	strLineBefore = strReadLine;
		    }

		    oCSVFile.close();
		}
	}
	catch(std::exception &exc) {
		lstLinesReturn = NULL;
		CLogger::GetLogger()->Log(" <EXCEPTION>: CGlobal::ReadFile " + std::string(exc.what()));
	}

	return lstLinesReturn;
}

/**
 * Function to a text file and store the result in a List of lines
 * @param: strPathFile: Parh where the file is located
 * @return: std:list with the lines of the text file.
 */
ListStringData * CGlobal::ReadFileAll(std::string strPathFile) {

	ListStringData *lstLinesReturn = NULL;

	try {

		if(m_pThis->FileExist(strPathFile)) {

			lstLinesReturn = new ListStringData();

			ifstream oCSVFile;
			oCSVFile.open(strPathFile.c_str());
			std::string strReadLine = STRING_EMPTY;

		    while(getline(oCSVFile, strReadLine)) {
		    	CGlobal::Trim(strReadLine);

		    	if((!m_pThis->StartsWithPattern(strReadLine, GRID)	&&
					!m_pThis->StartsWithPattern(strReadLine, CQUAD4) &&
					!m_pThis->StartsWithPattern(strReadLine, CTRIA3) &&
					!m_pThis->StartsWithPattern(strReadLine, CBEAM) &&
					!m_pThis->StartsWithPattern(strReadLine, CROD)) ||
	    		   (m_pThis->StartsWithPattern(strReadLine, COMMENTS))) {
		    		continue;
		    	}

		    	lstLinesReturn->push_back(strReadLine);
		    }

		    oCSVFile.close();
		}
	}
	catch(std::exception &exc) {
		lstLinesReturn = NULL;
		CLogger::GetLogger()->Log(" <EXCEPTION>: CGlobal::ReadFile " + std::string(exc.what()));
	}

	return lstLinesReturn;
}

/**
 * Function to a text file and store the result in a List of lines
 * @param: lstDFEMData:
 * @param: lstDataDetail:
 * @param: strPattern:
 * @param: dNumElements
 * @return: std:list with the lines of the text file.
 */
DataMatrixDFEM1D2D * CGlobal::GetNodesDetail(ListStringData lstDFEMData, ListStringData *lstDataDetail, std::string strPattern, int dNumElements) {

	DataMatrixDFEM1D2D *oDataMAtrixReturn = NULL;
	ListStringData *lstNodesDFEM = new ListStringData;

	try {

		if((lstDFEMData.size() <= 0) ||
		   (lstDataDetail == NULL) ||
		   (lstDataDetail != NULL && lstDataDetail->size() <= 0)) return oDataMAtrixReturn;

		int dSize = std::stoi(CGlobal::GetItem(lstDFEMData, 2));

		oDataMAtrixReturn = new DataMatrixDFEM1D2D();

		if((int)lstDFEMData.size() >= dSize + 3) {
			ListStringData::iterator itListDFEMData = lstDFEMData.begin();

			// Advance the iterator by 3 positions,
			std::advance(itListDFEMData, 3);

			while(itListDFEMData != lstDFEMData.end()) {

				lstNodesDFEM->push_back((*itListDFEMData));
				itListDFEMData++;
			}
		}

		oDataMAtrixReturn->push_back(lstNodesDFEM);

	    for(ListStringData::iterator itData = lstDataDetail->begin(); itData != lstDataDetail->end(); itData++) {
	    	std::string strData = (*itData).erase(0,3);

	    	lstNodesDFEM = m_pThis->ParseDataLineNotNumber((*itData), strPattern, dNumElements);

    		if(lstNodesDFEM->size() > 0)
    			oDataMAtrixReturn->push_back(lstNodesDFEM);
	    }
	}
	catch(std::exception &exc) {
		oDataMAtrixReturn->clear();
		CLogger::GetLogger()->Log(" <EXCEPTION>: CGlobal::GetNodesDetail " + std::string(exc.what()));
	}

	return oDataMAtrixReturn;
}

/**
 * Function to return the unique values in a list of list nodes in string format
 * @param: lstData: List where de data are stored
 * @param: strPattern: Pattern to parse each line of data
 * @return: ListStringData with the uniques values.
 */
ListStringData * CGlobal::GetUniqueValues(ListStringData *lstData, std::string strPattern) {

	ListStringData *lstUniqueElements = NULL;

	try {

		if((lstData == NULL) || (lstData != NULL && lstData->size() <= 0)) 	return lstUniqueElements;

		lstUniqueElements = new ListStringData();

	    for(ListStringData::iterator itData = lstData->begin(); itData != lstData->end(); itData++) {

	    	ListStringData lstLine =  m_pThis->ParseDataLine((*itData), strPattern, false);

	    	if(lstLine.size() > 0) {
	    		lstUniqueElements->splice(lstUniqueElements->end(), lstLine);
	    	}
	    }

	    lstUniqueElements->sort();
	    lstUniqueElements->unique();

	    //m_pThis->ShowListData(*lstUniqueElements);
	}
	catch(std::exception &exc) {
		lstUniqueElements->clear();
		CLogger::GetLogger()->Log(" <EXCEPTION>: CGlobal::GetUniqueValues " + std::string(exc.what()));
	}

	//CGlobal::GetGlobal()->ShowListData(*lstUniqueElements);

	return lstUniqueElements;
}

/**
 * Function to return
 * @param: IdSegment: List where de data are stored
 * @param: dataConnection: Pattern to parse each line of data
 * @param: node1: Pattern to parse each line of data
 * @param: node2: Pattern to parse each line of data
 * @return:
 */
bool CGlobal::FindSegmentDFEMNodes(std::string IdSegment, DataMatrixDFEM1D2D *dataConnection, std::string &node1, std::string &node2){

	bool bReturn = RESULT_KO;
	int dLocated = 0;
	int dSegmentIndex1 = UNDEFINED;
	int dSegmentIndex2 = UNDEFINED;
	int dAuxIndex = 0;

	try {

		if(dataConnection == NULL) return bReturn;

		DataMatrixDFEM1D2D::iterator itMatrix = dataConnection->begin();

		while(++itMatrix != dataConnection->end() && dLocated < 2) {

			dAuxIndex = 0;

			for(std::list<std::string>::iterator itElement = (*itMatrix)->begin(); itElement != (*itMatrix)->end(); itElement++) {

				//cout << " NodeFind: " << IdSegment << "  Node Matrix: " << (*itElement) << " Indx: " << dAuxIndex << endl;

				if(IdSegment == (*itElement)) {

					if(dLocated++ == 0) {
						dSegmentIndex1 = dAuxIndex;
						dAuxIndex++;
					}
					else {
						dSegmentIndex2 = dAuxIndex;
					}

					if(dLocated == 2) {
						break;
					}
				}
				else {
					++dAuxIndex;
				}
			}

			if(dLocated == 2) {
				break;
			}
		}

		if(dSegmentIndex1 != UNDEFINED) {
			itMatrix = dataConnection->begin();
			node1 = m_pThis->GetItemAtPosition(*(*itMatrix), dSegmentIndex1);
		}

		if(dSegmentIndex2 != UNDEFINED) {
			itMatrix = dataConnection->begin();
			node2 = m_pThis->GetItemAtPosition(*(*itMatrix), dSegmentIndex2);
		}

		bReturn = RESULT_OK;
	}
	catch(std::exception &exc) {
		CLogger::GetLogger()->Log(" <EXCEPTION>: CGlobal::FindSegmentDFEMNodes " + std::string(exc.what()));
	}

	return bReturn;
}

/**
 *
 * @param strSource
 * @param strFind
 * @return
 */
bool CGlobal::FindString(std::string strSource, std::string strFind) {

	bool bReturn = false;

	try {
		// different member versions of find in the same order as above:
		 std::size_t found = strSource.find(strFind);

		 if (found!=std::string::npos) {

			 bReturn = true;
		 }
	}
	catch(std::exception &exc) {
		CLogger::GetLogger()->Log(" <EXCEPTION>: CGlobal::FindString " + std::string(exc.what()));
	}

	return bReturn;

}

/**
 *
 * @param strSource
 * @param strFind
 * @return
 */
void CGlobal::RemoveString(std::string &strSource, std::string strRemove) {

	bool bDeleted = false;

	try {
		std::string::size_type pos1 = strSource.find(strRemove);

		std::string strToRemove = strRemove;
		m_pThis->ToUpper(strToRemove);
		std::string::size_type pos2 = strSource.find(strToRemove);

		if (pos1 != std::string::npos) {
			strSource.erase(pos1, strRemove.length());

			bDeleted = true;
		}

		if (!bDeleted && pos2 != std::string::npos) {
			strSource.erase(pos2, strRemove.length());
		}

	}
	catch(std::exception &exc) {
		CLogger::GetLogger()->Log(" <EXCEPTION>: CGlobal::FindString " + std::string(exc.what()));
	}

}

/**
 *
 * @param lstItems
 * @param strFind
 * @return
 */
std::string CGlobal::GetItemContain(ListStringData lstItems, std::string strFind) {
	std::string strReturn = STRING_EMPTY;
	bool bLocated = false;

	try {

		for(ListStringData::iterator itList = lstItems.begin(); itList != lstItems.end(); itList++) {

			std::string strItem = (*itList);
			if(m_pThis->FindString(strItem, strFind)) {

				m_pThis->RemoveString(strItem, strFind);
				m_pThis->Trim(strItem);

				strReturn = strItem;

				break;
			}
		}

	}
	catch(std::exception &exc) {
		CLogger::GetLogger()->Log(" <EXCEPTION>: CGlobal::FindString " + std::string(exc.what()));
	}

	return strReturn;
}

/**
 *
 * @param strPathFile
 * @return
 */
std::string CGlobal::GetELSETName(std::string strReadLine, std::string strDelimiter) {

	std::string strReturn = STRING_EMPTY;

	try {
		if(CGlobal::GetGlobal()->FindString(strReadLine, ELSET_NAME)) {
			ListStringData lstItems = m_pThis->ParseDataLineStrings(strReadLine, strDelimiter);

			strReturn = CGlobal::GetGlobal()->GetItemContain(lstItems, ELSET_NAME);
		}
	}
	catch(std::exception &exc) {
		CLogger::GetLogger()->Log(" <EXCEPTION>: CGlobal::GetELSETName " + std::string(exc.what()));
	}

	return strReturn;
}

/**
 *
 * @param strPathFile
 * @return
 */
std::string CGlobal::GetInstanceName(std::string strReadLine, std::string strDelimiter) {

	std::string strReturn = STRING_EMPTY;
	std::string strReturnUPP = STRING_EMPTY;

	try {
		if(CGlobal::GetGlobal()->FindString(strReadLine, NAME) ||CGlobal::GetGlobal()->FindString(strReadLine, NAME_UPP)) {
			ListStringData lstItems = m_pThis->ParseDataLineStrings(strReadLine, strDelimiter);

			strReturn = CGlobal::GetGlobal()->GetItemContain(lstItems, NAME);
			strReturnUPP = CGlobal::GetGlobal()->GetItemContain(lstItems, NAME_UPP);
		}
	}
	catch(std::exception &exc) {
		CLogger::GetLogger()->Log(" <EXCEPTION>: CGlobal::GetInstanceName " + std::string(exc.what()));
	}

	if(strReturn != STRING_EMPTY)
		return strReturn;
	else
		return strReturnUPP;
}

/**
 *
 * @param strPathFile
 * @return
 */
std::string CGlobal::GetInstancePart(std::string strReadLine, std::string strDelimiter) {

	std::string strReturn = STRING_EMPTY;

	try {
		if(CGlobal::GetGlobal()->FindString(strReadLine, PART)) {
			ListStringData lstItems = m_pThis->ParseDataLineStrings(strReadLine, strDelimiter);

			strReturn = CGlobal::GetGlobal()->GetItemContain(lstItems, PART);
		}
	}
	catch(std::exception &exc) {
		CLogger::GetLogger()->Log(" <EXCEPTION>: CGlobal::GetInstancePart " + std::string(exc.what()));
	}

	return strReturn;
}


/**
 * Function to create a kinematic coupling between the node of the CoG and all DFEM NODES 1D/2D
 * @param: dTie
 * @return: The string result by the lines concatenation
 */
std::string CGlobal::Create_Kinematic_Coupling_CoG_DFEM_1D_2D(CConnection *oConnection, int dPart) {

	std::string strReturn = STRING_EMPTY;
	std::string strNodes = STRING_EMPTY;
	std::string strLineReaded = STRING_EMPTY;
	std::string strLine1_Kinematic = STRING_EMPTY;
	std::string strLine2_Kinematic = STRING_EMPTY;

	int dIdGFEMNode = UNDEFINED;

	try {

		int dIdNodeGFEM = UNDEFINED;
		MapGFEMNodes::iterator itGFEmNodes = oConnection->GetGFEMNodes()->begin();
		if(itGFEmNodes != oConnection->GetGFEMNodes()->end()) {

			dIdNodeGFEM = (*itGFEmNodes).second->getIdNode();

			if(dPart == PART_0) {
				strLineReaded = m_pThis->getIniFile().get("kINEMATIC_COUPLING_COG_DFEM_1D2D").get("line_0");
				int dNodesLine = std::stol(m_pThis->getIniFile().get("kINEMATIC_COUPLING_COG_DFEM_1D2D").get("n_nodes_per_line"));

				m_pThis->Replace(strLineReaded, "%NODE%", std::to_string(dIdNodeGFEM));

				MapDFEMNodes::iterator itDFEMNode = oConnection->GetDFEMNodes()->begin();

				int dNodesWrited = 0;
				if(itDFEMNode != oConnection->GetDFEMNodes()->end())
				{
					while(itDFEMNode != oConnection->GetDFEMNodes()->end()) {

						dNodesWrited++;
						strNodes += std::to_string((*itDFEMNode).second->getIdNode()) + ", ";

						if(dNodesWrited >= dNodesLine) {

							strNodes +=  "\n";
							dNodesWrited = 0;
						}

						itDFEMNode++;
					}
				}

				strReturn = "\n" + strLineReaded + "\n" + strNodes + "\n**\n**";

			}
			else if(dPart == PART_1) {

				strLine1_Kinematic = m_pThis->getIniFile().get("kINEMATIC_COUPLING_COG_DFEM_1D2D").get("line_1");
				strLine2_Kinematic = m_pThis->getIniFile().get("kINEMATIC_COUPLING_COG_DFEM_1D2D").get("line_2");

				m_pThis->Replace(strLine1_Kinematic, "%COG_NODE%", std::to_string(oConnection->getIdCoGNode()));
				m_pThis->Replace(strLine2_Kinematic, "%NODE%", std::to_string(dIdNodeGFEM));

				strReturn = strLine1_Kinematic + "\n" + strLine2_Kinematic;
			}
		}
	}
	catch(std::exception &exc) {
		strReturn = STRING_EMPTY;

		CLogger::GetLogger()->Log(" <EXCEPTION>: CGlobal::Create_Surface_NSET " + std::string(exc.what()));
	}

	return strReturn;
}

/**
 *
 * @param connection
 * @return
 */
std::string CGlobal::GetNodesGFEM_OutputData(CConnection *connection, ListIntegerData &lstNodesProcessed) {

	std::string strReturn = STRING_EMPTY;
	std::string strNodeData = STRING_EMPTY;

	try {

		if(connection == NULL)  return strReturn;
		if(connection->GetGFEMNodes()->size() <= 0) return strReturn;

		MapGFEMNodes *mapNodes = connection->GetGFEMNodes();


		for(MapGFEMNodes::iterator itGFEMNode = mapNodes->begin(); itGFEMNode != mapNodes->end(); itGFEMNode++) {

			std::string strIdNode = std::to_string((*itGFEMNode).second->getIdNode());

			if(CGlobal::GetGlobal()->NodeInList((*itGFEMNode).second->getIdNode(), lstNodesProcessed)) continue;

			std::string strCoord_X = std::to_string((*itGFEMNode).second->getGridNode()->getCoord_X1());
			std::string strCoord_Y = std::to_string((*itGFEMNode).second->getGridNode()->getCoord_X2());
			std::string strCoord_Z = std::to_string((*itGFEMNode).second->getGridNode()->getCoord_X3());

			strNodeData = CGlobal::GetGlobal()->PadLeft(strIdNode,10,' ') 		+ ",  " +
						  CGlobal::GetGlobal()->PadRight(strCoord_X, 15, ' ') 	+ ",  " +
						  CGlobal::GetGlobal()->PadRight(strCoord_Y, 15, ' ') 	+ ",  " +
						  CGlobal::GetGlobal()->PadRight(strCoord_Z, 15, ' ')	+ "\n";

			strReturn += strNodeData;

			lstNodesProcessed.push_back((*itGFEMNode).second->getIdNode());
		}

	}
	catch(std::exception &exc) {
		strReturn = STRING_EMPTY;

		CLogger::GetLogger()->Log(" <EXCEPTION>: CGlobal::GetNodesGFEM_OutputData " + std::string(exc.what()));
	}

	return strReturn;

}

/**
 *
 * @param connection
 * @return
 */
std::string CGlobal::GetNode2Node3CoG_OutputData(CConnection *connection, int dType, ListIntegerData &lstNodesProcessed) {

	std::string strReturn = STRING_EMPTY;
	std::string strNodeData = STRING_EMPTY;

	try {

		if(connection == NULL)  return strReturn;
		if(connection->GetGFEMNodes()->size() <= 0) return strReturn;

		MapGFEMNodes *mapNodes = connection->GetGFEMNodes();

		std::string strIdNode = STRING_EMPTY;
		std::string strCoord_X = STRING_EMPTY;
		std::string strCoord_Y = STRING_EMPTY;
		std::string strCoord_Z = STRING_EMPTY;

		for(MapGFEMNodes::iterator itGFEMNode = mapNodes->begin(); itGFEMNode != mapNodes->end(); itGFEMNode++) {

			if((*itGFEMNode).second->getNode_2_ID() != 0 &&
			   !CGlobal::GetGlobal()->NodeInList((*itGFEMNode).second->getNode_2_ID(), lstNodesProcessed)) {

				strIdNode  = std::to_string((*itGFEMNode).second->getNode_2_ID());
				strCoord_X = std::to_string((*itGFEMNode).second->getNode_2_X1());
				strCoord_Y = std::to_string((*itGFEMNode).second->getNode_2_X2());
				strCoord_Z = std::to_string((*itGFEMNode).second->getNode_2_X3());

				strNodeData = CGlobal::GetGlobal()->PadLeft(strIdNode,10,' ') 		+ ",  " +
							  CGlobal::GetGlobal()->PadRight(strCoord_X, 15, ' ') 	+ ",  " +
							  CGlobal::GetGlobal()->PadRight(strCoord_Y, 15, ' ') 	+ ",  " +
							  CGlobal::GetGlobal()->PadRight(strCoord_Z, 15, ' ')	+ "\n";

				lstNodesProcessed.push_back((*itGFEMNode).second->getNode_2_ID());
			}

			if((*itGFEMNode).second->getNode_3_ID() != 0 &&
			   !CGlobal::GetGlobal()->NodeInList((*itGFEMNode).second->getNode_3_ID(), lstNodesProcessed)) {

				strIdNode  = std::to_string((*itGFEMNode).second->getNode_3_ID());
				strCoord_X = std::to_string((*itGFEMNode).second->getNode_3_X1());
				strCoord_Y = std::to_string((*itGFEMNode).second->getNode_3_X2());
				strCoord_Z = std::to_string((*itGFEMNode).second->getNode_3_X3());

				strNodeData += CGlobal::GetGlobal()->PadLeft(strIdNode,10,' ') 		+ ",  " +
							  CGlobal::GetGlobal()->PadRight(strCoord_X, 15, ' ') 	+ ",  " +
							  CGlobal::GetGlobal()->PadRight(strCoord_Y, 15, ' ') 	+ ",  " +
							  CGlobal::GetGlobal()->PadRight(strCoord_Z, 15, ' ')	+ "\n";

				lstNodesProcessed.push_back((*itGFEMNode).second->getNode_3_ID());
			}

			if(dType == TYPE_1D2D) {

				if((*itGFEMNode).second->getCoG_NODE() != 0 &&
				   !CGlobal::GetGlobal()->NodeInList((*itGFEMNode).second->getCoG_NODE(), lstNodesProcessed)) {

					std::string strIdNode_CoG  = std::to_string((*itGFEMNode).second->getCoG_NODE());
					std::string strCoord_X_CoG = std::to_string((*itGFEMNode).second->getCoG_NODE_X1());
					std::string strCoord_Y_CoG = std::to_string((*itGFEMNode).second->getCoG_NODE_X2());
					std::string strCoord_Z_CoG = std::to_string((*itGFEMNode).second->getCoG_NODE_X3());

					strNodeData += CGlobal::GetGlobal()->PadLeft(strIdNode_CoG,10,' ') 		+ ",  " +
								  CGlobal::GetGlobal()->PadRight(strCoord_X_CoG, 15, ' ') 	+ ",  " +
								  CGlobal::GetGlobal()->PadRight(strCoord_Y_CoG, 15, ' ') 	+ ",  " +
								  CGlobal::GetGlobal()->PadRight(strCoord_Z_CoG, 15, ' ')	+ "\n";

					lstNodesProcessed.push_back((*itGFEMNode).second->getCoG_NODE());
				}
			}

			strReturn += strNodeData;
		}
	}
	catch(std::exception &exc) {
		strReturn = STRING_EMPTY;

		CLogger::GetLogger()->Log(" <EXCEPTION>: CGlobal::GetNodesGFEM_OutputData " + std::string(exc.what()));
	}

	return strReturn;
}

/**
 * Function to a text file and store the result in a List of lines
 * @param: strPathFile: Parh where the file is located
 * @return: std:list with the lines of the text file.
 */
ListStringData * CGlobal::ReadFileBetweenPatterns(std::string strPathFile, std::string strBeginSection, std::string strEndSection) {

	ListStringData *lstLinesReturn = new ListStringData();

	bool bBeginSection = false;
	bool bEndSection = false;

	try {

		if(m_pThis->FileExist(strPathFile)) {

			ListStringData *lstFileData = ReadFile(strPathFile);
			ListStringData::iterator itLine = lstFileData->begin();

			while(itLine != lstFileData->end() && !bEndSection) {

				std::string strLine = (*itLine);

				if(strBeginSection != STRING_EMPTY) {
					if(bBeginSection == false && m_pThis->StartsWithPattern((*itLine), strBeginSection) ) {
						bBeginSection = true;
					}
				}
				else
					bBeginSection = true;

				if(bBeginSection && m_pThis->StartsWithPattern((*itLine), INCLUDE) ) {

					std::string::size_type pos = strLine.find("=");

					if (pos != std::string::npos) {
						strLine.erase(0, pos+1);
					}

					CGlobal::GetGlobal()->Replace(strLine, "./", "");

					lstLinesReturn->push_back(strLine);
				}

				itLine++;

				if(strEndSection ==  STRING_EMPTY) {
					bEndSection = (itLine == lstFileData->end());

					continue;
				}

				if(strEndSection !=  STRING_EMPTY && m_pThis->StartsWithPattern((*itLine), strEndSection) ) {
					bEndSection = true;
				}
			}
		}
	}
	catch(std::exception &exc) {
		lstLinesReturn = NULL;
		CLogger::GetLogger()->Log(" <EXCEPTION>: CGlobal::ReadFileBetweenPatterns " + std::string(exc.what()));
	}

	return lstLinesReturn;
}

/**
 * Function to a text file and store the result in a List of lines
 * @param: strPathFile: Parh where the file is located
 * @return: std:list with the lines of the text file.
 */
void CGlobal::GetTwoParts(std::string strSource, std::string strDelimiter, std::string &strPart1, std::string &strPart2) {


	try {

		strPart2 = strSource;
		size_t pos = strPart2.find(strDelimiter);
		strPart2.erase (strPart2.begin(), (strPart2.begin() + pos + 1));

		strPart1 = strSource.substr(0, pos);
	}
	catch(std::exception &exc) {
		CLogger::GetLogger()->Log(" <EXCEPTION>: CGlobal::GetTwoParts " + std::string(exc.what()));
	}
}


/**
 * Function to
 * @param: strSource
 * @return:
 */
void CGlobal::ToLower(std::string &strSource) {

	std::transform(strSource.begin(), strSource.end(), strSource.begin(), [](unsigned char c){ return std::tolower(c); });
}

/**
 * Function to
 * @param: strSource
 * @return:
 */
void CGlobal::ToUpper(std::string &strSource) {

	std::transform(strSource.begin(), strSource.end(), strSource.begin(), [](unsigned char c){ return std::toupper(c); });
}

/**
 *
 * @param mapGridData
 * @param keyNode
 * @return
 */
ListStringData  CGlobal::GetDFEMNode(MapDFEMData *mapDFEMData, std::string keyNode) {

	ListStringData lstGFEMNode;

	try {

		if ((mapDFEMData == NULL) ||
			(mapDFEMData != NULL && mapDFEMData->size() <= 0)) return lstGFEMNode;

		if(mapDFEMData->size() > 0) {

			MapDFEMData::iterator itMap;
			itMap = mapDFEMData->find(keyNode);

			if (itMap != mapDFEMData->end()) {
				lstGFEMNode = itMap->second;
			}
		}
	}
	catch(std::exception &exc) {

		CLogger::GetLogger()->Log(" <EXCEPTION>: CGlobal::GetGFEMNode " + std::string(exc.what()));
	}

	return lstGFEMNode;
}

/**
 *
 * @param strFile
 * @param &strName
 * @param &strExtension
 * @return: The result of the operation
 */
bool  CGlobal::GetFileNameAndExtension(std::string strFile, std::string &strName, std::string &strExtension) {

	bool bReturn = RESULT_KO;

	try {

    	size_t pos = strFile.find(".");

    	if(pos == std::string::npos) {
    		strName = strFile;
    		strExtension = STRING_EMPTY;
    	}
    	else {
    		m_pThis->GetTwoParts(strFile, ".", strName, strExtension);
    	}




		bReturn = RESULT_OK;
	}
	catch(std::exception &exc) {

		CLogger::GetLogger()->Log(" <EXCEPTION>: CGlobal::GetFileNameAndExtension " + std::string(exc.what()));
	}

	return bReturn;
}


