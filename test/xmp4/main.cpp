/**
 *
 */

#include <unistd.h>
#include <stdio.h>
#include "pop_xmp_object.ph"

int main(int argc, char* argv[]) {
    printf("POP-C++ Test Case: XMP Support\n");

    // Declare and initialize two XMP process of type POPXMPObject
    POPXMPObject xmp;
    printf("Group object name is %s\n", xmp.get_class_name());
    xmp.initialize(2);

    xmp.execute_xmp_1();

    xmp[0].set_value(20);
    xmp[1].set_value(19);

    xmp.propagate_value(21);

    xmp.finalize();

    printf("POP-C++ Test Case: XMP Support finished\n");

    return 0;
}
