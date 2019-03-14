#include "fillit.h"

char	**create_map(int size)
{
	char	**map;
	int		i;

	if (!(map = malloc((size + 1) * sizeof(*map))))
		exit(105);
	map[size] = NULL;
	i = -1;
	while (++i < size)
	{
		if (!(map[i] = ft_strnew(size)))
			exit(106);
		ft_bchar(map[i], '.', size);
		printf("%s\n", map[i]);
	}
	return (map);
}

void	delete_map(char **map)
{
	int	i;

	i = -1;
	while (*(map + ++i))
		free(*(map + i));
	free(map);
}

void	print_map(char **map)
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
