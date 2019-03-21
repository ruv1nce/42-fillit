/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   support.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dfonarev <dfonarev@42.us.org>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/21 00:29:10 by dfonarev          #+#    #+#             */
/*   Updated: 2019/03/21 00:45:00 by dfonarev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

void	count_adj(char *s, int i, int *adj)
{
	if ((i + 1) % 4 != 0 && s[i + 1] == '#')
		(*adj)++;
	if (i < 12 && s[i + 4] == '#')
		(*adj)++;
	if (i % 4 != 0 && s[i - 1] == '#')
		(*adj)++;
	if (i > 3 && s[i - 4] == '#')
		(*adj)++;
}

void	coordinit(t_coord *cells, int size)
{
	int	i;

	i = -1;
	while (++i < size)
	{
		cells[i].x = 0;
		cells[i].y = 0;
	}
}

/*
** mode 0: allocation of the array
** mode 1: erasing the info in 'put' key
*/

int		arrinit(t_tetra **pcs, int size, int mode)
{
	int	i;

	if (mode == 0)
	{
		if (!(*pcs = malloc(((size + 1) * sizeof(**pcs)))))
			return (0);
		(*pcs + size)->c = '0';
	}
	i = -1;
	while (++i < size)
	{
		if (mode == 0)
		{
			(*pcs + i)->wdl = 0;
			(*pcs + i)->wdr = 0;
			(*pcs + i)->ht = 0;
		}
		(*pcs + i)->put = 0;
	}
	return (1);
}
