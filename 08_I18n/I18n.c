#include <stdio.h>
#include <math.h>
#include <string.h>
#include <libintl.h>
#include <locale.h>
#define _(STRING) gettext(STRING)

int main(int argc, char *argv[]) {
	setlocale(LC_ALL, "");
	bindtextdomain ("I18n", ".");
	textdomain ("I18n");
	
	int min = 0;
	int max = 101;
	int eq = 0;
	char responce[128];
	char r = '?';

	printf(_("Please, choose an integer from 1 to 100\n"));

	while(!eq) {

		printf(_("Is your digit greater, less or equal than %d?\n"), (min + max) / 2);
		scanf("%s", responce);
		
		if (!strcmp(responce, _("greater"))) r = '>';
		if (!strcmp(responce, _("less"))) r = '<';
		if (!strcmp(responce, _("equal"))) r = '=';
		
		switch (r) {
			case '>': min = (min + max) / 2; break;
			case '<': max = (min + max) / 2; break;
			case '=': printf(_("Thanks for playing!\n")); return 0; 	  
			default: printf(_("Please, type greater/less/equal\n")); break;
		}
		
		if ((min + max) / 2 == min || (min + max) / 2 == max) { 
			printf(_("Are you sure? Let's try playing again\n")); 
			eq = 1;
		}	
		
		r = '?';

	}

	return 0;
}

