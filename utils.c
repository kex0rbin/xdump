#include <stdio.h>
#include "utils.h"
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
	if(byte >= 35 && byte <= 125){
		printf(GREEN "%02x   " RESET, byte);
	}else{
		printf("%02x   ", byte);
	}
}


char intToChar(int num){
	if(num >= 35 && num <= 125){
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

int check(int argc){
	if(argc == 2){
		return 1;
	}else{
		return 0;
	}

}