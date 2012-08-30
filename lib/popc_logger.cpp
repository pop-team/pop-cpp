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

int popc_logger(LOGLEVEL level, const char *format,...){
	char *tmp=getenv("POPC_TEMP");
	char logfile[256];
	if (tmp!=NULL) sprintf(logfile,"%s/popc_log",tmp);
	else strcpy(logfile, "/tmp/popc_log.log");
	FILE *f=fopen(logfile,"a");
	if (f==NULL) return 1;
	time_t t=time(NULL);
	fprintf(f, "%s", ctime(&t));
	va_list ap;
	va_start(ap, format);
	switch(level){
		case ERROR:
		fprintf(f, "%s", LEVEL_ERROR_PREFIX);	
		break;
		case DEBUG:
		fprintf(f, "%s", LEVEL_DEBUG_PREFIX);			
		break;
		case INFO:
		fprintf(f, "%s", LEVEL_INFO_PREFIX);	
		break;		
		case DEV:
		fprintf(f, "%s", LEVEL_DEV_PREFIX);			
		break;		
		case CORE:
		fprintf(f, "%s", LEVEL_CORE_PREFIX);							
		break;
	}
	vfprintf(f, format, ap);
	fprintf(f,"%s","\n");
	va_end(ap);
	fclose(f);
	return 0;
}