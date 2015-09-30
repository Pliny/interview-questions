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
 *  Without using any libraries, determine which direction the stack moves
 *  when a new entry is placed.
 *
 */

#include <stdio.h>
#include <stdbool.h>

int * func1(void)
{
	int i;
	return  &i;
}

int stack_direction(void)
{
	int i;

	unsigned second_func_addr = (unsigned)(func1());
	unsigned first_func_addr = (unsigned)&i;

#if 0
	printf("1: 0x%0.8X 2: 0x%0.8X\n", first_func_addr, second_func_addr);
#endif

	return second_func_addr - first_func_addr;
}

int main(int argc, char *argv[])
{
	if(stack_direction() > 0) {
		printf("Stack moves UP the address space\n");
	}
	else {
		printf("Stack moves DOWN the address space\n");
	}

	return 0;
}
