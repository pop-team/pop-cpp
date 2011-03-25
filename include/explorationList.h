/* 
UPDATES : 
Authors		Date			Comment
clementval	2010/04/19	All code added for the semester project begins with this comment //Added by clementval, ends with //End of add
clementval	2010/04/19	All code modified during the semester project begins with //Modified by clementval, ends with //End of modification	
clementval	2010/04/22	Modified the method IsIn. This method was not correctly implemented. The comparaison between string was wrong
*/

#ifndef _EXPLORATION_LIST_H
#define _EXPLORATION_LIST_H
#include <map>
#include <list>
#include <iterator>
#include <utility>
#include "../include/paroc_string.h"
#include "../include/paroc_base.h"
#define NEIGHBORSPATH 5

using namespace std;



// Type representing a list of nodeId.
typedef list<paroc_string> neighborsList;

// Type linking a nodeId (string) to a list of nodeId(neighborsList).
typedef map<paroc_string, neighborsList> explorationList;

/*
 *  Class representing a list of exploration of nodes. This class must inherit
 *  from POPBase to be passed in the network.
 */
class ExplorationList: public POPBase{
    public :
        // Default constructor
        ExplorationList();
        
        // Destructor
        ~ExplorationList();
        
        // Inherited method to serialize the object
        virtual void Serialize(POPBuffer &buf, bool pack);
        
        // Method used to add a list of nodes in the list
        void         addListNode(paroc_string nodeId, 
                                 list<paroc_string> neighbors);
        // Method indicating if a node (identified by its nodeId) is present
        // or not in the list
        bool         isIn(paroc_string nodeId);

    private :
        explorationList visitedNodes; // The exploration list of visited nodes
};

int explo_log(const char *format,...);
#endif
