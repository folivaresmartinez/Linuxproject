/*
 * CAssociativityFile.h
 *
 *  Created on: 12 nov. 2019
 *      Author: NG82748
 */

#include "Global.h"


#ifndef ASSOCIATIVITYFILE_H_
#define ASSOCIATIVITYFILE_H_

/**
* Class that implement the functionality required to read an parse the Associativity files (csv files)
 */

 class CAssociativityFile {

public:
	/**
	 * Default contructor
	 */
	 CAssociativityFile();

	/**
	 * Default destructor
	 */
	 virtual ~CAssociativityFile();

private:

	/*
	 * List to store the data associated to the 1D2D Connections
	 */
	 ListConnections  *m_lstConnections1D2D;

	/*
	 * List to store the data associated to the 2D2D Connections
	 */
	 ListConnections  *m_lstConnections2D2D;

public:

	 /**
	  * Getter of the List 1D2D conections.
	  **/
	 ListConnections * GetConnections1D2D() { return m_lstConnections1D2D; }

	 /**
	  * Getter of the List 2D2D conections.
	  **/
	 ListConnections * GetConnections2D2D() { return m_lstConnections2D2D; }

};

#endif /* ASSOCIATIVITYFILE_H_ */
