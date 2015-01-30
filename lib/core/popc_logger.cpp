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
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 * POP-C++ is developed by the GRID & Cloud Computing Group
 * http://gridgroup.hefr.ch
 *
 */

#include "popc_logger.h"
#include <stdio.h>
#include <stdlib.h> 
#include <string.h>
#include <time.h>

int popc_logger(LOGLEVEL level, const char *format, ...) {
    (void)level;
    (void)format;
     //TODO remove
     return 0;
}

int popc_logger(LOGLEVEL level, const char* file, int line, const char* function, const char *format,...) {
    static const char* LOG_LEVEL_PREFIX[__LAST__] = {
        "[DEBUG]",
        "[INFO]",
        "[CORE]",
        "[WARNING]",
        "[ERROR]"
    };

    // Check if message level in higher than our threshold (hard-coded for now)
    if(level < __DEBUG__)
        return 0;

    char *tmp=getenv("POPC_TEMP");
    char logfile[256];
    if(tmp!=NULL) {
        sprintf(logfile,"%s/popc_log",tmp);
    } else {
        strcpy(logfile, "/tmp/popc_log.log");
    }

    FILE *f=fopen(logfile,"a");
    if(f==NULL) {
        return 1;
    }
    time_t t=time(NULL);
    va_list ap;
    va_start(ap, format);

    // Print the message to file
    fprintf(f, "%s ",  LOG_LEVEL_PREFIX[level]);
    vfprintf(f, format, ap);
    fprintf(f, "(%s:%d %s)", file, line, function);
    fprintf(f, ", %s", ctime(&t));
    //no need to break line since ctime already does it
    //fprintf(f,"%s","\n");
    va_end(ap);
    fclose(f);
    return 0;
}
