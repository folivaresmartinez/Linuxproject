/*
 * Logger.cpp
 *
 *  Created on: 13 nov. 2019
 *      Author: fernando.olivares
 */



#include <stdlib.h>
#include <stdarg.h>
#include <stdio.h>

#include "../Headers/Logger.h"
#include "../Headers/Global.h"


const string CLogger::m_sFileName = "MyLogFile.log";
CLogger* CLogger::m_pThis = NULL;
ofstream CLogger::m_Logfile;

/**
 * 
 */
CLogger::CLogger()
{

}

/**
 * 
 * @return 
 */
CLogger* CLogger::GetLogger()
{
    if (m_pThis == NULL)
    {
            m_pThis = new CLogger();
            //m_Logfile.open(m_sFileName.c_str(), ios::out | ios::app);
    }
    return m_pThis;
}

/**
 * 
 * @param format
 * @param ...
 */
void CLogger::Log(const char * format, ...)
{
	char* sMessage = NULL;
	int nLength = 0;
	va_list args;
	va_start(args, format);
	//  Return the number of characters in the string referenced the list of arguments.
	// _vscprintf doesn't count terminating '\0' (that's why +1)
	nLength = CGlobal::_vscprintf(format, args) + 1;
       
	sMessage = new char[nLength];
	//vsprintf_s(sMessage, nLength, format, args);
        
	vsprintf(sMessage, format, args);
	m_Logfile << "[" + CGlobal::CurrentDateTime() << "]:\t";
	m_Logfile << sMessage << "\n";
	va_end(args);

	delete [] sMessage;
}

/**
 * 
 * @param sMessage
 */
void CLogger::Log(const string& sMessage)
{
	m_Logfile <<  "[" + CGlobal::CurrentDateTime() << "]:\t";
	m_Logfile << sMessage << "\n";
}

/**
 * 
 * @param sMessage
 * @return 
 */ 
CLogger& CLogger::operator<<(const string& sMessage)
{
	m_Logfile << "\n" << "[" + CGlobal::CurrentDateTime()  + "] --> " << ":\t";
	m_Logfile << sMessage << "\n";
	return *this;
}

void CLogger::SetPath(std::string strPath) {

	m_Logfile.open(strPath + "/" + m_sFileName.c_str(), ios::out | ios::app);


}

