#include "fillit.h"

static int	is_four_cell_block(int x, int y, char **map)
{
	int	cnt;

	map[y][x] = '@';
	cnt = 1;
	/* scan the "first" row left to right */
	while (map[y][++x])
	{
		if (map[y][x] == '.' && map[y][x - 1] == '@')
		{
			map[y][x] = '@';
			cnt++;
		}
		if (cnt >= 4)
			break;
	}
	/* scan the other rows */
	while (map[++y])
	{
		/* scan row left direction */
		while (--x >= 0)
		{
			if (map[y][x] == '.' && (map[y][x + 1] == '@' || map[y - 1][x] == '@'))
			{				
				   map[y][x] = '@';
				   cnt++;
			}
			if (cnt >= 4)
				break;
		}
		/* scan row right direction */
		while (map[y][++x])
		{
			if (map[y][x] == '.' && map[y][x - 1] == '@')
			{
				map[y][x] = '@';
				cnt++;
			}
			if (cnt >= 4)
				break;
		}
	}
	print_map(map);
	y = -1;
	while (map[++y])
	{
		x = -1;
		while (map[y][++x])
		{
			if (map[y][x] == '@')
				map[y][x] = '.';
		}
	}
	if (cnt >= 4)
		return (1);
	return (0);
}

static int	find_empty_cell(int	*x, int *y, char **map)
{
	while (map[*y])
	{
		while (map[*y][*x])
		{
			if (map[*y][*x] == '.')
			{
				if ((is_four_cell_block(*x, *y, map)))
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
			if (!(find_empty_cell(&x, &y, map)))
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

	/* base case: all fit  */
	if ((i = find_piece(pcs, pccount)) == -1)
		return (size - 1);
	while (i < pccount && !fit)
	{
		if (!(pcs[i].put))
		{
			if (put_piece(map, &pcs[i], size))
				fit = fillit(map, size, pcs, pccount, fit);
			if (!fit)
				/* it runs excessively with a piece that wasn't put */
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

