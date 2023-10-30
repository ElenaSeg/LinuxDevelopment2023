#define _GNU_SOURCE
#include <string.h>
#include <dlfcn.h>

typedef int (*source)(const char* inputfile);

int remove(const char* inputfile) {
	if (strstr(inputfile, "PROTECT") != NULL) return 0;
	

	source s = (source) dlsym(RTLD_NEXT,"remove");
	return s(inputfile);
 }
