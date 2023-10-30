#include <stdio.h>

int checksum(char *in, char *out) {
        FILE *input_bin = fopen(in, "rb");
        FILE *output_bin = fopen(out, "rb");

        unsigned char checksum_input = 0;
        unsigned char checksum_output = 0;
        while (!feof(input_bin) && !ferror(input_bin)) {
                checksum_input ^= fgetc(input_bin);
        }

        while (!feof(output_bin) && !ferror(output_bin)) {
                checksum_output ^= fgetc(output_bin);
        }

	if(checksum_input != checksum_output){
		return -1;
        }

	return 0;
}

int main(int argc, char *argv[]) {

	if(argc != 3) {
		printf("Args error, exit code 1\n");
		return 1;
	}
	
	FILE *inputfile;
	FILE *outputfile;
	char ch;

	if ((inputfile = fopen(argv[1], "r")) == NULL) {
		printf("Read error, exit code 2\n");	
		return 2;
	}

	if((outputfile = fopen(argv[2], "w")) == NULL) {
		printf("File create error, exit code 3\n");
		return 3;
	}

	while((ch = fgetc(inputfile)) != EOF) {
		fputc(ch, outputfile);
	}	

	if(fclose(inputfile) != 0) {
		printf("Input file close error, exit code 5\n");
		remove(argv[2]);
		return 5;
	}

	if(fclose(outputfile) != 0) {
		printf("Output file close error, exit code 6\n");
		remove(argv[2]);
		return 6;
	}
	
	if(checksum(argv[1], argv[2]) == -1) {
                printf("Input and output files not the same, exit code 4\n");
		remove(argv[2]);
		return 4;
	}

	if(remove(argv[1]) != 0) {
		printf("Removing input file error, exit code 7\n");
		return 7;
	}

	return 0;
}

