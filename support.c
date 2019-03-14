#include "fillit.h"

void	arrinit(t_tetra **pcs, int size)
{
	int	i;

	if (!(*pcs = malloc(size * sizeof(**pcs))))
		exit(104);
	i = -1;
	while (++i < size)
		(*pcs + i)->put = 0;
}
