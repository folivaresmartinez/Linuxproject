/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Global.h
 * Author: fernando.olivares
 *
 * Created on 31 de enero de 2018, 8:43
 */

#ifndef GLOBAL_H
#define GLOBAL_H

#include <stddef.h>
#include <wchar.h>
#include <string>

#include "Connection.h"

#pragma GCC diagnostic ignored "-Wunused-variable"

#include <map>
#include <list>
#include <ctime>
#include "GFEMNode.h"
#include "DFEMNode.h"
#include "DFEMObject.h"
#include "Segment.h"

#include "CQUAD4Node.h"
#include "CTRIA3Node.h"
#include "ConfigurationReader.h"


#ifdef WINDOWS
    #include <direct.h>
    #define GetCurrentDir _getcwd
#else
    #include <unistd.h>
    #define GetCurrentDir getcwd
 #endif


using namespace std;

class CConnection;
class CVector3D;
class CCoordinate3D;
class CGFEMNodesDistance;
class CSHELLSection;
class CELSETSection;
class CELEMENTSection;
class CDFEMGroup;
class CInstance;


#ifndef USLONG
#define USLONG               							unsigned long
#endif

#define ONE_FILE										1
#define MANY_FILES										2

#define FORMAT_1										"FORMAT_1"
#define FORMAT_2										"FORMAT_2"

#define RESULT_OK                      	 				true
#define RESULT_KO                       				false
#define UNDEFINED                       				-1
#define STRING_EMPTY                    				""
#define NULL_CHAR                       				'\0'
#define ULONG                           				unsigned long


#define TYPE_CBEAM                             			0
#define TYPE_CROD                         				1

#define PART_0                             				0
#define PART_1                             				1

#define INFINITE										9999999999
#define ZERO                            				0
#define SZERO                            				"0"
#define ONE                             				1
#define TWO                             				2
#define THREE                             				3
#define FOUR                             				4

//********************************************************************************************************************************************
//Defines of file sections

#define GRID                    						"GRID"
#define CQUAD4											"CQUAD4"
#define CTRIA3											"CTRIA3"
#define CBEAM											"CBEAM "
#define CROD											"CROD "

#define NODE                    						"*NODE"
#define NODE_LOW                						"*Node"
#define COMMENTS                    					"**"
#define DETAIL1D2D                 						",,,"
#define SHELL                    						"*SHELL SECTION,"
#define ELSET                    						"*ELSET,"
#define ELEMENTS                    					"*ELEMENT,"
#define ELEMENTS_LOW                  					"*Element,"

#define INSTANCE                    					"*Instance,"
#define INSTANCE_UPP                   					"*INSTANCE,"
#define NAME                    						"name="
#define NAME_UPP                   						"NAME="
#define PART                    						"part="

#define ELSET_NAME                    					"ELSET="

#define BEGIN_ASSEMBLY									"*Assembly,"
#define END_ASSEMBLY									"*End Assembly"
#define INCLUDE											"*Include,"

#define PART_DFEM										"*Part, name="

//********************************************************************************************************************************************

#define	TYPE_1D2D										1
#define	TYPE_2D2D										2

#define	TYPE_DFEM_1D									1
#define	TYPE_DFEM_2D									2
#define	TYPE_GFEM_1D									3
#define	TYPE_GFEM_2D									4


//********************************************************************************************************************************************
//********************************************************************************************************************************************
//Defines of types
typedef pair <int, int> 								PairNodes;


typedef std::list<std::list<std::string> *>				DataMatrixDFEM1D2D;

typedef std::list<int>									ListIntegerData;
typedef std::list<float>								ListFloatData;
typedef std::list<std::string>							ListStringData;
typedef std::list<CConnection *>						ListConnections;
typedef std::list <PairNodes *> 						ListPairNodes;
typedef std::list<CGFEMNode *>							ListGFEMNodes;
typedef std::list<CDFEMNode *>							ListDFEMNodes;

typedef std::map <std::string, CSegment *> 				MapSegments;
typedef std::map<int, CGFEMNode *>						MapGFEMNodes;
typedef std::map<std::string, CDFEMNode *>				MapDFEMNodes;
typedef std::map<std::string, CDFEMObject *>			MapDFEMObjects;

typedef std::map<int, ListStringData>					MapGFEMData;
typedef std::map<std::string, ListStringData>			MapDFEMData;
typedef std::map<int, CGridNode*>						MapGRIDData;
typedef std::map<int, CCQUAD4Node*>						MapCQUAD4Data;
typedef std::map<int, CCTRIA3Node*>						MapCTRIA3Data;

typedef std::map<std::string, CSHELLSection*>			MapSHELLSections;
typedef std::map<std::string, CELSETSection*>			MapELSETSections;
typedef std::map<std::string, CELEMENTSection*>			MapELEMENTSections;
typedef std::map<std::string, CInstance*>				MapInstances;

typedef std::map<std::string, CDFEMGroup*>				MapDFEMGroups;

//********************************************************************************************************************************************
//********************************************************************************************************************************************

class CGlobal 
{

private:
	CGlobal();

	/**
	 * Format Data
	 */
	std::string		m_FormatData;

	/**
	 * Main DFEM Data File
	 */
	std::string		m_MainDFEMFile;

	/**
	 * Singleton Instance
	 */
	static CGlobal	* m_pThis;

	/**
	 * m_OFFSET_NODE2_ID_GFEM value
	 */
	long m_OFFSET_NODE2_ID_GFEM;

	/**
	 * m_OFFSET_NODE3_ID_GFEM value
	 */
	long m_OFFSET_NODE3_ID_GFEM;

	/**
	 * m_Ini value
	 */
	mINI::INIStructure m_Ini;


	/**
	 * m_SOLIDSECTION_Tie value
	 */
	int m_SOLIDSECTION_Tie;

public:

	/**
	*   Function to create the instance of CGlobal class.
	*   @return singleton object of CGlobal class..
	*/
	static CGlobal* GetGlobal();

	/**
	* Getter/Setter of m_OFFSET_NODE2_ID_GFEM.
	**/
	static std::string getFormatData() { return m_pThis->m_FormatData; }
	static void setFormatData(std::string strFormat) { m_pThis->m_FormatData = strFormat; }

	/**
	* Getter/Setter of strMainDFEMFile.
	**/
	static std::string getMainDFEMFile() { return m_pThis->m_MainDFEMFile; }
	static void setMainDFEMFile(std::string strMainDFEMFile) { m_pThis->m_MainDFEMFile = strMainDFEMFile; }

	/**
	* Getter/Setter of m_OFFSET_NODE2_ID_GFEM.
	**/
	static long getOFFSET_NODE2_ID_GFEM() { return m_pThis->m_OFFSET_NODE2_ID_GFEM; }
	static void setOFFSET_NODE2_ID_GFEM(long offsetid) { m_pThis->m_OFFSET_NODE2_ID_GFEM = offsetid; }

	/**
	* Getter/Setter of m_OFFSET_NODE3_ID_GFEM.
	**/
	static long getOFFSET_NODE3_ID_GFEM() { return m_pThis->m_OFFSET_NODE3_ID_GFEM; }
	static void setOFFSET_NODE3_ID_GFEM(long offsetid) { m_pThis->m_OFFSET_NODE3_ID_GFEM = offsetid; }

	/**
	* Getter/Setter of m_Ini.
	**/
	static mINI::INIStructure getIniFile() { return m_pThis->m_Ini; }
	static void setIniFile(const mINI::INIStructure &ini) { m_pThis->m_Ini = ini; }

	/**
	* Getter/Setter of m_SOLIDSECTION_Tie.
	**/
	int getSolidsectionTie() const { return m_SOLIDSECTION_Tie; }
	void setSolidsectionTie(int solidsectionTie) { m_SOLIDSECTION_Tie = solidsectionTie; }

    virtual ~CGlobal();
    
public:

	/**
	 * Method that implement the operation to return Current DateTime in string format
	 */
    static const std::string    		CurrentDateTime();

	/**
	 * Method that implement the operation to print text with format
	 */
    static const int            		_vscprintf (const char * format, va_list pargs);


	/**
	 * Method that implement the operation to check if a file exist
	 */
    static bool							FileExist(const std::string& name);

	/**
	 * Method that implement the operation to return te current directory where the application is executed
	 */
    static std::string 					getCurrentDir();

	/**
	 * Method that implement the operation to replace a text into a string
	 */
    static bool 						Replace(std::string& strSource, const std::string& toSearch, const std::string& replaceStr);

	/**
	 * Method that implement the operation to get an item of a position into a list
	 */
    static std::string 					GetItem(std::list<std::string>lstDataList, int dPos);

	/**
	 * Method that implement the operation to trim left a string
	 */
    static std::string& 				Ltrim(std::string& s);

	/**
	 * Method that implement the operation to trim right a string
	 */
    static std::string& 				Rtrim(std::string& s);

	/**
	 * Method that implement the operation to trim a string
	 */
    static std::string& 				Trim(std::string& s);

	/**
	 * Method that implement the operation to check if a node exist in a list
	 */
    static bool							NodeInList(int dIdNode, ListIntegerData lstSource);

	/**
	 * Method that implement the operation to check if a node exist in a list
	 */
    bool 								NodeInList(std::string IdNode, ListStringData lstSource);

	/**
	 * Method that implement the operation to check if a string is a valid number
	 */
    static bool 						IsNumber(const std::string& strData);

	/**
	 * Method that implement the operation to pad a string with a char
	 */
    static void 						PadTo(std::string &str, const size_t num, const char paddingChar);

	/**
	 * Method that implement the operation to pad right a string with a char
	 */
    static std::string 					PadRight(std::string const& str, size_t dSize, const char paddingChar);

	/**
	 * Method that implement the operation to pad left a string with a char
	 */
    static std::string 					PadLeft(std::string const& str, size_t dSize, const char paddingChar);

	/**
	 * Method that implement the operation to Get the Node Type
	 */
    static int 							GetNodeType(int dType, std::string sNode);

	/**
	 * Method that implement the operation to Get Item At Position in a list
	 */
    static std::string					GetItemAtPosition( std::list<std::string> lstSource, int dPosition);

	/**
	 * Method that implement the operation to Get Item At Position in a list
	 */
    static int							GetItemAtPosition( std::list<int> lstSource, int dPosition);

	/**
	 * Method that implement the operation to check is a string Starts With Pattern
	 */
    static bool							StartsWithPattern(std::string strSource, std::string strPattern);

	/**
	 * Method that implement the operation to check the Number of Occurrences of a string into other string
	 */
    static int 							NumberOccurrences(std::string strSource, char chFind);

	/**
	 * Method that implement the operation to parse a string data line
	 */
    static ListStringData				ParseDataLine(std::string strGridLine, int dFieldSize, std::string strPattern);

	/**
	 * Method that implement the operation to parse a string data line
	 */
    static ListStringData 				ParseDataLine(std::string strDataLine, std::string strDelimiter);

	/**
	 * Method that implement the operation to parse a string data line
	 */
    static ListStringData 				ParseDataLine(std::string strDataLine, std::string strDelimiter, bool bCheckIsNumber = true);

    /**
	 * Method that implement the operation to parse a string data line
	 */
    static ListStringData *				ParseDataLine(std::string strDataLine, std::string strDelimiter, int NElements);

    /**
	 * Method that implement the operation to parse a string data line
	 */
    static ListStringData *				ParseDataLineNotNumber(std::string strDataLine, std::string strDelimiter, int NElements);

    /**
	 * Method that implement the operation to parse a string data line
	 */
    static std::list<std::string> *		ParseDataLine(std::string strDataLine, std::string strDelimiter, long NElements, bool NOZERO = false);

    /**
	 * Method that implement the operation to parse a string data line
	 */
    static std::list<int> *				ParseDataLineToInt(std::string strDataLine, std::string strDelimiter, long NElements, bool NOZERO = false);

    /**
	 * Method that implement the operation to parse a string data line
	 */
    static ListStringData 				ParseDataLineStrings(std::string strDataLine, std::string strDelimiter);

    /**
	 * Method that implement the operation to Find Associated To GFEM
	 */
    static CCQUAD4Node* 				FindAssociatedNodeToGFEM(int dIdGFEM, MapCQUAD4Data *mapCQUAD4, std::list<int> lstExcluded);

    /**
	 * Method that implement the operation to Find Associated To GFEM
	 */
    static CCTRIA3Node* 				FindAssociatedNodeToGFEM(int dIdGFEM, MapCTRIA3Data *mapCTRIA3, std::list<int> lstExcluded);

    /**
	 * Method that implement the operation to Show List Data
	 */
    static void							ShowListData(std::list<int> lstNodes);

    /**
	 * Method that implement the operation to Show List Data
	 */
    static void							ShowListData(ListStringData lstNodes);

    /**
	 * Method that implement the operation to Show List Data
	 */
    static void							ShowListData(ListGFEMNodes *lstGFEMNodes);

    /**
	 * Method that implement the operation to Show List Data
	 */
    static void 						ShowListData(ListDFEMNodes *lstDFEMNodes);

    /**
	 * Method that implement the operation to Show Node Data
	 */
	static void 						ShowNodeData(std::string strMessage, CGFEMNode *oNode);

    /**
	 * Method that implement the operation to Show Vector3D Data
	 */
	static void 						ShowVector3D(std::string strMessage, CVector3D *oVector);

    /**
	 * Method that implement the operation to Show Grid Node Data
	 */
	static void 						ShowGridNode(std::string strMessage, CGFEMNode *oGFEMNode, CGridNode *oNode);

    /**
	 * Method that implement the operation to Load OFFSET NODE2 NODE3
	 */
	static void 						LoadOFFSETNODE2_NODE3();

    /**
	 * Method that implement the operation to Swap two values
	 */
	static void							Swap(int &dValueA, int &dValueB) ;

    /**
	 * Method that implement the operation to Free Memory
	 */
	void 								FreeMemory(ListPairNodes *lstToFree);

    /**
	 * Method that implement the operation to check if an element Exist In List
	 */
	static bool							ExistInList(ListPairNodes *lstPairs, PairNodes *oPairNode);

    /**
	 * Method that implement the operation to print in a console a Map object
	 */
	static void 						ShowMap(MapDFEMObjects *oMap);

    /**
	 * Method that implement the operation to Get the Distance between two 3D points
	 */
	static float 						GetDistance(CCoordinate3D *coord1, CCoordinate3D *coord2);

    /**
	 * Method that implement the operation to check if two points are Adjacent Points
	 */
	static bool 						AdjacentPoitns(CCoordinate3D *coord1, CCoordinate3D *coord2);

    /**
	 * Method that implement the operation to Load T3D2 Element Between GFEM Projected Nodes
	 */
	static std::string 					LoadT3D2ElementBetweenGFEMProjectedNodes();

    /**
	 * Method that implement the operation to Create SOLID SECTIONCard
	 */
	static std::string 					Create_SOLIDSECTION_Card(int dTieValue);


    /**
	 * Method that implement the operation to Create a Surface T3D2
	 */
	static std::string 					Create_Surface_T3D2(int dTieValue);

    /**
	 * Method that implement the operation to Create a Surface DFEM Nodes
	 */
	static std::string 					Create_Surface_DFEM_Nodes(CConnection *oConnection);


    /**
	 * Method that implement the operation to Create a Surface NSET
	 */
	static std::string 					Create_Surface_NSET(CConnection *oConnection);

    /**
	 * Method that implement the operation to Create a TIE
	 */
	static std::string 					Create_TIE(CConnection *oConnection);

    /**
	 * Method that implement the operation to Read a File
	 */
	static ListStringData *				ReadFile(std::string strPath, bool WithComments = false);

    /**
	 * Method that implement the operation to Read a File
	 */
	static ListStringData * 			ReadFileOutput(std::string strPathFile);

    /**
	 * Method that implement the operation to Read a File
	 */
	static ListStringData * 					ReadFileAll(std::string strPath);

	/**
	 * Method that implement the operation to Get Unique Values in a list
	 */
	static ListStringData *				GetUniqueValues(ListStringData *lstData, std::string strPattern);

	/**
	 * Method that implement the operation to Get Nodes Detail in a 1D2D connection
	 */
	static DataMatrixDFEM1D2D * 		GetNodesDetail(ListStringData lstDFEMData, ListStringData *lstDataDetail, std::string strPattern, int dNumElements);

	/**
	 * Method that implement the operation to Find Segment DFEM Nodes
	 */
	static bool 						FindSegmentDFEMNodes(std::string IdSegment, DataMatrixDFEM1D2D *dataConnection, std::string &node1, std::string &node2);


	/**
	 * Method that implement the operation to Find a String
	 */
	static bool 						FindString(std::string strSource, std::string strFind);

	/**
	 * Method that implement the operation to Remove a String
	 */
	static void 						RemoveString(std::string &strSource, std::string strRemove);

	/**
	 * Method that implement the operation to Get Item that contain a string passed as parameter
	 */
	static std::string 					GetItemContain(ListStringData lstItems, std::string strFind);

	/**
	 * Method that implement the operation to Get ELSET Name
	 */
	static std::string 					GetELSETName(std::string strReadLine, std::string strDelimiter);

	/**
	 * Method that implement the operation to Get INSTANCE Name
	 */
	static std::string 					GetInstanceName(std::string strReadLine, std::string strDelimiter);

	/**
	 * Method that implement the operation to Get INSTANCE Part
	 */
	static std::string 					GetInstancePart(std::string strReadLine, std::string strDelimiter);


	/**
	 * Method that implement the operation to Create Kinematic Coupling CoG DFEM 1D2D
	 */
	static std::string 					Create_Kinematic_Coupling_CoG_DFEM_1D_2D(CConnection *oConnection, int dPart);

	/**
	 * Method that implement the operation to Get Nodes GFEM Output Data
	 */
	static std::string 					GetNodesGFEM_OutputData(CConnection *connection, ListIntegerData &lstNodesProcessed);

	/**
	 * Method that implement the operation to Get Node2 Node3 CoG Output Data
	 */
	static std::string 					GetNode2Node3CoG_OutputData(CConnection *connection, int dType, ListIntegerData &lstNodesProcessed);

	/**
	 * Method that implement the operation to
	 */
	ListStringData * 					ReadFileBetweenPatterns(std::string strPathFile, std::string strBeginSection, std::string strEndSection);

	/**
	 * Method that implement the operation to
	 */
	void 								GetTwoParts(std::string strSource, std::string strDelimiter, std::string &strPart1, std::string &strPart2);

	/**
	 * String to LowerCase
	 */
	void 								ToLower(std::string &strSource);

	/**
	 * String to LowerCase
	 */
	void 								ToUpper(std::string &strSource);

	/**
	 * Find DFEM Node in Map DFEM nodes
	 */
	ListStringData  					GetDFEMNode(MapDFEMData *mapDFEMData, std::string keyNode);

	/**
	 * Method that return separately Filename and extension
	 */
	bool  								GetFileNameAndExtension(std::string strFile, std::string &strName, std::string &strExtension);
};

#endif /* GLOBAL_H */

