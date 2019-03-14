#ifndef FILLIT_H 
# define FILLIT_H

# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include "libft.h"

# include <stdio.h>	// KILLME

# define LEN 16
# define SIDE 4

typedef struct		s_tetra
{
	int				put;
	char			config[4][4];
}					t_tetra;

void				arrinit(t_tetra **pcs, int size);
int					save_piece(char *ln16, t_tetra *piece, char c);
char				**create_map(int size);
void				delete_map(char **map);
void				print_map(char **map);
int					fillit(char **map, int size, t_tetra *piece, int fit);

#endif
