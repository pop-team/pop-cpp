/**
 *
 * Copyright (c) 2005-2012 POP-C++ project - GRID & Cloud Computing group, University of Applied Sciences of western Switzerland.
 * http://gridgroup.hefr.ch/popc
 *
 * @author Valenti Clement
 * @date 2012/07/05
 * @brief Define a proper function and interface to produce log from the POP-C++ runtime.
 *
 *
 * Modifications
 * - Refactor the popc_logger, added a static array for error messages (LW Jan 2015)
 */

#ifndef POPC_LOGGER_H
#define POPC_LOGGER_H

#include <stdarg.h>

enum LOGLEVEL {
    __DEBUG__,
    //__DEV__, 
    __INFO__,
    __CORE__, 
    __WARNING__,
    __ERROR__, 
    __LAST__  // Only for dimensioning array
};

int popc_logger(LOGLEVEL level, const char *format,...);

#endif /* POPC_LOGGER */
