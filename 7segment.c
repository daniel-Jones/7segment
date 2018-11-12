/*
 * Copyright Daniel Jones <daniel@danieljon.es>
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.

 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <stdio.h>
#include <unistd.h>

/*
	A
	_
      F| |B
      G	-
      E| |C
	-
	D
	
 A 7 segment display (unsurprisingly) has 7 individual segments that can conveniently make 0-9 and A-F
 perfect for hexadecimal.
 The state of a single 7 segment character can also conveniently be stored in 8 bits (a byte, in C a char),
 almost as if these aren't coincidences (they're not).
*/

enum segments
{
	/* refer to the diagram to know which value represents which segment */
	SEG_A 	= 1 << 0,
	SEG_B 	= 1 << 1,
	SEG_C	= 1 << 2,
	SEG_D	= 1 << 3,
	SEG_E	= 1 << 4,
	SEG_F	= 1 << 5,
	SEG_G	= 1 << 6,
};

enum characters
{
	CHAR_ZERO	= SEG_A | SEG_B | SEG_C | SEG_D | SEG_E | SEG_F,
	CHAR_ONE	= SEG_B | SEG_C,
	CHAR_TWO	= SEG_A | SEG_B | SEG_D | SEG_E | SEG_G,
	CHAR_THREE	= SEG_A | SEG_B | SEG_C | SEG_D | SEG_G,
	CHAR_FOUR	= SEG_B | SEG_C | SEG_F | SEG_G,
	CHAR_FIVE	= SEG_A | SEG_C | SEG_D | SEG_F | SEG_G,
	CHAR_SIX	= SEG_A | SEG_C | SEG_D | SEG_E | SEG_F | SEG_G,
	CHAR_SEVEN	= SEG_A | SEG_B | SEG_C,
	CHAR_EIGHT	= SEG_A | SEG_B | SEG_C | SEG_D | SEG_E | SEG_F | SEG_G,
	CHAR_NINE	= SEG_A | SEG_B | SEG_C | SEG_D | SEG_F | SEG_G,
	CHAR_A		= SEG_A | SEG_B | SEG_C | SEG_E | SEG_F | SEG_G,
	CHAR_B		= SEG_C | SEG_D | SEG_E | SEG_F | SEG_G,
	CHAR_C		= SEG_A | SEG_D | SEG_E | SEG_F,
	CHAR_D		= SEG_B | SEG_C | SEG_D | SEG_E | SEG_G,
	CHAR_E		= SEG_A | SEG_D | SEG_E | SEG_F | SEG_G,
	CHAR_F		= SEG_A | SEG_E | SEG_F | SEG_G,
};

void
printdisplay(char segs)
{
	/* line 1 */
	printf("\t %c\n", (segs & SEG_A) ? '_' : ' ');
	/* line 2 */
	printf("\t%c %c\n", (segs & SEG_F) ? '|' : ' ',
			    (segs & SEG_B) ? '|' : ' ');
	/* line 3 */
	printf("\t %c\n", (segs & SEG_G) ? '-' : ' ');
	/* line 4 */
	printf("\t%c %c\n", (segs & SEG_E) ? '|' : ' ',
			    (segs & SEG_C) ? '|' : ' ');
	/* line 5 */
	printf("\t %c\n", (segs & SEG_D) ? '-' : ' ');
}

void
clear()
{

	printf("%s", "\033[5;0F");
	printf("%s", "\033[0J");
}

char hexcharacters[16] = {CHAR_ZERO, CHAR_ONE, CHAR_TWO, CHAR_THREE, CHAR_FOUR, CHAR_FIVE, CHAR_SIX, CHAR_SEVEN, CHAR_EIGHT, CHAR_NINE,
			  CHAR_A, CHAR_B, CHAR_C, CHAR_D, CHAR_E, CHAR_F};

int
main(void)
{
	for (int i = 0; i < 16; i++)
	{
		printdisplay(hexcharacters[i]);
		sleep(1);
		clear();
	}
}
