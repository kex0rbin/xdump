/*
	Script developed by kex0rbin
	A simple tool for hexdump files
	
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "converter.h"

#define GREEN "\x1b[32;1m"
#define RESET "\x1b[0m"

#define HELP_FILE " xdmp tool: Select an option and the file.\n \t xdmp <option> <file>\n Uses:\n\t Hexdump:\txdmp h <file>\n\t\t\txdmp h <file> <lines>\n\n\t Strings:\txdmp s <file>\n\n\t Help:\t\txdmp h\n"
#define INVALID_ARGUMENTS " xdmp tool: To many arguments.\n"
#define F_LINE "Offset\t\t00   01   02   03   04   05   06   07   08   09   0A   0B   0C   0D   0E   0F\tDecoded Text\n\n"
#define ERROR_FILE " xdmp tool: File not found or not selected.\n"
#define INVALID_INPUT " xdmp tool: Invalid number! (Third argument).\n"
#define INVALID_OPTION " xdmp tool: Put a valid option:\n\td for hexdump, s for extract strings.\n"
void print_string(char *str);
void print_byte(int byte);
void header(){
	printf(F_LINE);
}
void show_all(FILE *f);
void show_with_limits(FILE *p, int limit);

int main(int argc, char *argv[]){
	if(argc <= 1){printf(HELP_FILE);return 1;}

	if(argc >= 2){
		if(argc > 4){
			printf(INVALID_ARGUMENTS);
			return 1;
		}
		if(strcmp(argv[1],"d")==0){
			FILE *f = fopen(argv[2], "rb");
			if(f == NULL){
				printf(ERROR_FILE);
				return 1;
			}
			if(argc == 3){
				show_all(f);
			}else{
				int limit = atoi(argv[3]);
				if(limit > 0){
					show_with_limits(f,limit);
					printf("\n");
				}else{
					printf(INVALID_INPUT);
				}
				fclose(f);
				return 0;
			}

		}else if(strcmp(argv[1],"s")==0){
			if(argc > 3){
				printf(INVALID_ARGUMENTS);
				return 1;
			}
			printf(" We are working on this :D.\n");


			return 0;
		}else if(strcmp(argv[1],"h")==0){
			printf(HELP_FILE);
		}else{
			printf(INVALID_OPTION);
			return 1;
		}

	}		
}

void show_all(FILE *f){
		fseek(f,0,SEEK_END);
		long seek = ftell(f);
		rewind(f);

		char string[17];
		int c, cont = 0;
		header();
		printf("%08x\t", ftell(f)); 
		while((c = fgetc(f)) != EOF){
				string[cont] = intToChar(c);
				print_byte(c);
				cont++;
				if(cont == 16 || ftell(f) == seek){
					string[cont] = '\0';
					print_string(string);
					printf("\n");
					if(ftell(f) != seek) printf("%08x\t", ftell(f));
					cont = 0;
				}
		}

}

void show_with_limits(FILE *f, int limit){
		char string[17];
		int c, cont = 0;
		header();
		printf("%08x\t", ftell(f)); 
		int lines = 0;
		while((c = fgetc(f)) != EOF && lines <= limit){
			string[cont] = intToChar(c);
			print_byte(c);
			cont++;
			if(cont == 16){
				string[cont] = '\0';
				print_string(string);
				printf("\n");
				lines++;
				if(lines >= limit) break;
				printf("%08x\t", ftell(f));
				cont = 0;	
			}
				
		}

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
	if(byte >= 40 && byte <= 125){
		printf(GREEN "%02x   " RESET, byte);
	}else{
		printf("%02x   ", byte);
	}
}

