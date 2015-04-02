/**
 * File : allocobj.cc
 * Author : Tuan Anh Nguyen
 * Description : Implementation of the batch creation mechanism of parallel objects
 * Creation date : -
 *
 * Modifications :
 * Authors      Date            Comment
 */


#include "pop_allocobj.h"
#include "pop_interface.h"


pop_mutex pop_allocobj::lock;

pop_allocobj::pop_allocobj(int count) {
    lock.lock();
    holding=true;
    pop_interface::batchsize=count;
    pop_interface::batchindex=0;
}

void pop_allocobj::release() {
    if(holding) {
        pop_interface::batchsize=pop_interface::batchindex=0;
        holding=false;
        lock.unlock();
    }
}

pop_allocobj::~pop_allocobj() {
    release();
}
