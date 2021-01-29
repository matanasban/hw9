#include <iostream>
#include <cstring>
#include "ip.h"
#include "port.h"
#include "input.h"
#define SOURCE_IP "src-ip"
#define DST_IP "dst-ip"
#define SRC_PORT "src-port"
#define DST_PORT "dst-port"


int main(int argc, char** argv){
	if(check_args(argc,argv)!=0){
		return 1;
	}

	
	String rule(argv[1]);
	String* splitted_strings;
	size_t size = 0;
	rule.split("=", &splitted_strings, &size);
	String rule_type = splitted_strings[0].trim();
	String rule_value =splitted_strings[1].trim();

	if ((rule_type.equals(String(SOURCE_IP))) || 
		(rule_type.equals(String(DST_IP)))){
			Ip ip_rule(rule_type);   
			ip_rule.set_value(rule_value);  

			parse_input(ip_rule);
	}	
	if((rule_type.equals(String(SRC_PORT)))||
		(rule_type.equals(String(DST_PORT)))){
		Port port_rule(rule_type);
		port_rule.set_value(rule_value);

		parse_input(port_rule);
	}
	delete[] splitted_strings;
}