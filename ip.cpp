#include "ip.h"
#include <cstring>
#include <iostream>
#define MAX_BITS 32 
#define MAX_HEXA 0xFFFFFFFF
#define VALID_SIZE 2

/** Constractor with an object from class string as input
 * param pattern : The string we obtain from the rules
 * Init List of father class Field inorder to init properly
 **/
Ip::Ip(String pattern): Field(pattern, IP){
}
/** Recieves an object of String class and sat the correct value
    in place.
 * param val : the rule we are currently checking
 * return : returns true if rule values were sat correctly
 			and false otherwise.
 **/
bool Ip::set_value(String val)
{	
	String* splitted_string;
	size_t string_size = 0;
	unsigned int bit_mask = 0;
	val.split("/", &splitted_string, &string_size);
	/* Check if input is a valid ip rule */
	if (( string_size  != VALID_SIZE ) && (string_size != 0))
	{
		delete[] splitted_string;
		return false;
	}
	/* get ip and mask ip */
	int ip = splitted_string[0].to_integer();
	/* int and not unsigned because we dont know for sure that
	   input is valid */
	 int prefix = MAX_BITS - splitted_string[1].to_integer();
	 delete[] splitted_string;
	
	/* Check if ip prefix is valid */
	if((prefix < 0) || (prefix > MAX_BITS)) {	
		return false;
	}
	if(prefix == MAX_BITS){
		bit_mask = MAX_HEXA;
	}
	if(prefix < MAX_BITS){
    	bit_mask = unsigned((1 << prefix) - 1);
	}
	/*change all bits after prefix into zero */
	low = ip & (~bit_mask);
	/* change all bits after prefix into one */
	high = ip | bit_mask;
	return true;
}
/** Recieves an object of String class , checks if the
	value are matched correctly.
 * param val : the rule we are currently checking
 * return : returns true if rule values matched correctly
 			and false otherwise.
 **/
bool Ip::match_value(String val) const 
{	String trimmed_value = val.trim();
	unsigned int value_to_check=(unsigned int)trimmed_value.to_integer();
	if((low <= value_to_check) && (value_to_check <= high)){
		return true;
	}
	return false;
}
