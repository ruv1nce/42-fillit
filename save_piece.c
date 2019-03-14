#include "fillit.h"

static void	check_piece(char *s)
{
	/* a reference grid where each cell has such value so that
	 * any sum of n other cells can be equal to its value */
	int	ref[13] = {1, 2, 4, 8, 16, 32, 64, 128, 256, 512, 1024, 2048, 4096};
	/* valid sums for each of the 19 possible tetraminos */
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
	if (ft_binsearch(valid, sum, 19) == -1)
		exit(105);
}

static int	calc_shift(char *ln16)
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

static void	move_piece(char *ln16, int shift)
{
	int i;

	ln16 = ft_strcpy(ln16, ln16 + shift);
	i = LEN - 1;
	while (shift--)
		ln16[i--] = '.';
}

int			save_piece(char *ln16, t_tetra *piece, char c)
{
	int		i;
	int		x;
	int		y;

	if (!ln16)
		exit(106);
	move_piece(ln16, calc_shift(ln16));
	check_piece(ln16);
	i = -1;
	x = 0;
	y = 0;
	while (ln16[++i])
	{
		if (ln16[i] == '#')
			piece->config[y][x++] = c;
		else if (ln16[i] == '.')
			piece->config[y][x++] = ln16[i];
		else
			return (0);
		if ((i + 1) % 4 == 0)
		{
			x = 0;
			y++;
		}
	}
	free(ln16);
	return (1);
}
