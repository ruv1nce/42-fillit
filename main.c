#include "fillit.h"
#include <stdio.h>	// KILLME

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

static int	create_tetra_list(char *file, t_tetra **pieces)
{
	char	*line;
	int		i;
	int		len;
	int		npcs;
	
	read_file(file, &line);
	npcs = 0;
	i = 0;
	len = ft_strlen(line);
	while (i < len)
	{
		printf("i %i, len %i\n", i, len);	// KILLME
		if (!(lstadd(pieces)) || !(save_piece(ft_strsub(line, i, LEN), pieces)))
		{
			lstdel(pieces);
			exit(104);
		}
		npcs++;
		i += LEN;
	}
	return (npcs);
}

int			main(int argc, char **argv)
{
	t_tetra	*pieces;
	int		npcs;
	int		size;
	int		i;	// KILLME
	t_tetra	*tmp;	// KILLME
//	char	**square;

	if (argc != 2)
		write(1, "usage: ./fillit <filename>\n", 27);
	pieces = NULL;
	npcs = create_tetra_list(argv[1], &pieces);
	printf("size = %i\n", size = (ft_sqrt_floor(npcs * 4) + 1));
/*	square = NULL;
	while (side)
	{
		if (square)
			free(square);
		square = malloc(
		side = fillit(square, size, pieces);
	}


	*//* print pieces list */
	tmp = pieces;				// KILL
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
	lstdel(&pieces);
}
