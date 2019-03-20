#include "fillit.h"

static void	remove_piece(char **map, t_tetra *pc, t_coord *cur)
{
	int	i;

	i = -1;
	while (++i < 4)
		map[cur[i].y][cur[i].x] = '.';
	pc->put = 0;
}

static int	put_piece(char **map, t_tetra *pc, int size, t_coord *cur)
{
	int	i;
	int	wd[4];
	int	ht[4];

	if ((cur[4].x - pc->wdl < 0) || (cur[4].x + pc->wdr > (size - 1))
			|| (cur[4].y + pc->ht > (size - 1)))
		return (0);
	i = -1;
	while (++i < 4)
	{
		wd[i] = pc->x[i] + cur[4].x;
		ht[i] = pc->y[i] + cur[4].y;
		if ((wd[i] >= size || ht[i] >= size) || (map[ht[i]][wd[i]] != '.'))
			return (0);
	}
	/* draw the piece */
	i = -1;
	while (++i < 4)
	{
		map[ht[i]][wd[i]] = pc->c;
		cur[i].x = wd[i];
		cur[i].y = ht[i];
	}
	pc->put = 1;
	return (1);
}
/*
int			find_piece(t_tetra *pcs, int pccount)
{
	int	i;

	i = -1;
	while (++i < pccount)
	{
		if (!(pcs[i].put))
			return (i);
	}
	return (-1);
}
*/
int			fillit(char **map, int size, t_tetra *pcs, int i)
{
	/* cells where the current piece will be put (cur[0] to cur [3]) */
	/* cur[4] are the map coordinates through which piece position will be iterated */
	t_coord cur[CUR_SIZE];

	/* base case: iterated through all the pieces */
	if (pcs[i].c == '0')
		return (1);
	coordinit(cur, CUR_SIZE);
	/* iterate through map cells trying current piece */
	cur[4].y = -1;
	while (++cur[4].y < size)
	{
		cur[4].x = -1;
		while (++cur[4].x < size)
		{
			/* if piece is put, run fillit again */
			if (put_piece(map, &pcs[i], size, cur))
				if ((fillit(map, size, pcs, i + 1)))
					return (1);
			if (pcs[i].put)
				remove_piece(map, &pcs[i], cur);
		}
	}
	return (0);
}
