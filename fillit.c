#include "fillit.h"

int	fillit(char **map, int size, t_tetra *piece, int fit)
{
	if (!piece)
	{
		if (!(piece = find_piece(piece)))
			return (size - 1);
	}
	if (put_piece(map, piece))
	{
		fit = fillit(map, size, piece->next, fit);
		if (!fit)
			remove_piece(map, piece);
	}
	return (fit);
}

/*	stupid version to test main
 *	if (size == 5 && piece)
	{
		fit = size;
		fit--;
		map[0][0] = '$';
		return (fit);
	}
	else
		return (0);
*/
