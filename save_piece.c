#include "fillit.h"

static void	check_piece(char *s)
{
	/* a reference grid where each cell has such value so that
	 * any sum of n other cells can be equal to its value */
	int	ref[13] = {REFWEIGHTS};
	/* valid sums for each of the 19 possible tetraminos */
	int valid[19] = {VALIDSUMS};

	int	i;
	int sum;
	int	cnt;

	i = -1;
	sum = 0;
	cnt = 0;
	while (s[++i])
	{
		if (s[i] == '#')
		{
			sum += ref[i];
			cnt++;
		}
		else if (s[i] != '.')
			exit(109);
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

int			save_piece(char *ln16, t_tetra *piece, char ch)
{
	int		i;
	int		k;

	if (!ln16)
		exit(106);
	move_piece(ln16, calc_shift(ln16));
	check_piece(ln16);
	piece->c = ch;
	i = -1;
	k = -1;
	while (ln16[++i])
	{
		if (ln16[i] == '#')
		{
			piece->x[++k] = i % 4;
			piece->y[k] = i / 4;
		}
	}
	free(ln16);
	return (1);
}
