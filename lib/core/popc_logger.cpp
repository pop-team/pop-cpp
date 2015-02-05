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
#include <unistd.h>


int popc_logger(LOGLEVEL level, const char* file, int line, const char* function, const char *format,...) {
    static const char* LOG_LEVEL_PREFIX[__LAST__] = {
        "DEBUG",
        "INFO ",
        "CORE ",
        "WARN ",
        "ERROR"
    };

    // Check if message level in higher than our threshold (hard-coded for now)
    // TODO: Implement different logging levels
    if(level < __DEBUG__)
        return 0;

    // Use file name without path to avoid having the full user path in logs
    const char *basename = strrchr(file, '/');
    if(basename==NULL)
        basename=file;
    else basename += 1;

    char *tmp=getenv("POPC_TEMP");
    char logfile[256];
    if(tmp!=NULL) {
        // note: we need to log in diferent files for each user
        // to avoid that root or any other user locks the log files
        sprintf(logfile,"%s/popc.%s.log", tmp, getenv("USER"));
    } else {
        sprintf(logfile, "/tmp/popc.%s.log", getenv("USER"));
    }


    // Time
    time_t rawtime;
    time(&rawtime);
    const tm* timeinfo = localtime (&rawtime);
    char dd[20];
    strftime(dd, sizeof(dd), "%Y-%m-%d %H:%M:%S", timeinfo);

    char msg[512];
    va_list ap;
    va_start(ap, format);
    vsprintf(msg, format, ap);
    va_end(ap);

    // Print the message to stderr or stdout
    if(level >= __CORE__)
        fprintf(stderr, "%s %5d %s %s (%s:%d %s)\n", dd, getpid(), LOG_LEVEL_PREFIX[level], msg, basename, line, function);
    else if(level >= __INFO__)
        fprintf(stdout, "%s\n", msg);

    // Print the message to file
    FILE *f=fopen(logfile,"a");
    if(f==NULL) {
        fprintf(stderr, "ERROR: Impossible to open log file %s\n", logfile);
        return 1;
    }
    fprintf(f, "%s %5d %s %s (%s:%d %s)\n", dd, getpid(), LOG_LEVEL_PREFIX[level], msg, basename, line, function);
    fclose(f);
    return 0;
}
