#include "fillit.h"

/* hash function ??? */
/* bitwise ??? */
static void	check_piece(char *s)
{
	int	ref[13] = {1, 2, 4, 8, 16, 32, 64, 128, 256, 512, 1024, 2048, 4096};
	int valid[19] = {15, 23, 39, 51, 54, 71, 99, 113, 114, 116, 275, 305, 306, 547, 561, 562, 785, 802, 4369};

	int	i;
	int sum;

	i = -1;
	sum = 0;
	while (s[++i])
	{
		if (s[i] == '#')
			sum += ref[i];
	}
	printf("%i\n", sum);
	if (ft_binsearch(valid, sum, 19) == -1)
		exit(105);
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
