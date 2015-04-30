/**
 *
 * Copyright (c) 2005-2012 POP-C++ project - GRID & Cloud Computing group, University of Applied Sciences of western
 *Switzerland.
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

#ifndef POP_LOGGER_H
#define POP_LOGGER_H

#include <stdarg.h>
#include <sstream>

// Define here the min level of logging for Debug and Release modes
#ifndef NDEBUG
#define MIN_LOG_LEVEL \
    __DEBUG__  // Min level at which a message is logged in log file /tmp/popc.user.log. A lower level means more access
               // to the disk.
#define MIN_STDOUT_LEVEL __INFO__     // Min level at which the message is printed on stdout
#define MIN_STDERR_LEVEL __WARNING__  // Min level at which the message is printed on stderr
#else
#define MIN_LOG_LEVEL __INFO__
#define MIN_STDOUT_LEVEL __INFO__
#define MIN_STDERR_LEVEL __WARNING__
#endif

enum LOGLEVEL {
    __DEBUG__,
    __INFO__,
    __CORE__,
    __WARNING__,
    __ERROR__,
    __LAST__  // Only for dimensioning array
};

#define LOG_DEBUG(_log_msg, ...) \
    popc_logger_t(__DEBUG__, __FILE__, __LINE__, __FUNCTION__, NULL, _log_msg, ##__VA_ARGS__)
#define LOG_INFO(_log_msg, ...) popc_logger_t(__INFO__, __FILE__, __LINE__, __FUNCTION__, NULL, _log_msg, ##__VA_ARGS__)
#define LOG_CORE(_log_msg, ...) popc_logger_t(__CORE__, __FILE__, __LINE__, __FUNCTION__, NULL, _log_msg, ##__VA_ARGS__)
#define LOG_WARNING(_log_msg, ...) \
    popc_logger_t(__WARNING__, __FILE__, __LINE__, __FUNCTION__, NULL, _log_msg, ##__VA_ARGS__)
#define LOG_ERROR(_log_msg, ...) \
    popc_logger_t(__ERROR__, __FILE__, __LINE__, __FUNCTION__, NULL, _log_msg, ##__VA_ARGS__)

#define LOG_DEBUG_T(tag, _log_msg, ...) \
    popc_logger_t(__DEBUG__, __FILE__, __LINE__, __FUNCTION__, tag, _log_msg, ##__VA_ARGS__)
#define LOG_INFO_T(tag, _log_msg, ...) \
    popc_logger_t(__INFO__, __FILE__, __LINE__, __FUNCTION__, tag, _log_msg, ##__VA_ARGS__)
#define LOG_CORE_T(tag, _log_msg, ...) \
    popc_logger_t(__CORE__, __FILE__, __LINE__, __FUNCTION__, tag, _log_msg, ##__VA_ARGS__)
#define LOG_WARNING_T(tag, _log_msg, ...) \
    popc_logger_t(__WARNING__, __FILE__, __LINE__, __FUNCTION__, tag, _log_msg, ##__VA_ARGS__)
#define LOG_ERROR_T(tag, _log_msg, ...) \
    popc_logger_t(__ERROR__, __FILE__, __LINE__, __FUNCTION__, tag, _log_msg, ##__VA_ARGS__)

#define LOG_DEBUG_IF(_cond, _log_msg, ...)                                                         \
    if (_cond) {                                                                                   \
        popc_logger_t(__DEBUG__, __FILE__, __LINE__, __FUNCTION__, NULL, _log_msg, ##__VA_ARGS__); \
    }

int popc_logger_t(LOGLEVEL level, const char* file, int line, const char* function, const char* tag, const char* format,
                  ...);

#endif /* POPC_LOGGER */
