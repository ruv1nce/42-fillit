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
	struct s_tetra	*next;
}					t_tetra;

typedef struct		s_list
{
	int				count;
	t_tetra			*head;
	t_tetra			*tail;
}					t_list;

void				lstinit(t_list *l);
int					addtail(t_list *l);
void				lstdel(t_list *l);
int					save_piece(char *ln16, t_list *lst, char c);
char				**create_map(int size);
void				delete_map(char **map);
void				print_map(char **map);
int					fillit(char **map, int size, t_tetra *piece, int fit);

#endif
