/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fillit.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dfonarev <dfonarev@42.us.org>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/21 00:27:38 by dfonarev          #+#    #+#             */
/*   Updated: 2019/03/22 23:47:45 by dfonarev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

static void	remove_piece(char **map, t_tetra *pc, t_coord *cur)
{
	int	i;

	i = -1;
	while (++i < 4)
		map[cur[i].y][cur[i].x] = '.';
	pc->put = 0;
}

/*
** - check if piece will reach beyond map borders
** - calculate realtive coordinates of the piece for current map cell
** - check if each relative piece coordinate is an empty map cell
** - draw the piece on the map and store its map position in *cur
*/

static int	put_piece(char **map, t_tetra *pc, int size, t_coord *cur)
{
	int	i;
	int	wd[4];
	int	ht[4];

	if ((cur[4].y + pc->ht) > (size - 1))
		return (-1);
	else if ((cur[4].x + pc->wdr) > (size - 1) || (cur[4].x + pc->wdl) < 0)
		return (0);
	i = -1;
	while (++i < 4)
	{
		wd[i] = pc->x[i] + cur[4].x;
		ht[i] = pc->y[i] + cur[4].y;
		if (map[ht[i]][wd[i]] != '.')
			return (0);
	}
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
** - cells where the current piece will be put (cur[0] to cur [3])
** - cur[4] are map coordinates through which piece position will be iterated
** - base case: iterated through all the pieces
*/

int			fillit(char **map, int size, t_tetra *pcs, int i)
{
	t_coord cur[CUR_SIZE];
	int		putty;

	if (pcs[i].c == '0')
		return (1);
	coordinit(cur, CUR_SIZE);
	cur[4].y = -1;
	while (++cur[4].y < size)
	{
		cur[4].x = -1;
		while (++cur[4].x < size)
		{
			if ((putty = put_piece(map, &pcs[i], size, cur) == 1))
			{
				if ((fillit(map, size, pcs, i + 1)))
					return (1);
			}
			else if (putty == -1)
				return (0);
			if (pcs[i].put)
				remove_piece(map, &pcs[i], cur);
		}
	}
	return (0);
}
