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

void	mapinator(t_tetra *pcs, int pccount, int size)
{
	char	**map;
	char	**oldmap;
	t_lost	lost;
	int		maxlost;

	map = NULL;
	oldmap = NULL;
	lost.cnt = 0;
	lost.total = 0;
	while (size && (size * size >= pccount * 4))
	{
		if (!(map = create_map(size)))
			kill_all(NULL, &pcs, map, oldmap);
		arrinit(&pcs, pccount, 1);
//		printf("empty map:\n");	// KILLME
//		print_map(map);	// KILLME
		maxlost = size * size - pccount * 4;
		printf("maxlost %i\n", maxlost);
		if ((size = fillit(map, size, pcs, pccount, 0, &lost, maxlost)))
		{
			if (oldmap)
				delete_map(oldmap);
			oldmap = map;
//			printf("filled map:\n");	// KILLME
//			print_map(map);	// KILLME
		}
	}
//	delete_map(map);
//	printf("result:\n");	// KILLME
	print_map(oldmap);
	delete_map(oldmap);
	free(pcs);
}
