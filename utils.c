#include <stdio.h>
#include "converter.h"
#define GREEN "\x1b[32;1m"
#define RESET "\x1b[0m"


void print_colored_string(char *str){
	char *c = str;
	while(*c != '\0'){
		if(*c != '.'){
			printf(GREEN "%c"RESET,*c);
		}else{
			printf("%c",*c);
		}
		c++;
	}
}

void print_colored_byte(int byte){
	if(byte >= 40 && byte <= 125){
		printf(GREEN "%02x   " RESET, byte);
	}else{
		printf("%02x   ", byte);
	}
}


char intToChar(int num){
	if(num >= 40 && num <= 122){
		char c = num;
		return c;
	}else{
		return '.';
	}	
}
void print_buff(char *buff){
	for (int i = 0; i < 4; i++){
		printf("%c", buff[i]);
	}
}