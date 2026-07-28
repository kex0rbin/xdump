#include <stdio.h>
#include "converter.h"
int toInt(char c){
	if(c >= 97 && c <= 102){
		return c - 'a' + 10;
	}else if(c >= 65 && c <= 70){
		return c - 'A' + 10;
	}else if(c >= 48 && c <= 57){
		return c - '0';
	}else{
		return 0;
	}
}

void toChar(char c){
	printf("\\x");
	int a = c/16;
	int b = c%16;
	if(a >= 10){printf("%c",a+87);}else{printf("%d",a);}
	if(b >= 10){printf("%c",b+87);}else{printf("%d",b);}
	printf("");
}

char intToChar(int num){
	if(num >= 40 && num <= 122){
		char c = num;
		return c;
	}else{
		return '.';
	}	
}