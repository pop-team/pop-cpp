/**
 * File: popfile_grip.h
 * Author: Valentin Clement (clementval)
 * Description: Header declaration of POPFileGrip object. This object is used as a grip in read in background operation
 * Creation date: 03.25.2012
 * 
 * Change Log: 
 * Author		Date			Description
 * clementval	05.21.2012	Creation of this file
 */

 
#ifndef POPGRIP_H_INCLUDE
#define POPGRIP_H_INCLUDE

namespace popfile {

class POPFileGrip {
public:
	// Constructor of the POPFileGrip
	POPFileGrip();
	
	// Destrcutor of the POPFileGrip
	~POPFileGrip();

	// Get the size of the grip
	long get_size();
	// Set the size of the grip
	void set_size(long value);
	
	// Set the first POPFileReader
	void set_first_reader(int identifier);
	// Get the first POPFileReader
	int get_first_reader();
	
	// Set the order of this grip
	void set_order(int value);
	// Get the order of this grip
	int get_order();
	
	// Set the first byte read for this grip
	void set_first_read(long value);
	// Get the first byte read for this grip
	long get_first_read();

private:
	// The size of this grip
	long popfilegrip_size; 
	// The first byte read for this grip
	long popfilegrip_first_read;
	// The POPFileReader used at first call for this grip
	int popfilegrip_first_reader;
	// The order of this grip
	int popfilegrip_order;
	
	
	
};	
		
} // namespace popfile


#endif /* POPGRIP_H_INCLUDE */
