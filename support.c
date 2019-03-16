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
