/**
 *
 * Copyright (c) 2005-2012 POP-C++ project - GRID & Cloud Computing group, University of Applied Sciences of western Switzerland.
 * http://gridgroup.hefr.ch/popc
 *
 * @author Valentin Clement
 * @date 2012/04/13
 * @brief Declaration of the POPFileStrip class
 *
 *
 */

#ifndef _POPFILESTRIP_H
#define _POPFILESTRIP_H

#include <string>
#include "paroc_string.h"
#include "POPFileManager.ph"

/**
 * ViSaG : clementval
 * @author clementval
 * This class is used to save a path of nodes in the GRID and to reroute some specific message back to a specific node.
 */
class POPFileStrip : public POPBase {
public:
   POPFileStrip();  //POPFileStrip constructor
   ~POPFileStrip(); //POPFileStrip destructor

   //Inherited method to serialize the object
   virtual void Serialize(POPBuffer &buf, bool pack); 

private: 
	std::string path;
	std::string name;
};

#endif /* _POPFILESTRIP_H */
