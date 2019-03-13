#include "fillit.h"

/* hash function ??? */
/* a row of ints which cannot be sums of each other!!!
 * the ints are powers of 2 */
static int	check_piece(char *s)
{
//	if (s[0] OK && s[1] OK && s[2] OK && s[3] OK)
	if (s[0] == '#')
	{
		while (s
	}
}

static int	move_piece(char *ln16)
{
	int	i;
	int	j;
	int	shiftup;
	int	shiftleft;

	shiftup = 0;
	i = -1;
	while (ln16[++i])
	{
		/* check for empty rows */
		if (ln16[i] == '#')
			break;
	}
	if (i > SIDE)
		shiftup = (i / SIDE);
	shiftleft = SIDE;
	i = -1;
	/* check for empty positions to the left */
	while (++i < SIDE)
	{
		j = -1;
		while (++j < SIDE)
			if (ln16[i * SIDE + j] == '#' && j < shiftleft)
				shiftleft = j;
	}
	return (shiftup * SIDE + shiftleft);
}

int	save_piece(char *ln16, t_tetra **pieces)
{
	int	i;
	int	x;
	int	y;
	int	shift;

	shift = move_piece(ln16);
	check_piece(ln16);
	ln16 = ft_strcpy(ln16, ln16 + shift);
	i = LEN - 1;
	while (shift--)
		ln16[i--] = '.';
	i = -1;
	x = 0;
	y = 0;
	while (ln16[++i])
	{
		if (ln16[i] != '#' && ln16[i] != '.')
			return (0);
		(*pieces)->config[y][x++] = ln16[i];
		if ((i + 1) % 4 == 0)
		{
			x = 0;
			y++;
		}
	}
	free(ln16);
	return (1);
}
