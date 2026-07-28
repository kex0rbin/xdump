/*
	Script developed by kex0rbin
	A simple tool for hexdump files
	
*/
#include <stdio.h>
#include <stdlib.h>
#include "converter.h"

#define GREEN "\x1b[32;1m"
#define RESET "\x1b[0m"

#define HELP_FILE "hx tool: Put the name of the file as the second argument. You can use arguments\n hx <file> <lines>"
#define INVALID_ARGUMENTS "hx tool: To many arguments.\n"
#define F_LINE "Offset\t00   01   02   03   04   05   06   07   08   09   0A   0B   0C   0D   0E   0F\t   Decoded Text\n\n"
#define ERROR_FILE "hx tool: File not found.\n"
#define INVALID_INPUT "hx tool: Invalid number! (Second argument).\n"

void print_string(char *str);
void print_byte(int byte);
void header(){
	printf(F_LINE);
}

int main(int argc, char *argv[]){
	if(argc <= 1){
		printf(HELP_FILE);
		return 1;
	}

	if(argc >= 2){
		if(argc > 3){
			printf(INVALID_ARGUMENTS);
			return 1;
		}

		FILE *f = fopen(argv[1], "rb");
		if(f == NULL){
			printf(ERROR_FILE);
			return 1;
		}
		char string[17];
		int c, cont = 0;
		long addr = ftell(f);


		if(argc == 2){
			header();
			printf("%x\t", addr); 
			while((c = fgetc(f)) != EOF)
			{
				string[cont] = intToChar(c);
				print_byte(c);
				cont++;
				if(cont == 16){
					string[16] = '\0';
					print_string(string);
					addr = ftell(f);
					printf("\n");
					printf("%x\t", addr);
					cont = 0;
				}
			}
		}else{

			int limit = atoi(argv[2]);
			if(limit != 0 && limit > 0){
				header();
				printf("%x\t", addr); 
				int lines = 0;
				while((c = fgetc(f)) != EOF && lines <= limit)
				{
					string[cont] = intToChar(c);
					print_byte(c);
					cont++;
					if(cont == 16){
						string[16] = '\0';
						print_string(string);
						printf("\n");
						lines++;
						if(lines >= limit) break;
						addr = ftell(f);
						printf("%x\t", addr);
						cont = 0;
					
					}
				
				}
			}else{
				printf(INVALID_INPUT);
			}
			
		}
		printf("\n");
		fclose(f);
		return 0;
	}		

	return 0;
}

void print_string(char *str){
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

void print_byte(int byte){
	if(byte >= 40 && byte <= 122){
		printf(GREEN "%02x   " RESET, byte);
	}else{
		printf("%02x   ", byte);
	}
}

