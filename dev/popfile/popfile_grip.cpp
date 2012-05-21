/**
 * File: popfile_grip.cpp
 * Author: Valentin Clement
 * Description: Implementation of POPFileGrip object. A POPFileGrip is a grip to read data from read in background process.
 * Creation date: 2012/03/25
 * 
 * Change Log: 
 * Author		Date			Description
 * clementval	05.21.2012	Creation of this file
 */

#include "popfile_grip.h"


using namespace popfile;


/**
 * Constrcutor of POPFileGrip. Initialize internal information
 */
POPFileGrip::POPFileGrip()
{
	popfilegrip_size = 0;
	popfilegrip_first_reader = 0;
	popfilegrip_order = 0;
	popfilegrip_first_read = 0;
}


/**
 * Destructor of POPFileGrip
 */
POPFileGrip::~POPFileGrip()
{
	
}

void POPFileGrip::set_order(int value)
{
	popfilegrip_order = value;
}

int POPFileGrip::get_order()
{
	return popfilegrip_order;	
}

/**
 *
 */
long POPFileGrip::get_size()
{
	return popfilegrip_size;
}

/**
 *
 */
void POPFileGrip::set_size(long value)
{
	popfilegrip_size = value;
}

/**
 *
 */	
void POPFileGrip::set_first_reader(int identifier)
{
	popfilegrip_first_reader = identifier;
}

/**
 *
 */
int POPFileGrip::get_first_reader()
{
	return popfilegrip_first_reader;
}

void POPFileGrip::set_first_read(long value)
{
	popfilegrip_first_read = value;
}
long POPFileGrip::get_first_read()
{
	return popfilegrip_first_read;
}