/***********************************************************************************/
/*  Copyright 2009 WSL Institute for Snow and Avalanche Research    SLF-DAVOS      */
/***********************************************************************************/
/* This file is part of MeteoIO.
    MeteoIO is free software: you can redistribute it and/or modify
    it under the terms of the GNU Lesser General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    MeteoIO is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU Lesser General Public License for more details.

    You should have received a copy of the GNU Lesser General Public License
    along with MeteoIO.  If not, see <http://www.gnu.org/licenses/>.
*/
#include "IOExceptions.h"

IOException::IOException(const std::string& message, const std::string& position)
{
	if (position=="")
  {
		msg = "At unknown position: " + message;
	} else
  {
		msg = position + ": " + message;
	}
#ifdef LINUX
	void* tracearray[25]; //maximal size for backtrace: 25 pointers
	size_t tracesize = backtrace(tracearray, 25); //obtains backtrace for current thread
	char** symbols = backtrace_symbols(tracearray, tracesize); //translate pointers to strings
	msg += "\n\n\033[01;30m**** backtrace ****\n"; //we use ASCII color codes to make the backtrace less visible/aggressive
	for (unsigned int ii=1; ii<tracesize; ii++)
		msg += "\tat " + string(symbols[ii]) + "\n";
	msg += "\033[0m"; //back to normal color
	free(symbols);
#endif

}

IOException::~IOException() throw(){
}


const char* IOException::what() const throw()
{
	return msg.c_str();
}

