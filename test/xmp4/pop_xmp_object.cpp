#include "pop_xmp_object.ph"
#include <stdio.h>

extern "C" {
#include "test.h"
}
POPXMPObject::POPXMPObject() {
    printf("REMOTE OBJECT: Created successfully (rank=%d)\n", get_rank());
    _XMP_constructor(0, NULL);
}

POPXMPObject::~POPXMPObject() {
    printf("REMOTE OBJECT: Destructor\n");
    _XMP_destructor();
}

void POPXMPObject::execute_xmp_1() {
    printf("REMOTE OBJECT: Execute XMP 1\n");
    // Call the C defined function
    xmp_function();
}

void POPXMPObject::set_value(int val) {
    printf("REMOTE OBJECT(%d): Set Value %d\n", get_rank(), val);
}

void POPXMPObject::propagate_value(int val) {
    printf("REMOTE OBJECT(%d): Propagate Value %d\n", get_rank(), val);
}
