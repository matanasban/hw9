#include "ip.h"
#include "field.h"
#include "port.h"
#include <iostream>
#include <cstring>
#define VALID_SIZE 2

/** Constractor with an object from class string as input
 * param pattern : The string we obtain from the rules
 * builds a new string class Object with generic type.
 **/
Field::Field(String pattern)
{
	this->type = GENERIC;
	this->pattern = pattern;
	
}

/** Constractor with an object from class string 
	and a type as input.
 * param pattern : The string we obtain from the rules
 * param type : the type of the rule.
 * builds a new string class Object with type and pattern.
 **/
Field::Field(String pattern, field_type type){
	this->pattern = pattern;
	this->type = type;
}

/** Destructor free's the memory
 **/
Field::~Field(){
}

/** Recieves the rule type.
 * returns the type o the rule 0 for ip 1 for port.
 **/
field_type Field::get_type() const{
	return type;
}


/** Recieves an object of String class , checks if the rule
	is a port rule or an ip rule and calls the right func.
 * param val : the rule we are currently checking
 * return : returns true if rule values were sat correctly
 			and false otherwise.
 **/
bool Field::set_value(String val) 
{
	if(type == PORT){
		int success_port = ((Port*)this)->set_value(val);
		return success_port;
	}
	if (type == IP)
	{
		int success_ip = ((Ip*)this)->set_value(val);
		return success_ip;
	}
	//didnt recieve valid ip or port.
	return false;
}


/** Recieves an object of String class , checks if the rule
	is a port rule or an ip rule and calls the right func.
 * param val : the rule we are currently checking
 * return : returns true if rule values matched correctly
 			and false otherwise.
 **/
bool Field::match_value(String val) const 
{
	if(type == PORT){
		int success_port = ((Port*)this)->match_value(val);
		return success_port;
	}
	if (type == IP)
	{
		int success_ip = ((Ip*)this)->match_value(val);
		return success_ip;
	}
	//didnt recieve valid ip or port.
	return false;
}




/** Recieves an object of String class , checks if the rule
	is a port rule or an ip rule and calls the right func.
 * param val : the rule we are currently checking
 * return : returns true if rule values were sat correctly
 			and false otherwise.
 **/
bool Field::match(String packet) 
{
	String* splitted_packets;
	String helper;
	String* rule_value_string;
	size_t splitted_numb = 0 , rule_value_string_numb = 0 ;
	bool value_equal = false;
	unsigned int i = 0;


	/* splitting packet by delimiter , */
	packet.split(",", &splitted_packets, &splitted_numb);
	if (splitted_numb == 0)
	{
		/* Failed to split */
		return false;
	} 
	
	/* Iterating all parts of String */
	for(i = 0; i < splitted_numb; i++)
	{	
		splitted_packets[i].split("=", &rule_value_string, &rule_value_string_numb);
		/* Skip the empty strings */
		if (rule_value_string_numb == 0)
		{
			continue;
		} 
		/* Number of sub strings has to be 2 - NAME and VALUE */
		if (rule_value_string_numb == VALID_SIZE)
		{
			pattern = pattern.trim();
			helper = rule_value_string[0].trim();
			if (pattern.equals(helper)){
				value_equal = match_value(rule_value_string[1].trim());
			}
		}
		delete[] rule_value_string;
	}
	delete[] splitted_packets;
	
	return value_equal;
}
