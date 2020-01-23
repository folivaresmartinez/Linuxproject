//============================================================================
// Name        : Testproject_2.cpp
// Author      : Olivares
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================


#include <iostream>
#include <string>
#include <string.h>

#include "../Headers/AssociativityFile.h"
#include "../Headers/Calculations.h"
#include "../Headers/CSVReader.h"
#include "../Headers/DataFileLoader.h"
#include "../Headers/Global.h"
#include "../Headers/Logger.h"
#include "../Headers/OutputFileCreator.h"
#include "../Headers/GlobalDFEMReader.h"

using namespace std;


int main(int argc, char* argv[]) {

    if ( argc < 5) {
        // Tell the user how to run the program
    	std::cout << "Incorrect params number. We need 3 existing files to execute the application" << std::endl;
    	std::cout << "\t Usage: ./LinuxProject " << " [FORMAT] [CSV File] [GFEM File] [DFEM File]" << std::endl;

    	return 1;
    }

    std::cout << "Params:\n\t Format: " << argv[1] << " CSVFile =  " << argv[2] << " GFEM File =  " << argv[3] << " DFEM File =  " << argv[4]   <<  std::endl;

    bool bResult = RESULT_KO;
    int dType = std::stoi(argv[1]);


	try {

		std::string strPath = CGlobal::getCurrentDir();
		std::string strAbsolutePath = strPath + "/Resources/ConfigurationFile.ini";
		CLogger::GetLogger()->SetPath(strPath + "/Logs");

		if(dType == 2) {

			CGlobal::GetGlobal()->setFormatData(FORMAT_2);

			std::cout << "Params:\n\t CSVFile =  " << argv[2] << " GFEM File =  " << argv[3] << " DFEM File =  " << argv[4]   <<  std::endl;
			bool bResult = CDataFileLoader::GetDataFileLoader()->LoadGlobalDataFiles(strPath, argv[2], argv[3],argv[4]);

			if(bResult == false) return 0;

			CGlobal::GetGlobal()->setMainDFEMFile(argv[4]);

			CCalculations::GetCalculations()->Get1D2D_2D2D_GFEM_AssociatedData();
			CCalculations::GetCalculations()->Get1D2DAssociatedData();
			COutputFileCreator::GetOutputFileCreator()->CreateOutputFiles(strPath);
		}
		else {
			CGlobal::GetGlobal()->setFormatData(FORMAT_1);

			std::cout << "Params:\n\t CSVFile =  " << argv[2] << " BDF File =  " << argv[3] << " INPFile =  " << argv[4]   <<  std::endl;
			bool bResult = CDataFileLoader::GetDataFileLoader()->LoadDataFiles(strPath, argv[2], argv[3], argv[4]);

			if(bResult == false) return 0;

			CCalculations::GetCalculations()->Get1D2D_2D2D_GFEM_AssociatedData();

			CCalculations::GetCalculations()->Get1D2DAssociatedData();

			COutputFileCreator::GetOutputFileCreator()->CreateOutputFiles(strPath);

		}
	}
	catch(std::exception &exc) {
		CLogger::GetLogger()->Log("<EXCEPTION> Main: " + std::string(exc.what()));
	}


  return 0;
}



