/**
 * Special header redefining mandatory function of the XMP runtime
 * These functions needs to be redefined without the GCC hack constructor/destructor
 *
 *
 *
 */

void _XMP_constructor(int argc, char** argv);
void _XMP_destructor();
