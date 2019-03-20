#include "fillit.h"
/*
int			check_piece(char *s)
{
	*//* a reference grid where each cell has such value so that
	 * any sum of n other cells cannot be equal to its value *//*
	int	*ref;
	*//* valid sums for each of the 19 possible tetraminos *//*
	int valid[19] = {VALIDSUMS};
	int	i;
	int sum;
	int	cnt;

	if (!(checkinit(&ref)))
		return (0);
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
	if (ft_binsearch(valid, sum, 19) == -1)
		return (0);
	return (1);
}
*/

int			check_piece(char *s)
{
	int	i;
	int	cnt;

	cnt = 0;
	i = -1;
	while (s[++i])
	{
		if (s[i] == '#')
		{
			/* check right */
			if (((i + 1) % 4 != 0 && s[i + 1] == '#') || ((i < 12) && s[i + 4] == '#') || ((i % 4 != 0) && s[i - 1] == '#') || (i > 3 && s[i - 4] == '#'))
				cnt++;
			else
				return (0);
		}
		else if (s[i] != '.')
			return (0);
	}
	if (cnt == 4)
		return (1);
	return (0);
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

void		store_coord(char *ln16, t_tetra *piece, int i, int k)
{
	int	zero;

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
}

int			save_piece(char *ln16, t_tetra *piece, char ch)
{
	int	i;
	int	k;

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
	store_coord(ln16, piece, i, k);
//	printf("put %i, c %c, wdl %i, wdr %i, ht %i\n", piece->put, piece->c, piece->wdl, piece->wdr, piece->ht);
	free(ln16);
	return (1);
}
