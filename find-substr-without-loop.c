/*
 * Interview Questions
 * Copyright (C) 2015  Dave S Desrochers <dave726@gmail.com>
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
 *
 * ==========================
 * = PROBLEM
 * ==========================
 * Without using loops (for() or while()), find out if a substring exists in a string.
 *
 * in: find_it(test_string, sub_str)
 * out: TRUE or FALSE
 *
 */

#include <stdbool.h>
#include <string.h>
#include <stdio.h>

#define STRING_SIZE 128

static char test_string[STRING_SIZE];
static char substr[STRING_SIZE];

void usage(char *cmd)
{
	fprintf(stderr, "Usage: \t%s \"A test string as argument\" \"A substring\"\n", cmd);
}

bool parse_cli(char *string_out, char *substr_out, int argv, char *argc[])
{
	if(argv == 3) {
		strncpy(string_out, argc[1], STRING_SIZE);
		strncpy(substr_out, argc[2], STRING_SIZE);
		return true;
	}
	else {
		fprintf(stderr, "ERROR: '%s' must have a string as argument.. Exiting\n", argc[0]);
		usage(argc[0]);
		return false;
	}
}

bool find_it(char *tp, char *sp)
{
	if(*sp == '\0') {
		return true;
	}
	else if (*tp == '\0') {
		return false;
	}
	else if(*tp == *sp) {
		sp++;
	}
	else {
		sp = substr;
		if(*tp == *sp) {
			sp++;
		}
	}
	return find_it(++tp, sp);
}

int main(int argv, char *argc[])
{
	int ret_val = 0;

	if(!parse_cli(test_string, substr, argv, argc)) {
		ret_val = 1;
		goto Exit;
	}

	printf("Is '%s' in '%s'? Lets find out.\n", test_string, substr);

	if(find_it(test_string, substr)) {
		printf("FOUND!\n");
	}
	else {
		printf("Not Found :( \n");
	}


Exit:
	return ret_val;
}
