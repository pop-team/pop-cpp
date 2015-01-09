/**
 *
 * Copyright (c) 2005-2012 POP-C++ project - GRID & Cloud Computing group, University of Applied Sciences of western Switzerland.
 * http://gridgroup.hefr.ch
 *
 * @author Valenti Clement
 * @date 2012/07/05
 * @brief Define a proper function and interface to produce log from the POP-C++ runtime.
 *
 *
 */

#ifndef POPC_LOGGER_H
#define POPC_LOGGER_H

#include <stdarg.h>

enum LOGLEVEL {__CORE__, __ERROR__, __DEBUG__, __DEV__, __INFO__};

static const char* LEVEL_ERROR_PREFIX = "[ERROR]";
static const char* LEVEL_DEBUG_PREFIX = "[DEBUG]";
static const char* LEVEL_INFO_PREFIX = "[INFO]";
static const char* LEVEL_DEV_PREFIX = "[DEV]";
static const char* LEVEL_CORE_PREFIX = "[CORE]";

int popc_logger(LOGLEVEL level, const char *format,...);

#endif /* POPC_LOGGER */
