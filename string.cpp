#include "string.h"
#include <string.h>
#include <iostream>
#include <cstring>
#define IP_ADDRESS 4
#define IP_MAX_VAL 255
#define BYTE_SIZE 8
using namespace std;
/**helper functions declarations**/
int find_first_non_space(char *str);
int find_last_non_space(char *str,int last_element);
bool delimiter_exist(const char *delimiters,char letter);
/**  
*recieves an array of delimiters and a letter to check 
*returns true or false if the letter is a delimiter
**/

bool delimiter_exist(const char *delimiters,char letter){
	for(unsigned int i=0;i<strlen(delimiters);i++){
		if(letter == delimiters[i]){
			return true;
		}
	}
	return false;
}
/** recieves a pointer to array of chars  
 *returns the location of the first char that is not space in the array
**/
int find_first_non_space(char *str){
	int pointer = 0;
	char *tmp = str;
	while(*tmp == ' ' && tmp){
		tmp = tmp + 1;
		pointer = pointer + 1;
	}
	return pointer;
}
/** recieves a pointer to array of chars  
 *returns the location of the last char that is not space in the array
**/
int find_last_non_space(char *str,int last_element){
	char *tmp =	str;
	while(tmp[last_element] == ' '){
		last_element--;
	}
	return last_element;
}
 /**
  * Initiazation list of an empty string
 **/
String::String() : data(NULL) ,length(0){}
/**
  * Initiazation of a String object from other string object
**/
String::String(const String &str){
	length = str.length;	
	if (!length){
		data = NULL;
	}
	else{
		data = new char[length + 1];
		strncpy(data, str.data, length + 1);
	}
}
/**
  * Initiazation of a String object from given char of arrays
**/
String::String(const char *str){
	if (!str){
		String();
		return;
	}
	length = strlen(str);
	data = new char[length + 1];
	strncpy(data, str, length + 1);
}
/**
  * destructor of a class string object
**/
String::~String(){
	if (data){
		delete[] data;
	}
}
/**
 * Operator = of a class string object from other given String object
 * returns a pointer to this (the string object)
**/
String& String::operator=(const String &rhs)
{
	if(this == &rhs){
		return *this;
	}
	else{
		if (data != NULL){
			delete[] data;
		}
	}
	length = rhs.length;		
	if (!length){
		String();
	}
	else{
		data = new char[length + 1];
		strncpy(data, rhs.data, length + 1);
	}
	return *this;
}
/**
 * Operator = changes this from other given char of arrays
 * returns a pointer to this
**/
String& String::operator=(const char *str)
{
	if (!str){
		String();
		return *this;
	}
	if (data){
		delete[] data;
	}
	length = strlen(str);	
	data = new char[length + 1];
	strncpy(data, str, length + 1);
	data[length] = '\0';
	return *this;
}
/**
 * Returns true iff the contents of this equals to the
 * contents of rhs.
**/
bool String::equals(const String &rhs) const {
	if((length != rhs.length) || strncmp(data, rhs.data, length)){
		return false;
	}
	return true;
}
/**
 * Returns true iff the contents of this equals to rhs
**/
bool String::equals(const char *rhs) const 
{	
	if (!rhs || (length != strlen(rhs)) || strncmp(data, rhs, length)){
		return false;
	}
	return true;
}
/**
 * Splits this to several sub-strings according to delimiters.
 * Allocates memory for output.
 * If "output" is set to NULL, do not allocated memory, only
 * compute "size".
 * output will be pointer to array of pointers to string objects
 * size will be the size of the array of the pointers to string objects
 * meaning that size will be the number of the substrings.
**/
void String::split(const char *delimiters, String **output, size_t *size) const 
{	
	int  index = 0 , num_of_split_strs = 1;
	char Copy_array[length + 1];
	if (data == NULL){
		*size=0;
		return;
	}
	strncpy(Copy_array, data, length);
	Copy_array[length] = '\0';
	for (unsigned int i = 0; i < length; i++){
		if (delimiter_exist(delimiters,data[i])){
			num_of_split_strs++;
		}
	}
	*size = num_of_split_strs;
	if(output != NULL){
		*output = new String[num_of_split_strs];
		char *token = strtok(Copy_array,delimiters);
		while(token != NULL){
			(*output)[index] = String(token);
			index = index + 1;
			token = strtok(NULL,delimiters);
		}
	}
	return;
}
/**
 * Remove any leading or trailing spaces.
 * Does not change this.
 * returns a pointer to this
**/
String String::trim() const {
	int start_string = 0 , end_string = length - 1;
	if (data == NULL){
		String();
		return *this;
	}
	start_string = find_first_non_space(data);
	end_string = find_last_non_space(data,end_string);	
	if (start_string > end_string){
		String();
		return *this;
	}
	end_string = end_string + 1;
	char trimmed_data[end_string - start_string + 1];
	strncpy(trimmed_data, &data[start_string], end_string - start_string);  
	trimmed_data[end_string - start_string] = '\0';
	return String(trimmed_data);
}
/**
 * converting this to an integer. 
 * does not change this.
 * deleting the allocated memory of the substrings
 *Returns 0 on error or the value of the array of chars in this in success.
**/
int String::to_integer() const 
{
	
	int val_of_string = 0 , count = 0;
	String *output;
	size_t size = 0;
	split(".", &output, &size);
	int index = IP_ADDRESS - 1;
	if(size == IP_ADDRESS){ 
		while(index>=0){
			int val_of_substring = atoi(output[index].trim().data);
			if (!(val_of_substring <= IP_MAX_VAL) && (val_of_substring >= 0)){
				delete[] output;
				return 0; 
			}	
			val_of_string += val_of_substring<<(BYTE_SIZE*count);
			count = count + 1;
			index--;
		}
		delete[] output;
		return val_of_string;
	}	
	else{
		int val_of_substring = atoi(data);
		if(val_of_substring){
			delete[] output;
			return val_of_substring;
		}
		delete[] output;
	}
	return 0;
}
