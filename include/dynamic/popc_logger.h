/*
 * POP-C++ Version 2.0.3 
 *
 * Copyright (C) 2012 Grid & Cloud Computing Group, College of Engineering 
 * and Architecture of Fribourg, Switzerland
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 * POP-C++ is developed by the GRID & Cloud Computing Group 
 * http://gridgroup.hefr.ch
 *
 */

/**
 * File: popc_log.h
 * Author: Valentin Clement
 * Description: Define a proper macro and interface to produce log from the POP-C++ runtime. 
 * Creation date: 2012/07/05
 * 
 * Modifications :
 * Authors		Date			Comment
 * clementval	2012/07/05	First version of this header file. POPC_CORE, POPC_ERROR, POPC_DEBUG, popc_log
 * 
 */

#ifndef POPC_LOGGER_H
#define POPC_LOGGER_H

#include <stdarg.h>

enum LOGLEVEL {CORE, ERROR, DEBUG, DEV, INFO};

static const char* LEVEL_ERROR_PREFIX = "[ERROR]";
static const char* LEVEL_DEBUG_PREFIX = "[DEBUG]";
static const char* LEVEL_INFO_PREFIX = "[INFO]";
static const char* LEVEL_DEV_PREFIX = "[DEV]";
static const char* LEVEL_CORE_PREFIX = "[CORE]";

int popc_logger(LOGLEVEL level, const char *format,...);

#endif /* POPC_LOGGER */