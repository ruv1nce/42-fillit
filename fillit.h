#ifndef FILLIT_H 
# define FILLIT_H

# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include "libft.h"

# define PIECELEN 16
# define PIECESIDE 4

typedef struct		s_tetra
{
	char			config[4][4];
	struct s_tetra	*next;
}					t_tetra;

t_tetra				*lstnew(void);
int					lstadd(t_tetra **lst);
void				lstdel(t_tetra **lst);

#endif
