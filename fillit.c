#include "fillit.h"

static int	is_four_cell_block(int x, int y, char **map, int size)
{
	int 	cnt;
	int		i;
	/* cells where the '@' chars will be after flood_fill */
	t_coord dogs[4];	

	coordinit(dogs);
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

static void	remove_piece(char **map, t_tetra *pc, t_coord *cur)
{
	int	i;

	i = -1;
	while (++i < 4)
		map[cur[i].y][cur[i].x] = '.';
	pc->put = 0;
}

static int	try_piece(char **map, t_tetra *pc, int x, int y, int size, t_coord *cur)
{
	int	i;
	int	wd[4];
	int	ht[4];

	/* calc relative coordinates and check if the positions are empty */
	i = -1;
	while (++i < 4)
	{
		wd[i] = pc->x[i] + x;
		ht[i] = pc->y[i] + y;
		if (wd[i] >= size || ht[i] >= size)
			return (0);
		if (map[ht[i]][wd[i]] != '.')
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
	return (1);
}

static int	put_piece(char **map, t_tetra *pc, int size, t_coord *cur)
{
	int		x;
	int		y;

	y = -1;
	while (map[++y])
	{
		x = -1;
		while (map[y][++x])
		{
			if ((map[y][x] == '.') && ((is_four_cell_block(x, y, map, size))))
			{
				if (try_piece(map, pc, x, y, size, cur))
				{
//					print_map(map);
//					write(1, "\n", 1);
					pc->put = 1;
					return (1);
				}
			}
		}
	}
	return (0);
}

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

int			fillit(char **map, int size, t_tetra *pcs, int pccount, int fit)
{
	int	i;
	/* cells where the current piece will be put */
	t_coord cur[4];

	coordinit(cur);
	/* base case: all pieces have been put */
	if ((i = find_piece(pcs, pccount)) == -1)
		return (size - 1);
	/* iterate through unput pieces */
	while (i < pccount && !fit)
	{
		if (!(pcs[i].put))
		{
			/* if piece is put, run fillit again */
			if (put_piece(map, &pcs[i], size, cur))
				fit = fillit(map, size, pcs, pccount, fit);
			if (!fit && pcs[i].put)
				remove_piece(map, &pcs[i], cur);
		}
		i++;
	}
	return (fit);
}
