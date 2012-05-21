/**
 * File: popfile_grip.h
 * Author: Valentin Clement
 * Description: Header declaration of POPFileGrip object. This object is used as a grip in read in background operation
 * Creation date: 2012/03/25
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

private:
	long popfilegrip_size; 
	int popfilegrip_first_reader;
	
	
};	
		
} // namespace popfile


#endif /* POPGRIP_H_INCLUDE */
