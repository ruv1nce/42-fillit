/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save_piece.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dfonarev <dfonarev@42.us.org>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/21 00:28:37 by dfonarev          #+#    #+#             */
/*   Updated: 2019/03/21 00:38:47 by dfonarev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

/*
** - check that the amount of '#' is 4
** - count how many '#' neighbours each '#' has ("adjacency")
** - check that sum of all adjacencies is at least 6
*/

static int	check_piece(char *s)
{
	int	i;
	int	cnt;
	int adj;

	cnt = 0;
	adj = 0;
	i = -1;
	while (s[++i])
	{
		if (s[i] == '#')
		{
			cnt++;
			count_adj(s, i, &adj);
		}
		else if (s[i] != '.')
			return (0);
	}
	if (cnt == 4 && adj >= 6)
		return (1);
	return (0);
}

/*
** - find first '#'
** - calc which row is it on, store in shiftup
** - find the lowest horizontal indent of a '#', store in shiftleft
*/

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
		if (ln16[i] == '#')
			break ;
	}
	if (i >= SIDE)
		shiftup = (i / SIDE);
	shiftleft = SIDE;
	i = -1;
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

/*
** - first '#' always has x=0, y=0
** - "zero" contains right indent of the first '#'
** - subtract "zero" from x position of other '#' (result might be neg)
** - calc the maximum left, right and down deviations of piece's
**   	coordinates, store in piece->wdl,wdr,ht
*/

void		store_coord(char *ln16, t_tetra *piece, int i, int k)
{
	int	zero;

	zero = -1;
	while (ln16[++i])
	{
		if (ln16[i] == '#')
		{
			if (zero == -1)
			{
				zero = i;
				piece->x[++k] = 0;
			}
			else
			{
				if (((piece->x[++k] = i % 4 - zero) < 0)
						&& (piece->x[k] < piece->wdl))
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
	if (!(check_piece(ln16)))
	{
		free(ln16);
		return (0);
	}
	piece->c = ch;
	i = -1;
	k = -1;
	store_coord(ln16, piece, i, k);
	free(ln16);
	return (1);
}
