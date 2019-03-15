#include "fillit.h"

int	fillit(char **map, int size, t_tetra *pcs, int pccount, int fit)
{
	int	i;

	/* base case: all fit */
	if (!(find_piece(pcs)))
		return (size - 1);
	i = -1;
	while (++i < pccount && !fit)
	{
		if (put_piece(map, pcs[i]))
			fit = fillit(map, size, &pcs[i + 1], pccount - 1, fit);
		if (!fit)
			remove_piece(map, piece);
	}
	return (fit);
}

		
	/* stupid version to test main */
/* 	if (size == 5 && pcs && pccount)
	{
		fit = size;
		fit--;
		map[0][0] = '$';
		return (fit);
	}
	else
		return (0);*/

