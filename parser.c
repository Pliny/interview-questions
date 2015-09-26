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
 *  Validate a text file. Make sure all brackets are properly closed.
 *  Brackets are '[]' '()' '{}' '<>'
 *
 */

#include <stdio.h>
#include <stdbool.h>

enum {
	OPEN = 0,
	CLOSE
};

/* static int cnt = 12345678; */
static int cnt;

const char const brackets[4][2] =  { { '[', ']' }, { '{', '}' },  { '(', ')' }, { '<', '>' } };

bool is_open_bracket(char c)
{
	int i;
	int size = sizeof(brackets)/sizeof(brackets[0]);

	for (i = 0; i != size; ++i) {
		if(brackets[i][OPEN] == c) {
			return true;
		}
	}
	return false;
}

bool proper_closing_bracket(char c, char open_bracket)
{
	int i;
	int size = sizeof(brackets)/sizeof(brackets[0]);

	for (i = 0; i != size; ++i) {
		if(brackets[i][OPEN] == open_bracket && brackets[i][CLOSE] == c) {
			return true;
		}
	}
	return false;
}

bool bad_bracket(char c, char open_bracket)
{
	int i;
	int size = sizeof(brackets)/sizeof(brackets[0]);

	for (i = 0; i != size; ++i) {
		if(brackets[i][OPEN] != open_bracket && c == brackets[i][CLOSE]) {
			return true;
		}
	}

	return false;
}

bool parse(FILE *fp, char bracket)
{
	static int ok = true;
	int c;

	while(ok && (c = fgetc(fp)) != EOF) {
		if(bad_bracket(c, bracket)) {
			ok = false;
		}
		if(proper_closing_bracket(c, bracket)) {
			/* printf("%d: '%c'\n",cnt, (char)c); */
			cnt--;
			return true;
		}

		if(is_open_bracket((char)c)) {
			cnt++;
			/* printf("%d: '%c'\n",cnt, (char)c); */
			if(!parse(fp, (char)c)) {
				ok = false;
			}
		}
	}

	return ok;
}

int main(int argc, char *argv[])
{
	FILE *fp;
	int ret = 0;

	cnt = 0;

	fp = fopen(argv[1], "r");

	if(!parse(fp, '\0') || cnt != 0) {
		fprintf(stderr, "ERROR parsing at position: '%ld'\n", ftell(fp));
		ret = 1;
	}

	fclose(fp);

	return ret;
}

