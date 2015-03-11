/**
 *
 * Copyright (c) 2005-2012 POP-C++ project - GRID & Cloud Computing group, University of Applied Sciences of western Switzerland.
 * http://gridgroup.hefr.ch/popc
 *
 * @author -
 * @date 2010/04/19
 * @brief Exploration list used in the resource discovery algorithm
 *
 *
 */

#ifndef _EXPLORATION_LIST_H
#define _EXPLORATION_LIST_H
#include <map>
#include <list>
#include <iterator>
#include <utility>
#include "paroc_string.h"
#include "paroc_base.h"
#define NEIGHBORSPATH 5


// Type representing a list of nodeId.
typedef std::list<std::string> neighborsList;

// Type linking a nodeId (string) to a list of nodeId(neighborsList).
typedef std::map<std::string, neighborsList> explorationList;

/*
 *  Class representing a list of exploration of nodes. This class must inherit
 *  from POPBase to be passed in the network.
 */
class ExplorationList: public POPBase {
public :
    // Default constructor
    ExplorationList();

    // Destructor
    ~ExplorationList();

    // Inherited method to serialize the object
    virtual void Serialize(POPBuffer &buf, bool pack);

    // Method used to add a list of nodes in the list
    void         addListNode(paroc_string nodeId,
                             std::list<paroc_string> neighbors);
    // Method indicating if a node (identified by its nodeId) is present
    // or not in the list
    bool         isIn(paroc_string nodeId);

private :
    explorationList visitedNodes; // The exploration list of visited nodes
};

int explo_log(const char *format,...);
#endif
