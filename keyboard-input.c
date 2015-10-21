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
 * Given the following input from the CLI:
 *   "Hellll««oo« World"
 * Update the string in situ to contain:
 *   "Hello World"
 * In other words, use '«' as a backspace.
 *
 * '«' is "ALT-\". This is a UTF-8
 * character defined by the 2-byte value:
 * [0] = -62, [1] = -85
 *
 */

#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#define STRING_SIZE 128

static void usage(char *cmd)
{
	fprintf(stderr, "Usage: \t%s \"A test string with at least one '«' as argument\"\n", cmd);
}

static bool parse_cli(char *string_out, int argv, char *argc[])
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

static void process_input(char *input_string)
{
	char *p = input_string;
	char *i = input_string;

	while(*i != '\0') {
		if(*i != -62 && *(i+1) != -85) {
			*p = *i;
			p++;
		}
		else {
			p--;
			i++;
		}
		i++;
	}
	*p = '\0';
}

int main(int argv, char *argc[])
{
	int ret_val = 0;
	char test_string[STRING_SIZE];

	if(!parse_cli(test_string, argv, argc)) {
		ret_val = 1;
		goto Exit;
	}

	printf("ORIGINAL: %s\n", test_string);
	process_input(test_string);
	printf("MODIFIED: %s\n", test_string);

Exit:
	return ret_val;
}
