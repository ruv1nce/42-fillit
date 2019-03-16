#include "fillit.h"

void	coordinit(t_coord *cells)
{
	int	i;

	i = -1;
	while (++i < 4)
	{
		cells[i].x = 0;
		cells[i].y = 0;
	}
}

int		arrinit(t_tetra **pcs, int size)
{
	int	i;

	if (!*pcs)
	{
		if (!(*pcs = malloc(size * sizeof(**pcs))))
			return (0);
	}
	i = -1;
	while (++i < size)
		(*pcs + i)->put = 0;
	return (1);
}

void	flood_fill(int x, int y, char **map, int size, int *cnt, t_coord *dogs)
{
	map[y][x] = '@';
	dogs[*cnt].x = x;
	dogs[*cnt].y = y;
	(*cnt)++;
	if ((x + 1 < size) && (map[y][x + 1] == '.') && *cnt < 4)
		flood_fill(x + 1, y, map, size, cnt, dogs);
	if (x > 0 && (map[y][x - 1] == '.') && *cnt < 4)
		flood_fill(x - 1, y, map, size, cnt, dogs);
	if ((y + 1 < size) && (map[y + 1][x] == '.') && *cnt < 4)
		flood_fill(x, y + 1, map, size, cnt, dogs);
	if (y > 0 && (map[y - 1][x] == '.') && *cnt < 4)
		flood_fill(x, y - 1, map, size, cnt, dogs);
}
