/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dfonarev <dfonarev@42.us.org>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/21 00:28:27 by dfonarev          #+#    #+#             */
/*   Updated: 2019/03/21 04:03:06 by dfonarev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

static char	**create_map(int size)
{
	char	**map;
	int		i;

	if (!(map = malloc((size + 1) * sizeof(*map))))
		return (NULL);
	map[size] = NULL;
	i = -1;
	while (++i < size)
	{
		if (!(map[i] = ft_strnew(size)))
			exit(1);
		ft_bchar(map[i], '.', size);
	}
	return (map);
}

void		delete_map(char **map)
{
	int	i;

	i = -1;
	while (*(map + ++i))
		free(*(map + i));
	free(map);
}

void		print_map(char **map)
{
	int	i;
	int	j;

	i = -1;
	while (map[++i])
	{
		j = -1;
		while (map[i][++j])
			write(1, &map[i][j], 1);
		write(1, "\n", 1);
	}
}

void		mapinator(t_tetra *pcs, int pccount, int size)
{
	char	**map;
	char	**oldmap;

	oldmap = NULL;
	while (size && (size * size >= pccount * 4))
	{
		if (!(map = create_map(size)))
			kill_all(NULL, &pcs, map, oldmap);
		arrinit(&pcs, pccount, 1);
		if ((fillit(map, size, pcs, 0)))
		{
			if (oldmap)
				delete_map(oldmap);
			oldmap = map;
			size--;
			map = NULL;
		}
		else
			break ;
	}
	print_map(oldmap);
	delete_map(oldmap);
	if (map)
		delete_map(map);
	free(pcs);
}
