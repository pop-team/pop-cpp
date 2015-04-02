/**
 *
 * Copyright (c) 2005-2012 POP-C++ project - GRID & Cloud Computing group, University of Applied Sciences of western Switzerland.
 * http://gridgroup.hefr.ch/popc
 *
 *
 * @author Valentin Clement
 * @date 2010/10/07
 * @brief This object is used to store a path to a specific object
 *
 *
 * UPDATES:
 * Authors      Date              Comment
 * clementval 2010/10/07  First declaration of this object
 * clementval 2010/10/22  Add doxygen comment
 *
 */

#ifndef _POP_WAYBACK_H
#define _POP_WAYBACK_H

#include <list>
#include <string>
#include "pop_base.h"

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
    std::string getAsString() const;      //Get the object as a formatted string value
    void insertNode(std::string nodeId);  //Insert a node a the end of the way back
    std::string getNextNode() const;      //Return the next node in the object
    void deleteNextNode();                 //Delete the next node in the object
    bool isLastNode() const;         //Check if it's the lasr node in the way back
    bool isEmpty() const;            //Check if the way back is empty


    //Inherited method to serialize the object
    virtual void Serialize(POPBuffer &buf, bool pack);

private:
    std::list<std::string> _lst_wb;   //List containing the path to a specific node

};

#endif
