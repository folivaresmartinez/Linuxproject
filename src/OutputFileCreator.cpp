/*
 * OutputFileCreator.cpp
 *
 *  Created on: 14 nov. 2019
 *      Author: fernando.olivares
 */


#include <iostream>
#include <fstream>
#include <stdio.h>

#include "../Headers/OutputFileCreator.h"
#include "../Headers/Global.h"
#include "../Headers/Logger.h"
#include "../Headers/Calculations.h"
#include "../Headers/GFEMReader.h"
#include "../Headers/GlobalDFEMReader.h"

using namespace std;

COutputFileCreator* COutputFileCreator::m_pThis = NULL;

#pragma GCC diagnostic ignored "-Wunused-variable"

/**
 * Default Contructor on the class
 */
COutputFileCreator::COutputFileCreator() {
	m_PathFile = STRING_EMPTY;
}

/**
 * Default destructor on the class
 */
COutputFileCreator::~COutputFileCreator() {
	// TODO Auto-generated destructor stub
}

/**
 * Return a CGlobal instance
 * @return: CGlobal instance
 */
COutputFileCreator* COutputFileCreator::GetOutputFileCreator()
{
    if (m_pThis == NULL)
    {
            m_pThis = new COutputFileCreator();
    }

    return m_pThis;
}


/**
 * Method to compose a message with a formtar
 * @param strPathFile: Format to apply to the message
 * @param strData: params of the message
 * @return: result of the operation
 */
bool COutputFileCreator::OpenFile(std::string strPathFile, ofstream &fileOpen) {

	bool bReturn = RESULT_KO;

	 std::stringstream ss;

	 try {

		if( std::remove( strPathFile .c_str()) != 0 ) {

			ss << " <EXCEPTION>: COutputFileCreator::OpenFile "
			   << " Error deleting file: "
			   << strPathFile;

			CLogger::GetLogger()->Log(ss.str());
		}

		fileOpen.open (strPathFile, ios::app | ios::out );

		if(!fileOpen)
		{
			ss.clear();

			ss << " <EXCEPTION>: COutputFileCreator::OpenFile "
			   << " Error creating file: "
			   << strPathFile;

			CLogger::GetLogger()->Log(ss.str());

			return RESULT_KO;
		}

		bReturn = RESULT_OK;
	 }
	 catch(std::exception &exc) {

		 CLogger::GetLogger()->Log(" <EXCEPTION>: COutputFileCreator::OpenFile " + std::string(exc.what()));
	 }

	 return bReturn;
}

/**
 * Method to compose a message with a formtar
 * @param strPathFile: Format to apply to the message
 * @param strData: params of the message
 * @return: result of the operation
 */
bool COutputFileCreator::CloseFile(ofstream &fileOpen) {

	bool bReturn = RESULT_KO;

	try {

		fileOpen.close();

		bReturn = RESULT_OK;
	 }
	 catch(std::exception &exc) {

		 CLogger::GetLogger()->Log(" <EXCEPTION>: COutputFileCreator::CloseFile " + std::string(exc.what()));
	 }

	return bReturn;
}

/**
 * Method to compose a message with a formtar
 * @param strPathFile: Format to apply to the message
 * @param strData: params of the message
 * @return: result of the operation
 */
bool COutputFileCreator::AppendLine(ofstream &outputFile, std::string strLine) {

	bool bReturn = RESULT_KO;
	std::stringstream ss;

	try {

	    if(!outputFile)
	    {
	    	ss << " <EXCEPTION>: COutputFileCreator::OpenFile "
			   <<  "Error appending line to file";

			CLogger::GetLogger()->Log(ss.str());

	        return RESULT_KO;
	    }

	    CGlobal::GetGlobal()->Trim(strLine);

		outputFile << strLine;

		bReturn = RESULT_OK;
	 }
	 catch(std::exception &exc) {

		 CLogger::GetLogger()->Log(" <EXCEPTION>: COutputFileCreator::AppendLine " + std::string(exc.what()));
	 }

	return bReturn;
}

/**
 * Method to compose a message with a formtar
 * @return: result of the operation, KO or OK
 */
bool COutputFileCreator::CreateOutputFiles(std::string strPath) {
	 bool bReturn = RESULT_KO;

	 try {

		 CGlobal::Replace(strPath, "/cygdrive/c/", "C:/");

		 strPath += CGlobal::GetGlobal()->getIniFile().get("DATA_DIRECTORIES").get("output_files");

		 std::string strPartFile = strPath + CGlobal::GetGlobal()->getIniFile().get("OUTPUT_FILES").get("part");
		 std::string strInstanceFile = strPath + CGlobal::GetGlobal()->getIniFile().get("OUTPUT_FILES").get("instance");
		 std::string strAssemblyFile = strPath + CGlobal::GetGlobal()->getIniFile().get("OUTPUT_FILES").get("assembly");
		 std::string strMaterialFile = strPath + CGlobal::GetGlobal()->getIniFile().get("OUTPUT_FILES").get("material");

		 m_pThis->CreateFile_Part(strPartFile);
		 m_pThis->CreateFile_Instance(strInstanceFile);
		 m_pThis->CreateFile_Assembly(strAssemblyFile);
		 m_pThis->CreateFile_material(strMaterialFile);

		 if(CGlobal::GetGlobal()->getFormatData() == FORMAT_2) {
			 m_pThis->CreateMainDFEMFile(strPath, CGlobal::GetGlobal()->getMainDFEMFile());
		 }
	 }
	 catch(std::exception &exc) {

		 CLogger::GetLogger()->Log(" <EXCEPTION>: COutputFileCreator::CreateOutputFiles " + std::string(exc.what()));
	 }

	 return bReturn;
}

/**
 * Method to compose a message with a format
 * @param strPathFile: Format to apply to the message
 * @return: result of the operation, KO or OK
 */
bool COutputFileCreator::CreateFile_Part(std::string strPathFile) {
	 bool bReturn = RESULT_KO;
	 std::string strLine = STRING_EMPTY;
	 ofstream PartFile;
	 std::stringstream ss;

	 cout << "Path File: " << strPathFile << endl;

	 try {

		 if( m_pThis->OpenFile(strPathFile, PartFile)) {

			 ss << "****************************************************************************************************\n"
				<< "**\n"
			 	<< "**       			Integration_part.inp \n"
				<< "**				   Date: " << CGlobal::GetGlobal()->CurrentDateTime() 		 	 				 <<"\n"
				<< "**\n"
				<< "****************************************************************************************************\n"
				<< "**\n"
				<< "*PART, NAME=Integration_part\n"
				<< "**\n"
				<< "**\n"
				<<"*NODE, NSET=GFEM_nodes\n"
				<< m_pThis->GetStringNodesGFEM()
				<< "**\n"
				<< "**\n"
			 	<< "*NODE\n"
				<< m_pThis->GetStringNode2Node3CoG()
				<< "**\n"
				<< "**\n"
				<< m_pThis->GetStringKINEMATIC_COUPLING_COG_DFEM_1D2D()
				<< "\n**\n"
				<< "**\n"
				<< m_pThis->GetT3D2_ABAQUS()
				<< "**\n"
				<< "**\n"
				<< m_pThis->GetSOLIDSECTION()
				<< "**\n"
				<< "**\n"
				<< m_pThis->GetSurfaceWithT3D2Elements()
				<< "**\n"
				<< "**\n"
				<< m_pThis->GetSurfaceDFEMNodes()
				<< "**\n"
				<< m_pThis->GetSurfaceNSET()
				<< "**\n"
				<< "**\n"
				<<"*END PART \n";

				m_pThis->AppendLine(PartFile, ss.str());
		 }

		 m_pThis->CloseFile(PartFile);

	 }
	 catch(std::exception &exc) {

		 CLogger::GetLogger()->Log(" <EXCEPTION>: COutputFileCreator::CreateFile_Part " + std::string(exc.what()));
	 }

	 m_pThis->CleanFile(strPathFile);

	 return bReturn;
}

void COutputFileCreator::CleanFile(std::string strPathFile) {

	std::string strLine = STRING_EMPTY;
	ofstream PartFile;
	std::stringstream ss;

	ListStringData *lstFile = CGlobal::GetGlobal()->ReadFile(strPathFile, true);

	lstFile->remove(STRING_EMPTY);

	if( m_pThis->OpenFile(strPathFile, PartFile)) {
		for(ListStringData::iterator itLine = lstFile->begin(); itLine != lstFile->end(); itLine++) {

			ss << (*itLine) + "\n";
		}

		m_pThis->AppendLine(PartFile, ss.str());
	}

	m_pThis->CloseFile(PartFile);
}

/**
 * Method to compose a message with a defined format
 * @param strPathFile: Format to apply to the message
 * @return: result of the operation, KO or OK
 */
bool COutputFileCreator::CreateFile_Instance(std::string strPathFile) {

	 bool bReturn = RESULT_KO;
	 std::string strLine = STRING_EMPTY;
	 ofstream InstanceFile;
	 std::stringstream ss;

	 cout << "Path File: " << strPathFile << endl;

	 try {

		 if( m_pThis->OpenFile(strPathFile, InstanceFile)) {

			 ss << "****************************************************************************************************\n"
				<< "**\n"
			 	<< "**       				Integration_instance.inp \n"
				<< "**					   Date: " << CGlobal::GetGlobal()->CurrentDateTime() 		 	 <<"\n"
				<< "**\n"
				<< "****************************************************************************************************\n"
				<< "**\n"
				<< "*INSTANCE, NAME=Integration_instance, PART=Integration_part\n"
				<< "*END INSTANCE\n";

				m_pThis->AppendLine(InstanceFile, ss.str());
		 }

		 m_pThis->CloseFile(InstanceFile);

	 }
	 catch(std::exception &exc) {

		 CLogger::GetLogger()->Log(" <EXCEPTION>: COutputFileCreator::CreateFile_Instance " + std::string(exc.what()));
	 }

	 return bReturn;
}

/**
 * Method to compose a message with a defined format
 * @param strPathFile: Format to apply to the message
 * @return: result of the operation, KO or OK
 */
bool COutputFileCreator::CreateFile_material(std::string strPathFile) {

	 bool bReturn = RESULT_KO;
	 std::string strLine = STRING_EMPTY;
	 ofstream MaterialFile;
	 std::stringstream ss;

	 cout << "Path File: " << strPathFile << endl;

	 try {

		 if( m_pThis->OpenFile(strPathFile, MaterialFile)) {

			 ss << "****************************************************************************************************\n"
				<< "**\n"
			 	<< "**       				Integration_material.inp \n"
				<< "**					   Date: " << CGlobal::GetGlobal()->CurrentDateTime() 		 	 <<"\n"
				<< "**\n"
				<< "****************************************************************************************************\n"
				<< "**\n"
				<< "**\n"
				<< m_pThis->GetT3D2ElementBetweenGFEMProjectedNodes();

				m_pThis->AppendLine(MaterialFile, ss.str());
		 }

		 m_pThis->CloseFile(MaterialFile);
	 }
	 catch(std::exception &exc) {

		 CLogger::GetLogger()->Log(" <EXCEPTION>: COutputFileCreator::CreateFile_material " + std::string(exc.what()));
	 }

	 return bReturn;
}

/**
 * Method to compose a message with a defined format
 * @param strPathFile: Format to apply to the message
 * @return: result of the operation, KO or OK
 */
bool COutputFileCreator:: CreateFile_Assembly(std::string strPathFile) {

	 bool bReturn = RESULT_KO;
	 std::string strLine = STRING_EMPTY;
	 ofstream InstanceFile;
	 std::stringstream ss;

	 cout << "Path File: " << strPathFile << endl;

	 try {

		 if( m_pThis->OpenFile(strPathFile, InstanceFile)) {

			 ss << "****************************************************************************************************\n"
				<< "**\n"
			 	<< "**       				Integration_assembly.inp \n"
				<< "**					   Date: " << CGlobal::GetGlobal()->CurrentDateTime() 		 	  <<"\n"
				<< "**\n"
				<< "****************************************************************************************************\n"
				<< "**\n"
				<< "**\n"
				<< m_pThis->GetTIE_CARD()
				<< "**\n"
				<< "**\n"
				<< m_pThis->GetKINEMATIC_COUPLING_1_2_CARD()
				<< "**\n"
				<< m_pThis->GetKINEMATIC_COUPLING_CoG_DFEM_1D_2D()
				<< "**\n"
				<< "**";

			 	 if(CGFEMReader::GetGFEMReader()->getListCBEAM_Data()->size() > 0) {
					ss << "\n"
					   << m_pThis->GetConnNodesProjGFEM1D2DToCoG(TYPE_CBEAM)
					   << "**\n"
					   << "**";
				}

				ss << m_pThis->GetEQUATION_CARD_NODE3_NODE2_GFEM_2D2D();

				if(CGFEMReader::GetGFEMReader()->getListCROD_Data()->size() > 0) {
					ss << "\n**\n"
					   << "**\n"
					   << m_pThis->GetConnNodesProjGFEM1D2DToCoG(TYPE_CROD);
				}

				m_pThis->AppendLine(InstanceFile, ss.str());
		 }

		 m_pThis->CloseFile(InstanceFile);
	 }
	 catch(std::exception &exc) {

		 CLogger::GetLogger()->Log(" <EXCEPTION>: COutputFileCreator::CreateFile_Assembly " + std::string(exc.what()));
	 }

	 m_pThis->CleanFile(strPathFile);

	 return bReturn;
}

/**
 * Method to compose a message with a defined format
 * @return: result of the operation, KO or OK
 */
std::string COutputFileCreator::GetStringNodesGFEM() {

	std::string strReturn = STRING_EMPTY;

	 try {

		 ListStringData *lstGFEmNodes = CCalculations::GetCalculations()->GetGFEMNodesString();

		 for(ListStringData::iterator itList = lstGFEmNodes->begin(); itList != lstGFEmNodes->end(); itList++) {

			 strReturn += (*itList);
		 }

		 lstGFEmNodes->clear();
		 delete lstGFEmNodes;
		 lstGFEmNodes = NULL;
	 }
	 catch(std::exception &exc) {

		 CLogger::GetLogger()->Log(" <EXCEPTION>: COutputFileCreator::GetStringNodesGFEM " + std::string(exc.what()));
	 }

	 return strReturn;
}

/**
 * Method to compose a message with a defined format
 * @return: result of the operation, KO or OK
 */
std::string COutputFileCreator::GetStringNode2Node3CoG() {

	std::string strReturn = STRING_EMPTY;

	 try {

		 ListStringData *lstGFEmNodes = CCalculations::GetCalculations()->GetNode2Node3CoGString();

		 for(ListStringData::iterator itList = lstGFEmNodes->begin(); itList != lstGFEmNodes->end(); itList++) {

			 strReturn += (*itList);
		 }
	 }
	 catch(std::exception &exc) {

		 CLogger::GetLogger()->Log(" <EXCEPTION>: COutputFileCreator::GetStringNodesGFEM " + std::string(exc.what()));
	 }

	 return strReturn;
}

/**
 * Method to compose a message with a defined format
 * @return: result of the operation, KO or OK
 */
std::string COutputFileCreator::GetStringKINEMATIC_COUPLING_COG_DFEM_1D2D() {

	std::string strReturn = STRING_EMPTY;

	 try {

		 strReturn = CCalculations::GetCalculations()->GetStringKINEMATIC_COUPLING_COG_DFEM_1D2D();
	 }
	 catch(std::exception &exc) {

		 CLogger::GetLogger()->Log(" <EXCEPTION>: COutputFileCreator::GetStringNodesGFEM " + std::string(exc.what()));
	 }

	 return strReturn;

}

/**
 * Method to compose a message with a defined format
 * @return: result of the operation, KO or OK
 */
std::string COutputFileCreator::GetT3D2_ABAQUS() {
	std::string strReturn = STRING_EMPTY;

	 try {

		 strReturn = CCalculations::GetCalculations()->GetStringT3D2_ABAQUS();
	 }
	 catch(std::exception &exc) {

		 CLogger::GetLogger()->Log(" <EXCEPTION>: COutputFileCreator::GetT3D2_ABAQUS " + std::string(exc.what()));
	 }

	 return strReturn;
}

/**
 * Method to compose a message with a defined format
 * @return: result of the operation, KO or OK
 */
std::string COutputFileCreator::GetSOLIDSECTION() {
	std::string strReturn = STRING_EMPTY;

	 try {

		 strReturn = CCalculations::GetCalculations()->GetSOLIDSECTION_Cards();
	 }
	 catch(std::exception &exc) {

		 CLogger::GetLogger()->Log(" <EXCEPTION>: COutputFileCreator::GetSOLIDSECTION " + std::string(exc.what()));
	 }

	 return strReturn;
}

/**
 * Method to compose a message with a defined format
 * @return: result of the operation, KO or OK
 */
std::string COutputFileCreator::GetSurfaceWithT3D2Elements() {
	std::string strReturn = STRING_EMPTY;

	 try {

		 strReturn = CCalculations::GetCalculations()->GetSurfaceWithT3D2Elements();
	 }
	 catch(std::exception &exc) {

		 CLogger::GetLogger()->Log(" <EXCEPTION>: COutputFileCreator::GetSurfaceWithT3D2Elements " + std::string(exc.what()));
	 }

	 return strReturn;
}

/**
 * Method to compose a message with a defined format
 * @return: result of the operation, KO or OK
 */
std::string COutputFileCreator::GetSurfaceDFEMNodes() {
	std::string strReturn = STRING_EMPTY;

	 try {

		 strReturn = CCalculations::GetCalculations()->GetSurfaceDFEMNodes() + "\n";
	 }
	 catch(std::exception &exc) {

		 CLogger::GetLogger()->Log(" <EXCEPTION>: COutputFileCreator::GetSurfaceDFEMNodes " + std::string(exc.what()));
	 }

	 return strReturn;
}

/**
 * Method to compose a message with a defined format
 * @return: result of the operation, KO or OK
 */
std::string COutputFileCreator::GetSurfaceNSET() {
	std::string strReturn = STRING_EMPTY;

	 try {

		 strReturn = CCalculations::GetCalculations()->GetSurfaceNSET() + "\n";
	 }
	 catch(std::exception &exc) {

		 CLogger::GetLogger()->Log(" <EXCEPTION>: COutputFileCreator::GetSurfaceNSET " + std::string(exc.what()));
	 }

	 return strReturn;
}


/**
 * Method to compose a message with a defined format
 * @return: result of the operation, KO or OK
 */
std::string COutputFileCreator::GetT3D2ElementBetweenGFEMProjectedNodes() {
	std::string strReturn = STRING_EMPTY;

	 try {

		 strReturn = CCalculations::GetCalculations()->GetT3D2ElementBetweenGFEMProjectedNodes();
	 }
	 catch(std::exception &exc) {

		 CLogger::GetLogger()->Log(" <EXCEPTION>: COutputFileCreator::GetT3D2ElementBetweenGFEMProjectedNodes " + std::string(exc.what()));
	 }

	 return strReturn;
}

/**
 * Method to compose a message with a defined format
 * @return: result of the operation, KO or OK
 */
std::string COutputFileCreator::GetTIE_CARD() {
	std::string strReturn = STRING_EMPTY;

	 try {

		 strReturn = CCalculations::GetCalculations()->GetTIECard() + "\n";
	 }
	 catch(std::exception &exc) {

		 CLogger::GetLogger()->Log(" <EXCEPTION>: COutputFileCreator::GetTIE_CARD " + std::string(exc.what()));
	 }

	 return strReturn;
}


/**
 * Method to compose a message with a defined format
 * @return: result of the operation, KO or OK
 */
std::string COutputFileCreator::GetKINEMATIC_COUPLING_1_2_CARD() {

	std::string strReturn = STRING_EMPTY;

	 try {

		 strReturn = CCalculations::GetCalculations()->GetKINEMATIC_COUPLING_1_2_CARD();
	 }
	 catch(std::exception &exc) {

		 CLogger::GetLogger()->Log(" <EXCEPTION>: COutputFileCreator::GetKINEMATIC_COUPLING_1_2_CARD " + std::string(exc.what()));
	 }

	 return strReturn;
}

/**
 * Method to compose a message with a defined format
 * @return: result of the operation, KO or OK
 */
std::string COutputFileCreator::GetKINEMATIC_COUPLING_CoG_DFEM_1D_2D() {

	std::string strReturn = STRING_EMPTY;

	 try {

		 strReturn = CCalculations::GetCalculations()->GetKINEMATIC_COUPLING_CoG_DFEM_1D_2D() + "\n";
	 }
	 catch(std::exception &exc) {

		 CLogger::GetLogger()->Log(" <EXCEPTION>: COutputFileCreator::GetKINEMATIC_COUPLING_CoG_DFEM_1D_2D " + std::string(exc.what()));
	 }

	 return strReturn;
}

/**
 * Method to compose a message with a defined format
 * @return: result of the operation, KO or OK
 */
std::string COutputFileCreator::GetConnNodesProjGFEM1D2DToCoG(int dTypeToShow) {

	std::string strReturn = STRING_EMPTY;

	 try {

		 strReturn = CCalculations::GetCalculations()->GetConnTwoNodesProjGFEM1D2DToCoG(dTypeToShow) + "\n";
	 }
	 catch(std::exception &exc) {

		 CLogger::GetLogger()->Log(" <EXCEPTION>: COutputFileCreator::GetConnNodesProjGFEM1D2DToCoG " + std::string(exc.what()));
	 }

	 return strReturn;
}

/**
 * Method to compose a message with a defined format
 * @return: result of the operation, KO or OK
 */
std::string COutputFileCreator::GetEQUATION_CARD_NODE3_NODE2_GFEM_2D2D() {

	std::string strReturn = STRING_EMPTY;

	 try {

		 strReturn = CCalculations::GetCalculations()->GetEQUATION_CARD_NODE3_NODE2_GFEM_2D2D();
	 }
	 catch(std::exception &exc) {

		 CLogger::GetLogger()->Log(" <EXCEPTION>: COutputFileCreator::GetEQUATION_CARD_NODE3_NODE2_GFEM_2D2D " + std::string(exc.what()));
	 }

	 return strReturn;
}

/**
 * Method to compose a message with a defined format
 * @param strPathFileName
 * @return: result of the operation, KO or OK
 */
bool COutputFileCreator::CreateMainDFEMFile(std::string strPathFile, std::string strDFEMFileName) {

	bool breturn = RESULT_KO;
	std::string strLine = STRING_EMPTY;
	std::string strName = STRING_EMPTY;
	std::string strExtension = STRING_EMPTY;
	ofstream DFEMFile;
	std::stringstream ss;

	 std::string strPathSourceDFEMFile = CGlobalDFEMReader::GetCGlobalDFEMReader()->getPathRoot() + strDFEMFileName;
	 CGlobal::Replace(strPathSourceDFEMFile, "/cygdrive/c/", "C:/");
	 cout << "DFEM File: " << strPathSourceDFEMFile << endl;

	 try {

		std::string strSuffix = CGlobal::GetGlobal()->getIniFile().get("OUTPUT_FILES").get("dfem_main_file_modified");
		CGlobal::GetGlobal()->GetFileNameAndExtension(strDFEMFileName, strName, strExtension);
		std::string strNewFileName = strName + strSuffix;

		if(strExtension != STRING_EMPTY) {

			 strNewFileName = strNewFileName + "." + strExtension;
		}

		std::string strFullPathFile =  strPathFile + strNewFileName;
		ListStringData *lstFile = CGlobal::GetGlobal()->ReadFile(strPathSourceDFEMFile , true);

		if( m_pThis->OpenFile(strFullPathFile, DFEMFile)) {

			for(ListStringData::iterator itLine = lstFile->begin(); itLine != lstFile->end(); itLine++) {

				std::string strLine = (*itLine);

				if(CGlobal::GetGlobal()->StartsWithPattern((*itLine), BEGIN_ASSEMBLY)) {

					ss << "** INTEGRATION GFEM-DFEM \n*INCLUDE,  input=." + CGlobal::GetGlobal()->getIniFile().get("DATA_DIRECTORIES").get("output_files")
																		   + CGlobal::GetGlobal()->getIniFile().get("OUTPUT_FILES").get("part") + "\n**\n**\n";
					ss << (*itLine) + "\n**\n**\n";

					ss <<  "** INTEGRATION GFEM-DFEM \n*INCLUDE, input=."
							+ CGlobal::GetGlobal()->getIniFile().get("DATA_DIRECTORIES").get("output_files")
							+ CGlobal::GetGlobal()->getIniFile().get("OUTPUT_FILES").get("instance")
							+ "\n*INCLUDE, input=." + CGlobal::GetGlobal()->getIniFile().get("DATA_DIRECTORIES").get("output_files")
							+ CGlobal::GetGlobal()->getIniFile().get("OUTPUT_FILES").get("assembly") + "\n**\n";



				} else if(CGlobal::GetGlobal()->StartsWithPattern((*itLine), END_ASSEMBLY)) {

					ss << (*itLine) + "\n**\n**\n";

					ss <<  "** INTEGRATION GFEM-DFEM \n*INCLUDE, input=."
							+ CGlobal::GetGlobal()->getIniFile().get("DATA_DIRECTORIES").get("output_files")
							+ CGlobal::GetGlobal()->getIniFile().get("OUTPUT_FILES").get("material") + "\n**\n**\n**";
				}
				else {
					ss << (*itLine) + "\n";
				}



			}

			m_pThis->AppendLine(DFEMFile, ss.str());
		}

		m_pThis->CloseFile(DFEMFile);




	 }
	 catch(std::exception &exc) {

		 CLogger::GetLogger()->Log(" <EXCEPTION>: COutputFileCreator::GreateMainDFEMFile " + std::string(exc.what()));
	 }

	 return breturn;
}
