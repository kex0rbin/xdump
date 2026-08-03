#include <stdio.h>

#define PE_HEADER  "Format: Portable Executable file (PE). Windows executable or dll.\n"
#define ELF_HEADER "Format: Executable and Linkable Format file (ELF). Linux executable.\n"
#define RAR_HEADER "Format: Roshal Archive file (RAR). Compressed file.\n"
#define PDF_HEADER "Format: Portable Document Format (PDF). Electronic document\n"
#define PNG_HEADER "Format: Portable Network Graphics (PNG). Image\n"

int read_headers(FILE *f){
	rewind(f);
	int c = fgetc(f);
	switch(c){
		case 0x4D://windows-dll
			if((c = fgetc(f)) == 0x5A){
				return 1;
			}
			break;
		case 0x7F://linux-elf
			if((c = fgetc(f)) == 0x45){
				if((c = fgetc(f)) == 0x4C){
					if((c = fgetc(f)) == 0x46){
						return 2;
					}
				}
			}
			break;
		case 0x52://rar
			if((c = fgetc(f)) == 0x61){
				if((c = fgetc(f)) == 0x72){
					if((c = fgetc(f)) == 0x21){
						return 3;
					}
				}
			}
			break;
		case 0x25://pdf
			if((c = fgetc(f)) == 0x50){
				if((c = fgetc(f)) == 0x44){
					if((c = fgetc(f)) == 0x46){
						return 4;
					}
				}
			}
			break;
		case 0x89://png
			if((c = fgetc(f)) == 0x50){
				if((c = fgetc(f)) == 0x4E){
					if((c = fgetc(f)) == 0x47){
						return 5;
					}
				}
			}	
	}
	return 0;
}
void print_format(int n){
	switch(n){
	case 0:
		printf("Unknown or invalid format.\n");
		break;
	case 1:
		printf(PE_HEADER);
		break;
	case 2:
		printf(ELF_HEADER);
		break;
	case 3:
		printf(RAR_HEADER);
		break;
	case 4:
		printf(PDF_HEADER);
		break;
	case 5:
		printf(PNG_HEADER);
		break;
	default:
		printf("Unknown format or not added.\n");
		break;

	}
}

