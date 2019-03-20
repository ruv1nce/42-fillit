#include "fillit.h"
/*
int		checkinit(int **ref)//, int *valid)
{
	int	i;
	int	sum;

	if (!(*ref = malloc(REFS * sizeof(int))))
		return (0);
	(*ref)[0] = 1;
	i = 0;
	sum = 0;
	while (++i < REFS)
	{
		sum += (*ref)[i - 1];
		(*ref)[i] = sum + 1;
	}
	return (1);

}
*/
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

/* mode 0: allocation of the array
 * mode 1: erasing the info in 'put' key */

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
