#ifndef FILLIT_H 
# define FILLIT_H

# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include "libft.h"

# include <stdio.h>	// KILLME

# define LEN 16
# define SIDE 4
# define REFWEIGHTS 1, 2, 4, 8, 16, 32, 64, 128, 256, 512, 1024, 2048, 4096
# define VALIDSUMS 15, 23, 39, 51, 54, 71, 99, 113, 114, 116, 275, 305, 306, 547, 561, 562, 785, 802, 4369

typedef struct		s_tetra
{
	int				put;
	char			c;
	int				x[4];
	int				y[4];
}					t_tetra;

void				arrinit(t_tetra **pcs, int size);
int					save_piece(char *ln16, t_tetra *piece, char ch);
char				**create_map(int size);
void				delete_map(char **map);
void				print_map(char **map);
int					fillit(char **map, int size, t_tetra *pcs, int pccount, int fit);

#endif
