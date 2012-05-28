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
	POPFileGrip();
	~POPFileGrip();

	long get_size();
	void set_size(long value);
	
	void set_first_reader(int identifier);
	int get_first_reader();
	
	void set_order(int value);
	int get_order();
	
	void set_first_read(long value);
	long get_first_read();

private:
	long popfilegrip_size; 
	long popfilegrip_first_read;
	int popfilegrip_first_reader;
	int popfilegrip_order;
	
	
	
};	
		
} // namespace popfile


#endif /* POPGRIP_H_INCLUDE */
