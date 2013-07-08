/**
 *
 * Copyright (c) 2005-2012 POP-C++ project - GRID & Cloud Computing group, University of Applied Sciences of western Switzerland.
 * http://gridgroup.hefr.ch/popc
 *
 * @author Valentin Clement (clementval)
 * @date 2010/04/19
 * @brief Implementation of the exploration list for the resource discovery algorithm.
 *
 */
 
/* 
  Need refactoring to be in accordance: 
    POPC_ResourceDiscoveryExplorationList instead of ExplorationList
 */

#include "explorationList.h"
#include <stdio.h>
#include "timer.h"
#include <stdarg.h>
#include <string.h>


// Default constructor
ExplorationList::ExplorationList(){}

// destructor
ExplorationList::~ExplorationList(){}

// method to pass the object in the grid
void ExplorationList::Serialize(POPBuffer &buf, bool pack){
    if(pack){ // marshall
        int nElts;
        nElts = visitedNodes.size();
        
        // marshalling the size
        buf.Pack(&nElts,1);
        if(nElts > 0){
            explorationList::iterator i;
            
            // marshalling the neighbors
            for(i = visitedNodes.begin(); i != visitedNodes.end(); i++){
                buf.Pack(&(i->first), 1);
                neighborsList neighbors = i->second;
                int nNeighbors = neighbors.size();
                buf.Pack(&nNeighbors,1);
                neighborsList::iterator j;
                for(j = neighbors.begin(); j != neighbors.end(); j++){
                    buf.Pack(&(*j), 1);
                }
            }
        }
    }else{ // unmarshall
        int nElts, i, j;
        
        // unmarshalling the size
        buf.UnPack(&nElts, 1);
        
        // unmarshalling the neighbors
        for(i=0; i<nElts; i++){
            POPString nodeId;
            buf.UnPack(&nodeId, 1);
            int nNeighbors;
            buf.UnPack(&nNeighbors, 1);
            list<POPString> neighbors;
            for(j=0; j<nNeighbors; j++){
                POPString neighborId;
                buf.UnPack(&neighborId, 1);
                neighbors.push_back(neighborId);
            }
            addListNode(nodeId, neighbors);
        }
    }
}

// method used to add node's neighbors
void ExplorationList::addListNode(POPString nodeId,
                                  list<POPString> neighbors){
    explorationList::iterator i;
    explorationList::reverse_iterator j;
    explorationList::reverse_iterator k;
    int crtNeighborsPath = 0;
    
    i=visitedNodes.end();
    visitedNodes.insert(i, pair <POPString, list<POPString> >
                                     (nodeId, neighbors));

    
    for(j=visitedNodes.rbegin(); j != visitedNodes.rend(); j++){
        if(((*j).second).size() > 0){
            crtNeighborsPath++;
            k = j;
        }
    }
    
    if(crtNeighborsPath > NEIGHBORSPATH){
        (*k).second.clear();
    }
}

// method saying if a node is contained in the exploration list
bool ExplorationList::isIn(POPString nodeId){
    explorationList::iterator i;
    for(i = visitedNodes.begin(); i != visitedNodes.end(); i++){
        POPString crtNodeId = (*i).first;
        if(strcmp(crtNodeId.GetString(), nodeId.GetString()) == 0){	
            return true;
        }
        neighborsList neighbors = (*i).second;
        neighborsList::iterator j;
        for(j = neighbors.begin(); j!= neighbors.end(); j++){
            POPString nId = (*j);
				//Modified by clementval
				// old comparaison was strcmp(crtNodeId.GetString(), nId.GetString() but that was incorrect
            if(strcmp(nodeId.GetString(), nId.GetString()) == 0){
				//End of modification
                return true;
            }
        }
    }
    return false;
}
