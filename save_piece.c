#include "fillit.h"

int			check_piece(char *s)
{
	/* a reference grid where each cell has such value so that
	 * any sum of n other cells cannot be equal to its value */
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
			return (0);
	}
	ft_putnbr(sum);
	write(1, "\n", 1);
	if (ft_binsearch(valid, sum, 19) == -1)
		return (0);
	return (1);
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
	if (i >= SIDE)
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
	int	i;
	int	k;
	int	zero;

	if (!ln16)
		return (0);
	move_piece(ln16, calc_shift(ln16));
	if (!(check_piece(ln16)))/*, &pcwdl, &pcwdr, &pcht)))*/
	{
		free(ln16);
		return (0);
	}
	piece->c = ch;
	/* create piece coordinates */
	i = -1;
	k = -1;
	zero = -1;
	while (ln16[++i])
	{
		if (ln16[i] == '#')
		{
			/* save the number of column where the first # is , this will allow
			 * 		for storing negative x for other # cells */
			if (zero == -1)
			{
				zero = i;
				piece->x[++k] = 0;
			}
			else
			{
				if (((piece->x[++k] = i % 4 - zero) < 0) && (piece->x[k] < piece->wdl))
					piece->wdl = piece->x[k];
				else if (piece->x[k] > piece->wdr)
					piece->wdr = piece->x[k];
			}
			if ((piece->y[k] = i / 4) > piece->ht)
				piece->ht = piece->y[k];
		}
	}
	printf("put %i, c %c, wdl %i, wdr %i, ht %i\n", piece->put, piece->c, piece->wdl, piece->wdr, piece->ht);
	free(ln16);
	return (1);
}
