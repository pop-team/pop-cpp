/**
 *
 * Copyright (c) 2005-2012 POP-C++ project - GRID & Cloud Computing group, University of Applied Sciences of western Switzerland.
 * http://gridgroup.hefr.ch/popc
 *
 * @author Tuan Anh Nguyen
 * @date 2005/01/01
 * @brief Implementation of the batch creation mechanism of parallel objects, used by POP-C++ runtime
 *
 */

#ifndef POP_ALLOCOBJ_H
#define POP_ALLOCOBJ_H
#include <pop_mutex.h>

/**
 * @class pop_message_header
 * @author Tuan Anh Nguyen
 * @brief Implementation of the batch creation mechanism of parallel objects, used by POP-C++ runtime
 * Note : This class does not seem to be used so far
 */
class pop_allocobj {
public:
    pop_allocobj(int count);
    ~pop_allocobj();
    void release();

private:
    bool holding;
    static pop_mutex lock;
};

template<class T>
T * pnew(int np) {
    pop_allocobj t(np);
    return new T[np];
}
#endif
