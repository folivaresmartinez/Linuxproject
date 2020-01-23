/*
 * OutputFileCreator.h
 *
 *  Created on: 13 nov. 2019
 *      Author: fernando.olivares
 */

#ifndef OUTPUTFILECREATOR_H_
#define OUTPUTFILECREATOR_H_

#include <string>


using namespace std;

class COutputFileCreator {

private:
	/**
	 * Private default constructor
	 */
	COutputFileCreator();

	/**
	 * Static object used in the singleton object
	 */
	static COutputFileCreator* m_pThis;

	/**
	 * m_PathFile value
	 */
	std::string m_PathFile;

public:

	/**
	 * Default class destructor.
	 */
	virtual ~COutputFileCreator();

	/**
	*   Function to return the instance of OutputFileCreator class.
	*   @return singleton object of OutputFileCreator class..
	*/
	static COutputFileCreator* GetOutputFileCreator();

	 /**
	  * Getter/Setter of the map GFEM.
	  **/
	std::string  getPathFile() {return m_PathFile;}
	void setPathFile(std::string strPath) {m_PathFile = strPath;}

	void 			CleanFile(std::string strPathFile);

	/**
	 * Close File Method
	 */
	bool 			CloseFile(ofstream &fileOpen);

	/**
	 * Open File Method
	 */
	bool 			OpenFile(std::string strPathFile, ofstream &fileOpen);


	/**
	 * Append Line to a text File
	 */
	bool 			AppendLine(ofstream &outputFile, std::string strLine);


	/**
	 * Method to create all output files
	 */
	bool 			CreateOutputFiles(std::string strPath);

	/**
	 * Method to create Part output file
	 */
	bool 			CreateFile_Part(std::string strPathFile);

	/**
	 * Method to create Instance output file
	 */
	bool 			CreateFile_Instance(std::string strPathFile);
	/**
	 * Method to create Assembly output file
	 */
	bool 			CreateFile_Assembly(std::string strPathFile);

	/**
	 * Method to create Material output file
	 */
	bool 			CreateFile_material(std::string strPathFile);

	/**
	 * Method to create new DFEM main File
	 */
	bool 			CreateMainDFEMFile(std::string strPathFile, std::string strPathFileName);


	/**
	 * Method to Get String Nodes GFEM
	 */
	std::string 	GetStringNodesGFEM();

	/**
	 * Method to Get String Node2 Node3 CoG
	 */
	std::string 	GetStringNode2Node3CoG();

	/**
	 * Method to Get String KINEMATIC COUPLING COG DFEM 1D2D
	 */
	std::string 	GetStringKINEMATIC_COUPLING_COG_DFEM_1D2D();

	/**
	 * Method to Get T3D2 ABAQUS
	 */
	std::string 	GetT3D2_ABAQUS();

	/**
	 * Method to Get SOLID SECTION
	 */
	std::string 	GetSOLIDSECTION();

	/**
	 * Method to Get Surface With T3D2 Elements
	 */
	std::string 	GetSurfaceWithT3D2Elements();

	/**
	 * Method to Get Surface DFEM Nodes
	 */
	std::string 	GetSurfaceDFEMNodes();

	/**
	 * Method to Get Surface NSET
	 */
	std::string 	GetSurfaceNSET();

	/**
	 * Method to Get T3D2 Element Between GFEM Projected Nodes
	 */
	std::string 	GetT3D2ElementBetweenGFEMProjectedNodes();

	/**
	 * Method to Get TIE CARD
	 */
	std::string 	GetTIE_CARD();

	/**
	 * Method to Get KINEMATIC COUPLING 1D2D CARD
	 */
	std::string 	GetKINEMATIC_COUPLING_1_2_CARD();

	/**
	 * Method to Get KINEMATIC COUPLING CoG DFEM 1D2D
	 */
	std::string 	GetKINEMATIC_COUPLING_CoG_DFEM_1D_2D();

	/**
	 * Method to Get Connection Nodes Proj GFEM 1D2D To CoG
	 */
	std::string 	GetConnNodesProjGFEM1D2DToCoG(int dTypeToShow);

	/**
	 * Method to Get EQUATION CARD NODE3 NODE2 GFEM 2D2D
	 */
	std::string 	GetEQUATION_CARD_NODE3_NODE2_GFEM_2D2D();

};

#endif /* OUTPUTFILECREATOR_H_ */
