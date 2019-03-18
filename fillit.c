#include "fillit.h"

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

	/* check if map edges are too close */
						write(1, "check edge\n", 11);
						write(1, &pc->c, 1);
						write(1, "\nx:", 3);
						ft_putnbr(x);
						write(1, " y:", 3);
						ft_putnbr(y);
						write(1, "\nwdl ", 5);
						ft_putnbr(pc->wdl);
						write(1, " wdr ", 5);
						ft_putnbr(pc->wdr);
						write(1, " ht ", 4);
						ft_putnbr(pc->ht);
						write(1, "\n\n", 2);
	if ((x - pc->wdl < 0) || (x + pc->wdr > (size - 1)) || (y + pc->ht > (size - 1)))
		return (0);
	/* calc relative coordinates and check if the positions are empty */
						write(1, "try\n", 4);
						write(1, "pc c = ", 7);
						write(1, &pc->c, 1);
						write(1, "\nx:", 3);
						ft_putnbr(x);
						write(1, " y:", 3);
						ft_putnbr(y);
						write(1, "\n", 1);
						print_map(map);
						write(1, "\n", 1);
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
	while (map[cur[4].y] && !pc->put)
	{
		while (map[cur[4].y][cur[4].x] && !pc->put)
		{
			if (map[cur[4].y][cur[4].x] == '.')
			{
				if (try_piece(map, pc, cur[4].x, cur[4].y, size, cur))
				{
					pc->put = 1;
				}				
			}
			cur[4].x += 1;
			if (pc->put)
				return (1);
		}
		cur[4].y += 1;
		cur[4].x = 0;
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
	/* cells where the current piece will be put (cur[0] to cur [3]) */
	/* indexes cur[4].x and cut[4].y will be used to store the current cell coordinates
	 * when iterating through map and trying differenet starting positions for each piece */
	t_coord cur[CUR_SIZE];

//	coordinit(cur);
	/* base case: all pieces have been put */
	if ((i = find_piece(pcs, pccount)) == -1)
		return (size - 1);
	/* iterate through unput pieces */
	while (i < pccount && !fit)
	{
		/* iterate through map cells trying current piece */
		coordinit(cur, CUR_SIZE);
		while (map[cur[4].y] && map[cur[4].y][cur[4].x] && !(pcs[i].put))
		{
					write(1, "fillit\n", 7);
					write(1, "pc: i = ", 8);
					ft_putnbr(i);
					write(1, " c = ", 5);
					write(1, &pcs[i].c, 1);
					write(1, " put = ", 7);
					ft_putnbr(pcs[i].put);
					write(1, "\nx:", 2);
					ft_putnbr(cur[4].x);
					write(1, " y:", 3);
					ft_putnbr(cur[4].y);
					write(1, "\n", 1);
					print_map(map);
					write(1, "\n", 1);
			if (!(pcs[i].put))
			{
				/* if piece is put, run fillit again */
				if (put_piece(map, &pcs[i], size, cur))
					fit = fillit(map, size, pcs, pccount, fit);
				if (!fit && pcs[i].put)
					remove_piece(map, &pcs[i], cur);
			}
		}
		i++;
	}
	return (fit);
}
