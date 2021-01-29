#include "port.h"
#include <cstdlib>
#define VALID_SIZE 2
/** Constractor with an object from class string as input
 * param pattern : The string we obtain from the rules
 * Init List of father class Field inorder to init properly
 **/
Port::Port(String pattern): Field(pattern, PORT){
}
/** Recieves an object of String class and sat the correct value
    in place.
 * param val : the rule we are currently checking
 * return : returns true if rule values were sat correctly
 			and false otherwise.
 **/
bool Port::set_value(String val) 
{
	String* splitted_strings;
	size_t size = 0;
	val.split("-", &splitted_strings, &size);
	/* Check if Valid port size */
	if (size != VALID_SIZE)
	{
		if (size != 0)
		{
			delete[] splitted_strings;
		}
		return false;
	}
	
	range[0] = splitted_strings[0].to_integer();
	range[1] = splitted_strings[1].to_integer();

	delete[] splitted_strings;
	
	if(range[0] > range[1])
	{
		return false;
	}
	else
	{
		return true;
	}
}

/** Recieves an object of String class , checks if the
	value are matched correctly.
 * param val : the rule we are currently checking
 * return : returns true if rule values matched correctly
 			and false otherwise.
 **/
bool Port::match_value(String val) const 
{
	int port_val = val.to_integer();
	if((range[0] <= port_val) && (port_val <= range[1])){
	return 1;
	}
	else{
		return 0;
	}
}