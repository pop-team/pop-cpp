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

#define LOG_GENERIC(_log_level, _log_msg) {\
    std::stringstream ss;\
    ss<<_log_msg;\
    popc_logger(_log_level, __FILE__, __LINE__, __FUNCTION__, ss.str().c_str());\
}

#define LOG_DEBUG  (_log_msg) LOG_GENERIC(__DEBUG__  , _log_msg)
#define LOG_INFO   (_log_msg) LOG_GENERIC(__INFO__   , _log_msg)
#define LOG_CORE   (_log_msg) LOG_GENERIC(__CORE__   , _log_msg)
#define LOG_WARNING(_log_msg) LOG_GENERIC(__WARNING__, _log_msg)
#define LOG_ERROR  (_log_msg) LOG_GENERIC(__ERROR__  , _log_msg)

int popc_logger(LOGLEVEL level, const char *format,...);
int popc_logger(LOGLEVEL level, const char* file, int line, const char* function, const char *format);

#endif /* POPC_LOGGER */
