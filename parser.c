#include <stdio.h>
//os
#define PE_HEADER  "Format: Portable Executable file (PE). Windows executable or dll.\n"
#define ELF_HEADER "Format: Executable and Linkable Format file (ELF). Linux executable.\n"
//compressed
#define RAR_HEADER "Format: Roshal Archive file (RAR). Compressed file.\n"
#define SZIP_HEADER "7-Zip Archive file (7z). Compressed file.\n"
#define GUNZIP_HEADER "Format: GNU Zip file (GZIP). Compressed file.\n"
#define ZIP_HEADER "Format: ZIP Archive File (ZIP). Compressed file.\n"
//media //7zip, gzip, jpeg,mp3,zip
#define PDF_HEADER "Format: Portable Document Format (PDF). Electronic document\n"
#define PNG_HEADER "Format: Portable Network Graphics (PNG). Image\n"
#define JPEG_HEADER "Format: Joint Photographic Experts Group (JPEG). Image.\n"
#define MP3_HEADER "Format: MPEG-1 Audio Layer III (MP3). Audio file.\n"
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
		case 0x37://7zip
			if((c = fgetc(f)) == 0x7A){
				if((c = fgetc(f)) == 0xBC){
					if((c = fgetc(f)) == 0xAF){
						return 4;
					}
				}
			}
			break;
		case 0x1F://gzip
			if((c = fgetc(f)) == 0x8B){
				return 5;
			}
			break;
		case 0x50://zip
			if((c = fgetc(f)) == 0x4B){
				if((c = fgetc(f)) == 0x03){
					if((c = fgetc(f)) == 0x04){
						return 6;
					}
				}
			}
			break;
		case 0x25://pdf
			if((c = fgetc(f)) == 0x50){
				if((c = fgetc(f)) == 0x44){
					if((c = fgetc(f)) == 0x46){
						return 7;
					}
				}
			}
			break;
		case 0x89://png
			if((c = fgetc(f)) == 0x50){
				if((c = fgetc(f)) == 0x4E){
					if((c = fgetc(f)) == 0x47){
						return 8;
					}
				}
			}
			break;
		case 0xFF://jpeg
			if((c = fgetc(f)) == 0xD8){
				if((c = fgetc(f)) == 0xFF){
					return 9;
				}
			}
			break;
		case 0x49://mp3
			if((c = fgetc(f)) == 0x44){
				if((c = fgetc(f)) == 0x33){
						return 10;
					
				}
			}
			break;
	}
	return 0;
}
void print_format(int n){
	switch(n){
	case 0:printf("Unknown or invalid format.\n");break;
		//os
	case 1:printf(PE_HEADER);break;
	case 2:printf(ELF_HEADER);break;
		//compressed files
	case 3:printf(RAR_HEADER);break;
	case 4:printf(SZIP_HEADER);break;
	case 5:printf(GUNZIP_HEADER); break;
	case 6:printf(ZIP_HEADER);break;
		//media
	case 7:printf(PDF_HEADER);break;
	case 8:printf(PNG_HEADER);break;
	case 9:printf(JPEG_HEADER);break;
	case 10:printf(MP3_HEADER);break;
	default:printf("Unknown format or not added.\n");break;
	}
}

