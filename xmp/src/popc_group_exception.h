/**
 *
 * Copyright (c) 2005-2012 POP-C++ project - GRID & Cloud Computing group, University of Applied Sciences of western Switzerland.
 * http://gridgroup.hefr.ch/popc
 *
 * @author Valentin Clement
 * @date 2012/11/30
 * @brief Declaration of base POPC_Group_interface class. This class is the base class for interface-side of a group 
 *        parallel object. A group parallel object is a set of parallel object that can be called in a single or collective way.
 *
 *
 */

#include <exception>
#include <string.h>

class POPC_GroupException: public std::exception
{
public:
  POPC_GroupException(); 
  
  enum Cause { NOTINITIALIZED, NOTIMPLEMENTED, OUTOFGROUP, EMPTYGROUP }; 
  POPC_GroupException(Cause c) { _cause = c; }; 
  
  virtual const char* what() const throw() {
    std::string err_msg("POP-C++ Parallel Object Group Exception: "); 
    switch (_cause) {
      case NOTINITIALIZED:
        err_msg.append("The group is not initialized"); 
        break;
      case NOTIMPLEMENTED:
        err_msg.append("This method is not implemented yet"); 
        break;        
      case OUTOFGROUP:
        err_msg.append("Rank is out of the group"); 
        break;        
      case EMPTYGROUP:
        err_msg.append("Operation produced an empty group"); 
        break;                
    }
    return err_msg.c_str();
  }
  
private: 
  Cause _cause; 
};
