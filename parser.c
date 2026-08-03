#include <stdio.h>
int read_headers(FILE *f){
	rewind(f);
	return 1;
}
void print_format(int n){
	if(n == 1){
		printf("conexion\n");
	}
}