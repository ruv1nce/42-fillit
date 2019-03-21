/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fillit.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dfonarev <dfonarev@42.us.org>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/21 00:29:18 by dfonarev          #+#    #+#             */
/*   Updated: 2019/03/21 00:45:44 by dfonarev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FILLIT_H
# define FILLIT_H

# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include "libft.h"

# define LEN 16
# define SIDE 4
# define CUR_SIZE 5

/*
** t_tetra contains all the info about a tetra piece:
**  put:	1 if it's been put on the map, 0 if not
** 	c:		char id of a piece
** 	wdl:	relative width of a piece to the left of the column
**				where first # is located
** 	wdr:	relative width of a piece to the right of the column
**				where first # is located
** 	ht:		piece's height
** 	x & y:	arrays of piece's coordinates, where x[0], y[0]
**				are coordinates of the first #
*/

typedef struct	s_tetra
{
	int			put;
	char		c;
	int			wdl;
	int			wdr;
	int			ht;
	int			x[4];
	int			y[4];
}				t_tetra;

typedef struct	s_coord
{
	int			x;
	int			y;
}				t_coord;

int				arrinit(t_tetra **pcs, int size, int mode);
void			coordinit(t_coord *cells, int size);
int				save_piece(char *ln16, t_tetra *piece, char ch);
void			count_adj(char *s, int i, int *adj);
void			mapinator(t_tetra *pcs, int pccount, int size);
void			delete_map(char **map);
void			print_map(char **map);
int				fillit(char **map, int size, t_tetra *pcs, int i);
void			kill_all(char **line, t_tetra **pcs, char **map, char **oldmap);

#endif
