#include "libft.h"
#include "fillit.h"

t_tetra	*lstnew(void)
{
	t_tetra	*new;

	if (!(new = malloc(sizeof(*new))))
		return (NULL);
	new->next = NULL;
	return (new);
}

int		lstadd(t_tetra **lst)
{
	t_tetra	*new;

	if (!(new = lstnew()))
		return (0);
	if (*lst)
		new->next = *lst;
	*lst = new;
	return (1);
}

void	lstdel(t_tetra **lst)
{
	t_tetra	*tmp;

	while (*lst)
	{
		tmp = *lst;
		*lst = (*lst)->next;
		free(tmp);
	}
	*lst = NULL;
}
