/**
 * File: popfile_grip.cpp
 * Author: Valentin Clement (clementval)
 * Description: Implementation of POPFileGrip object. A POPFileGrip is a grip to read data from read in background process.
 * Creation date: 05.12.2012
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

/**
 * Set the current order of the grip. Grip must be used in the order they have been taken
 * @param value The order of this grip
 */
void POPFileGrip::set_order(int value)
{
	popfilegrip_order = value;
}

/**
 * Get the current order of the grip.
 * @return The order of the grip in the get_read() method
 */
int POPFileGrip::get_order()
{
	return popfilegrip_order;	
}

/**
 * Get the size requested when calling the grip.
 * @return The size for this grip
 */
long POPFileGrip::get_size()
{
	return popfilegrip_size;
}

/**
 * Set the size of the grip. Set by read_in_background().
 * @param value	The Size for this grip
 */
void POPFileGrip::set_size(long value)
{
	popfilegrip_size = value;
}

/**
 * Set the first POPFileReader used for this grip.
 * @param identifier The identifer of the POPFileReader
 */	
void POPFileGrip::set_first_reader(int identifier)
{
	popfilegrip_first_reader = identifier;
}

/**
 * Get the identifier of the first POPFileReader used for this grip.
 * @return The identifier of the first POPFileReader
 */
int POPFileGrip::get_first_reader()
{
	return popfilegrip_first_reader;
}

/**
 * Set the first byte read for this grip.
 * @param value The location of the first byte read in the file
 */
void POPFileGrip::set_first_read(long value)
{
	popfilegrip_first_read = value;
}

/**
 * Get the first byte read for this grip.
 * @return The first byte read for this grip
 */
long POPFileGrip::get_first_read()
{
	return popfilegrip_first_read;
}