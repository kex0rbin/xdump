/*
	Script developed by kex0rbin
	A simple tool for hexdump files
	
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "utils.h"


#define header() printf("Offset\t\t00   01   02   03   04   05   06   07   08   09   0A   0B   0C   0D   0E   0F\tDecoded Text\n\n")
#define FILE_NOT_FOUND " xdmp tool: File not found.\n"
#define FILE_NOT_SELECTED " xdmp tool: File not selected.\n"
#define HELP_FILE " xdmp tool: Select an option and the file.\n \t xdmp <option> <file>\n Uses:\n\t Hexdump:\txdmp d <file>\n\t\t\txdmp d <file> <lines>\n\n\t Strings:\txdmp s <file>\n\n\t File data:\txdmp f <file>\n\n\t Help:\t\txdmp h\n"
#define INVALID_INPUT " xdmp tool: Invalid number! (Third argument).\n"
#define INVALID_OPTION " xdmp tool: Put a valid option:\n\td for hexdump, s for extract strings, f for file data.\n"
#define INVALID_ARGUMENTS " xdmp tool: To many arguments.\n"
#define SHORT_STRING " xdmp tool: Write 3 letters at least.\n"
int read_headers(FILE *f);
void print_format(int n);
void file_data(FILE *f, char *buff);
void show_all(FILE *f);
void show_with_limits(FILE *f, int limit);
void show_strings(FILE *f, char *str, const int flag);

int main(int argc, char *argv[]){
	if(argc <= 1){printf(HELP_FILE);return 1;}
	if(argc > 4){printf(INVALID_ARGUMENTS);return 1;}

	if(strcmp(argv[1],"d")==0){
		if(check(argc) != 0){
			printf(FILE_NOT_SELECTED);
			return 1;
		}

		FILE *f = fopen(argv[2], "rb");
		if(f == NULL){
			printf(FILE_NOT_FOUND);
			return 1;
		}
		if(argc == 3){
			show_all(f);//hexdump without limits
		}else{
			int limit = atoi(argv[3]);
			if(limit > 0){
				show_with_limits(f,limit);//hexdump with limits
				printf("\n");
			}else{
				printf(INVALID_INPUT);
			}

		}
		fclose(f);
		return 0;
	}else if(strcmp(argv[1],"s")==0){
		if(check(argc) != 0){
			printf(FILE_NOT_SELECTED);
			return 1;
		}
		if(argc > 4){
			printf(INVALID_ARGUMENTS);
			return 1;
		}
		FILE *f = fopen(argv[2], "rb");
		if(f == NULL){
			printf(FILE_NOT_FOUND);
			return 1;
		}
		if(argc == 3){
		show_strings(f,"\0",0);//strings without word selected
		}else if(argc == 4){
			if(strlen(argv[3]) < 4){
				printf(SHORT_STRING);
			}else{
				show_strings(f,argv[3],1);
			}
		}

		fclose(f);
		return 0;
	}else if(strcmp(argv[1],"f")==0){
		if(check(argc) != 0){
			printf(FILE_NOT_SELECTED);
			return 1;
		}
		if(argc > 3){
			printf(INVALID_ARGUMENTS);
			return 1;
		}

		FILE *f = fopen(argv[2], "rb");
		if(f == NULL){
			printf(FILE_NOT_FOUND);
			return 1;
		}
		file_data(f,argv[2]);
		fclose(f);
		return 0;
	}else if(strcmp(argv[1],"h")==0){
		printf(HELP_FILE);
		return 0;
	}else{
		printf(INVALID_OPTION);
		return 1;
	}		
}//end main

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
				print_colored_byte(c);
				cont++;
				if(cont == 16 || ftell(f) == seek){
					string[cont] = '\0';
					print_colored_string(string);
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
	while((c = fgetc(f)) != EOF){
		string[cont] = intToChar(c);
		print_colored_byte(c);
		cont++;
		if(cont == 16){
			string[cont] = '\0';
			print_colored_string(string);
			printf("\n");
			lines++;
			if(lines >= limit) break;
			printf("%08x\t", ftell(f));
			cont = 0;	
		}
	}
}

void show_strings(FILE *f, char *str, const int flag){
	#define RED "\x1b[31m"
	#define RESET "\x1b[0m"
	int c, i=0;
	int cont = 0; char buff[4] = {'\0'};
	while((c = fgetc(f)) != EOF){
			if(c >= 32 && c <= 125){
				if(flag == 1){
					if(c == str[i]){
						printf(RED);
						i++;
					}else{
						printf(RESET);
						i=0;
					}
				}
				if(cont < 4){
					buff[cont] = c;

				}
				cont++;
				if(cont == 4){
					print_buff(buff);
				}
				if(cont > 4){
					printf("%c",c);
				}
			}else{
				if(cont >= 4){
					printf("\n");
				}
				cont = 0;
			}
		}
	printf("\n");			
}

void file_data(FILE *f, char *buff){
	printf("File name: %s\n", buff);
	//size
	rewind(f);
	fseek(f,0,SEEK_END);
	float conv = (float)ftell(f) /1024;
	printf("File size: %ld bytes. (%0.2f kb)\n", ftell(f), conv);
	//headers
	print_format(read_headers(f));
}