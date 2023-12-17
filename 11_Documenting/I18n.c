#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <libintl.h>
#include <locale.h>
#define _(STRING) gettext(STRING)

char roman[101][16] = {"0", "I", "II", "III", "IV", "V", "VI", "VII", "VIII", "IX", "X", "XI", "XII", "XIII", "XIV", "XV", "XVI", "XVII", "XVIII", "XIX", "XX", "XXI", "XXII", "XXIII", "XXIV", "XXV", "XXVI", "XXVII", "XXVIII", "XXIX", "XXX", "XXXI", "XXXII", "XXXIII", "XXXIV", "XXXV", "XXXVI", "XXXVII", "XXXVIII", "XXXIX", "XL", "XLI", "XLII", "XLIII", "XLIV", "XLV", "XLVI", "XLVII", "XLVIII", "XLIX", "L", "LI", "LII", "LIII", "LIV", "LV", "LVI", "LVII", "LVIII", "LIX", "LX", "LXI", "LXII", "LXIII", "LXIV", "LXV", "LXVI", "LXVII", "LXVIII", "LXIX", "LXX", "LXXI", "LXXII", "LXXIII", "LXXIV", "LXXV", "LXXVI", "LXXVII", "LXXVIII", "LXXIX", "LXXX", "LXXXI", "LXXXII", "LXXXIII", "LXXXIV", "LXXXV", "LXXXVI", "LXXXVII", "LXXXVIII", "LXXXIX", "XC", "XCI", "XCII", "XCIII", "XCIV", "XCV", "XCVI", "XCVII", "XCVIII", "XCIX", "C"};

void help() {
	printf(_("Usage: ./I18n [OPTIONS]\n"));
	printf(_("This program tries to guess an integer from 1 to 100 that you guessed\n\n"));
	printf(_("Arguments:\n"));
	printf(_("\t -r\t\tdisplay of numbers in the Roman system\n"));
	printf(_("\t--help\t\thelp message output\n\n"));
	printf(_("Functions:\n\n"));
	printf(_("\tint main(int argc, char *argv[])\n"));
	printf(_("\t\tthe main function that implements the game process\n\n"));
	printf(_("\tchar *to_roman(int num)\n"));
	printf(_("\t\tconverting arabic integers from 1 to 100 into roman\n\n"));
	printf(_("\tint from_roman(char *rom)\n"));
	printf(_("\t\tconverting roman integerss from 1 to 100 into arabic\n\n"));
	exit(0);
}

int from_roman(char *rom) {
	for(int i = 0; i <= 101; i++) {
		if(!strcmp(roman[i], rom)) return i;
	}

	return 0;
}

char *to_roman(int num) {
	return roman[num];
}

void ask(int is_roman, int min, int max) {
	if(is_roman)
		printf(_("Is your digit greater, less or equal than %s?\n"), to_roman((min + max) / 2));
	else
		printf(_("Is your digit greater, less or equal than %d?\n"), (min + max) / 2);

} 

int main(int argc, char *argv[]) {
	setlocale(LC_ALL, "");
	bindtextdomain ("I18n", ".");
	textdomain ("I18n");
	
	int min = 0;
	int max = 101;
	int eq = 0;
	char responce[128];
	char r = '?';
	int is_roman;

	if(argc == 1) {
		printf(_("Please, choose an integer from 1 to 100\n"));
                is_roman = 0;
	}
	else if(argc == 2) {
		if(!strcmp(argv[1], "--help")) help();
		if(!strcmp(argv[1], "-r")) { 
			printf(_("Please, choose an integer from I to C\n"));
			is_roman = 1;
		}
		else {
			printf(_("Unknown argument, please, read help:\n\n"));
			help();
		}
	}
	else {
		printf(_("Unknown arguments, please, read help:\n\n"));
		help();
	}

	while(!eq) {

		ask(is_roman, min, max);
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

