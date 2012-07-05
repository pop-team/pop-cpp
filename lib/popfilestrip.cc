/**
 * File : popfilestrip.cc
 * Author : Valentin Clement (clementval)
 * Description : Implementation of the POPFileStrip class
 * Creation date : 2012/04/13
 * 
 * Modifications : 
 * Authors		Date			Comment
 * clementval  2012/04/13  First implementation of this class
 */

#include "../include/popfilestrip.h"

using namespace std;

/**
 * POPFile : clementval
 * Constructor of the POPFileStrip class
 */
POPFileStrip::POPFileStrip(){}

/**
 * POPFile : clementval
 * Destructor of the POPFileStrip class
 */
POPFileStrip::~POPFileStrip(){}
   

/**
 * POPFile : clementval
 * Marshall or unmarshall the object to be sent over the network. 
 * Remark : This method is overwritten from the POPBase class
 * @param buf The POPBuffer to be used for the (un)marshalling
 * @param If true=masrhalling, if false=unmarshalling
 */
void POPFileStrip::Serialize(POPBuffer &buf, bool pack){
   if(pack){

   } else {
    
   }
}

