/*
 * CSVParser.h
 *
 *  Created on: 11 nov. 2019
 *      Author: NG82748
 */

#ifndef CSVREADER_H_
#define CSVREADER_H_

#include <list>
#include <string>
#include "Global.h"

using namespace std;

class CAssociativityFile;
class CConnection;

/**
 * Class that implement the functionality to read CSV files
 */
class CCSVReader {

private:
	/**
	 * Tie Area Value
	 */
	int m_TieArea;

	/**
	 * Path File to the file data to process
	 */
	std::string m_PathFile;

	/**
	 * Delimiter of the fields in each data line of the file
	 */
	std::string m_strDelimiter;

	/**
	 * Class to map the content csv file
	 */
	CAssociativityFile *m_AssociativityFile;

public:
	/**
	*   Funtion to create the instance of CSVReader class.
	*   @return singleton object of CCSVReader class..
	*/
	static CCSVReader* GetCSVReader();

	/**
	 * Set Method for Path member
	 */
	void setPathFile(std::string strPath) {m_PathFile = strPath;}

	/**
	 * Get Method for Path member
	 */
	std::string  getPathFile() {return m_PathFile;};

	/**
	 * Set Method for delimiter member
	 */
	void setDelimiter(std::string strDelimiter) {m_strDelimiter = strDelimiter;}

	/**
	 * Get Method for delimiter member
	 */
	std::string  getDelimiter() {return m_strDelimiter;};

	/**
	 * Default class destructor
	 */
	~CCSVReader();

	/**
	 * Method to load CSV Data File
	 * @param strPathFile
	 * @return: Result of the operation
	 */
	bool LoadFile(std::string strPathFile);

	/**
	 * Method to load CSV Data File with format 2 data
	 * @param strPathFile
	 * @return: Result of the operation
	 */
	bool LoadGlobalFile(std::string strPathFile);

	/**
	 * Method that return the AssociativityFile Loaded
	 * @return: AssociativityFile Loaded
	 */
	CAssociativityFile * GetAssociativityFile() { return m_AssociativityFile; }

	/**
	 * Method to set the AssociativityFile
	 * @param associativityFile: File to set
	 * @return: Result of the operation
	 */
	void SetAssociativityFile(CAssociativityFile *associativityFile) { m_AssociativityFile = associativityFile; }

	/**
	 * Getter/Setter of m_TieArea
	 */
	int getTieArea() const { return m_TieArea; }
	void setTieArea(int tieArea) { m_TieArea = tieArea; }


private:

	/**
	*    Default constructor for the CCSVReader class.
	*/
	CCSVReader();

	/**
	*   Singleton CCSVReader class object pointer.
	**/
	static CCSVReader* m_pThis;

	/**
	 * Method that store data readed
	 */
	bool StoreData(int dType, std::list<std::string> dataList, ListStringData *lstListNodes, DataMatrixDFEM1D2D *oDataMatrix);

	/**
	 * Process Data Read
	 */
	bool ProcessData(std::list<std::string> dataList, ListConnections *lstConnection, int dType, ListStringData *lstUniqueNodes, DataMatrixDFEM1D2D *dataMatrix);


	/**
	 * Add GFEM Nodes to MAP GEFEM
	 */
	bool AddGFEMNodes(std::list<std::string> dataList, MapGFEMNodes *mapGFEMNodes, int dType, int dTieArea);

	/**
	 * Add DFEM Nodes to MAPDEFEM
	 */
	bool AddDFEMNodes(std::list<std::string> dataList, MapDFEMNodes *mapDFEMNodes, int dType, int dTieArea);

	/**
	 * Create MapSegments object
	 */
	bool CreateSegments(ListStringData *lstSegments, MapSegments *mapSegments);

};

#endif /* CSVREADER_H_ */
