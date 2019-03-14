#include "fillit.h"

int	fillit(char **map, int size, t_tetra *piece, int fit)
{
	if (size == 5 && piece)
	{
		fit = size;
		fit--;
		map[0][0] = '$';
		return (fit);
	}
	else
		return (0);
}

/*
int	fillit(char **map, int size, t_tetra *piece, int fit)
{
	if (!piece)
		fit = size - 1;
	else
	{
		if (put_piece(map, piece))
		{
			fit = fillit(map, size, piece->next, fit);
			if (!fit)
				remove_piece(map, piece);
		}
	}
	return (fit);
}*/
