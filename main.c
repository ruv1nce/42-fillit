#include "fillit.h"

/* add proper exit function: in case of any error run this function:
 * - print error to stdout
 * - free map
 * - free list */

static void	read_file(char *file, char **line)
{
	int		fd;
	int		resume;
	char	*tmp;
	int		linecnt;

	fd = open(file, O_RDONLY);
	if (fd < 0)
		exit(101);
	*line = NULL;
	resume = 1;
	linecnt = 0;
	while ((resume = ft_gnl(fd, &tmp)) > 0)
	{
		linecnt = (linecnt == 4) ? 0 : linecnt + 1;
		if ((!(linecnt) && ft_strlen(tmp)) || (linecnt && ft_strlen(tmp) != 4))
			exit(102);
		*line = ft_strjoin(*line, tmp);
		free(tmp);
	}
	if (linecnt != 4)
		exit (103);
	close(fd);
}

static int	create_tetra_list(char *file, t_list *lst)
{
	char	*line;
	int		i;
	int		len;
	int		npcs;
	char	c;
	
	read_file(file, &line);
	npcs = 0;
	i = 0;
	len = ft_strlen(line);
	c = 'A';
	while (i < len)
	{
		if (!(addtail(lst)) || !(save_piece(ft_strsub(line, i, LEN), lst, c)))
		{
			lstdel(lst);
			exit(104);
		}
		npcs++;
		i += LEN;
		c++;
	}
	return (npcs);
}
/*
char	**create_map(int size)
{
	char	**map;
	int		i;

	if (!(map = malloc(size * sizeof(*map))))
		exit(105);
	i = -1;
	while (++i < size)
	{
		if (!(map[i] = malloc(size * sizeof(**map))))
			exit(106);
		ft_bzero(map[i], size);
	}
	return (map);
}
*/
int			main(int argc, char **argv)
{
	t_list	lst;
	int		size;
	int		i;	// KILLME
	t_tetra	*tmp;	// KILLME
	char	**map;
	char	**oldmap;

	if (argc != 2)
		write(1, "usage: ./fillit <filename>\n", 27);
	lstinit(&lst);
	size = create_tetra_list(argv[1], &lst);
	printf("npcs = %i\n", size);
	size = (ft_sqrt_floor(size * 4) + 1);
	printf("size = %i\n", size);

	map = NULL;
	oldmap = NULL;
	while (size)
	{
		map = create_map(size);
		if ((size = fillit(map, size, lst.head, 0)))
		{
			if (oldmap)
				delete_map(oldmap);
			oldmap = map;
		}
	}
	delete_map(map);
	print_map(oldmap);
	delete_map(oldmap);


	/* print pieces list */
	tmp = lst.head;				// KILL
	while (tmp)	
	{
		i = -1;
		while (++i < 4)
		{
			write(1, tmp->config[i], 4);
			write(1, "\n", 1);
		}
		write(1, "\n", 1);
		tmp = tmp->next;
	}							// US
	lstdel(&lst);
}
