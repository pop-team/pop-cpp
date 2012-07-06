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

#define POPC_CORE(x) 	popc_logger x 	// Used for critical core error of the runtime
#define POPC_ERROR(x) 	popc_logger x	// Used for common error e.g. Resource Discovery error
#define POPC_DEBUG(x) 	popc_logger x	// Used for debugging purpose
#define POPC_INFO(x) 	popc_logger x 	// Used to print log for information purpose
#define POPC_DEV(x) 		popc_logger x	// Used to print log only for dev purpose

#include <stdarg.h>
int popc_logger(const char *format,...);

#endif /* POPC_LOGGER */