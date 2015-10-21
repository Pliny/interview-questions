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
 * Implement malloc with an aligned address.
 *   void * aligned_malloc(size, byte_alignment);
 * Do not worry about implications of freeing the memory.
 *
 */

#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>

#define STRING_SIZE 128

static void usage(char *cmd)
{
	fprintf(stderr, "Usage: \t%s <alloc-size-in-bytes> <alignment>\n", cmd);
}

static bool parse_cli(size_t *alloc_size, unsigned char *alignment, int argv, char *argc[])
{
	if(argv == 3) {
		*alloc_size = strtol((const char*)argc[1], NULL, 0);
		if(errno) {
			perror("ERROR getting 'alloc-size-in-bytes'");
			return false;
		}
		*alignment = strtol((const char*)argc[2], NULL, 0);
		if(errno) {
			perror("ERROR getting 'alignment'");
			return false;
		}
		return true;
	}
	else {
		fprintf(stderr, "ERROR: '%s' must have 2 numbers as argument.. Exiting\n", argc[0]);
		usage(argc[0]);
		return false;
	}
}

void * aligned_malloc(size_t alloc_size, unsigned char alignment)
{
	void * buf;
	size_t *buf_addr;

	buf = malloc(alloc_size+(1<<alignment));

	buf_addr = (size_t*)buf;
	buf_addr = (size_t*)(((size_t)buf_addr & (((size_t)-1)<<alignment)) + (1<<alignment));

	return (void*)buf_addr;
}

void unit_test(void *buf, size_t alloc_size)
{
	size_t i;

	unsigned char *buf_cast = (unsigned char *)buf;

	memset(buf, 0x5A, alloc_size);

	for(i=0; i != alloc_size; i++) {
		if(buf_cast[i] != 0x5A) {
			printf("malloc() test failed at '%lu'. Expected 0x5A, but got 0x%0.2X\n. Halting\n", i, buf_cast[i]);
			break;
		}
	}
	printf("Test PASSED!\n");
}

int main(int argv, char *argc[])
{
	int ret_val = 0;
	size_t alloc_size;
	unsigned char alignment;

	void *buf;

	if(!parse_cli(&alloc_size, &alignment, argv, argc)) {
		ret_val = 1;
		goto Exit;
	}

	buf = aligned_malloc(alloc_size, alignment);

	unit_test(buf, alloc_size);

Exit:
	return ret_val;
}
