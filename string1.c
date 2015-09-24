#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define STRING_SIZE 128

void usage(char *cmd)
{
	fprintf(stderr, "Usage: \t%s \"A test string as argument\"\n", cmd);
}

bool parse_cli(char *string_out, int argv, char *argc[])
{
	if(argv == 2) {
		strncpy(string_out, argc[1], STRING_SIZE);
		return true;
	}
	else {
		fprintf(stderr, "ERROR: '%s' must have a string as argument.. Exiting\n", argc[0]);
		usage(argc[0]);
		return false;
	}
}

unsigned int get_size(char *test_string)
{
	char *beg = test_string;
	char *end = test_string;

	while(*(++end) != '\0') {
		/* find the address of the end of the string */
	}
	end--; /* so it points to the last valid character */

	return end - beg;
}

void swap(char *pb, char *pe)
{
	*pb = *pb ^ *pe;
	*pe = *pb ^ *pe;
	*pb = *pb ^ *pe;
}

char* reverse_string(char *test_string, int string_size)
{
	char *pb = test_string;
	char *pe = pb + string_size;

	while(pb < pe) {
		swap(pb, pe);
		pb++;
		pe--;
	}

	return test_string;
}

char* reverse_word_order(char *test_string)
{
	char *p = test_string;
	char *e = test_string;

	int string_size = get_size(test_string);

	reverse_string(test_string, string_size);

	do {
		++e;
		if(*e == ' ' || *e == '\0') {
			reverse_string(p, e-1-p);
			p = e+1;
		}
	} while(*e != '\0');

	return test_string;
}

int main(int argv, char *argc[])
{
	int ret_val = 0;
	char test_string[STRING_SIZE];

	if(!parse_cli(test_string, argv, argc)) {
		ret_val = 1;
		goto Exit;
	}

	printf("%s\n", test_string);

	reverse_word_order(test_string);

	printf("%s\n", test_string);

Exit:
	return ret_val;
}
