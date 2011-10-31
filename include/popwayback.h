/*
File : popwayback.h
Author : Clement Valentin (clementval)
Description : This object is used to store a path to a specific object
Date of creation : 07/10/2010

Modifications :
------------------
Author      Date        Description
clementval  07/10/2010  First declaration of this object
clementval  22/10/2010  Add doxygen comment
*/

#ifndef _POPC_WAYBACK_H
#define _POPC_WAYBACK_H

#include <list>
#include <string>
#include "paroc_string.h"

/**
 * ViSaG : clementval
 * @author clementval
 * This class is used to save a path of nodes in the GRID and to reroute some specific message back to a specific node.
 */
class POPWayback : public POPBase {
public:
   POPWayback();  //POPWayback constructor
   ~POPWayback(); //POPWayback destructor
   
   //Operator
	const POPWayback & operator=(const POPWayback &x);

   //Specialized methods
   paroc_string getAsString() const;      //Get the object as a formatted string value
   void insertNode(paroc_string nodeId);  //Insert a node a the end of the way back
   paroc_string getNextNode() const;      //Return the next node in the object
   void deleteNextNode();                 //Delete the next node in the object
   const bool isLastNode() const;         //Check if it's the lasr node in the way back
   const bool isEmpty() const;            //Check if the way back is empty


   //Inherited method to serialize the object
   virtual void Serialize(POPBuffer &buf, bool pack); 

private: 
   std::list<paroc_string> _lst_wb;   //List containing the path to a specific node

};

#endif
