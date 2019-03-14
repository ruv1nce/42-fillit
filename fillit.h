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
int					save_piece(char *ln16, t_list *lst);

//t_tetra				*lstnew(void);
//int					lstadd(t_tetra **lst);
//void				lstdel(t_tetra **lst);

#endif
