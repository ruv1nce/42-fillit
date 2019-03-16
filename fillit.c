#include "fillit.h"

static int	is_four_cell_block(int x, int y, char **map, int size)
{
	int 	cnt;
	int		i;
	t_coord dogs[4];	

	dogsinit(dogs);
	cnt = 0;
	flood_fill(x, y, map, size, &cnt, &dogs[0]);
	/* think of keeping dogs if cnt < 4 */
	if (cnt)
	{
//		print_map(map);
//		write(1, "\n", 1);
		/* clear dogs */
		i = -1;
		while (++i < cnt)
			map[dogs[i].y][dogs[i].x] = '.';
//		print_map(map);
//		write(1, "\n", 1);
	}
	if (cnt >= 4) //
		return (1);
	return (0);
}

static int	find_empty_cell(int	*x, int *y, char **map, int size)
{
	while (map[*y])
	{
		while (map[*y][*x])
		{
			if (map[*y][*x] == '.')
			{
				if ((is_four_cell_block(*x, *y, map, size)))
					return (1);
			}
			(*x)++;
		}
		*x = 0;
		(*y)++;
	}
	return (0);
}

static void	remove_piece(char **map, t_tetra *pc)
{
	int	x;
	int	y;

	y = -1;
	while (map[++y])
	{
		x = -1;
		while (map[y][++x])
		{
			if (map[y][x] == pc->c)
				map[y][x] = '.';
		}
	}
	pc->put = 0;
}

static int	try_piece(char **map, t_tetra *pc, int x, int y, int size)
{
	int	i;
	int	wd[4];
	int	ht[4];

	i = -1;
	while (++i < 4)
	{
		wd[i] = pc->x[i] + x;
		ht[i] = pc->y[i] + y;
		if (wd[i] >= size || ht[i] >= size)
			return (0);
	}
	i = -1;
	while (++i < 4)
	{
		if (map[ht[i]][wd[i]] == '.')
			map[ht[i]][wd[i]] = pc->c;
		else
		{
			remove_piece(map, pc);
			return (0);
		}
	}
	return (1);
}

int	put_piece(char **map, t_tetra *pc, int size)
{
	int		x;
	int		y;

	y = -1;
	while (map[++y])
	{
		x = -1;
		while (map[y][++x])
		{
			if (!(find_empty_cell(&x, &y, map, size)))
				return (0);
			if (try_piece(map, pc, x, y, size))
			{
				pc->put = 1;
				return (1);
			}
		}
	}
	return (0);
}

int	find_piece(t_tetra *pcs, int pccount)
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

int	fillit(char **map, int size, t_tetra *pcs, int pccount, int fit)
{
	int	i;

	/* base case: all pieces have been put */
	if ((i = find_piece(pcs, pccount)) == -1)
		return (size - 1);
	/* iterate through unput pieces */
	while (i < pccount && !fit)
	{
		if (!(pcs[i].put))
		{
			/* if piece is put, run fillit again */
			if (put_piece(map, &pcs[i], size))
				fit = fillit(map, size, pcs, pccount, fit);
			if (!fit)
				/* it runs excessively with a piece that wasn't put
				 * add curly braces under put-piece-if */
				remove_piece(map, &pcs[i]);
		}
		i++;
	}
	return (fit);
}

		
	/* stupid version to test main */
/* 	if (size == 5 && pcs && pccount)
	{
		fit = size;
		fit--;
		map[0][0] = '$';
		return (fit);
	}
	else
		return (0);*/

