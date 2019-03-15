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

static int	create_arr(char *file, t_tetra **pcs)
{
	char	*line;
	int		i;
	int		len;
	int		pccount;
	char	c;
	
	read_file(file, &line);
	len = ft_strlen(line);
	arrinit(pcs, len / LEN);
	c = 'A';
	pccount = 0;
	i = 0;
	while (i < len)
	{
		if (!(save_piece(ft_strsub(line, i, LEN), (*pcs + pccount), c)))
			exit(108);
		pccount++;
		i += LEN;
		c++;
	}
	return (pccount);
}

int			main(int argc, char **argv)
{
	t_tetra	*pcs;
	int		size;
	int		pccount;
	int		i;	// KILLME
	int		j;
	char	**map;
	char	**oldmap;

	if (argc != 2)
		write(1, "usage: ./fillit <filename>\n", 27);
	pccount = create_arr(argv[1], &pcs);
	printf("pccount = %i\n", pccount);	// KILLME
	size = (ft_sqrt_floor(pccount * 4) + 1);
	printf("size = %i\n", size);	// KILLME

	map = NULL;
	oldmap = NULL;
	while (size)
	{
		map = create_map(size);
		if ((size = fillit(map, size, pcs, pccount, 0)))
		{
			if (oldmap)
				delete_map(oldmap);
			oldmap = map;
		}
	}
	delete_map(map);
	print_map(oldmap);
	delete_map(oldmap);


	/* print pieces  */
	i = -1;
	while (++i < pccount)	
	{
		j = -1;
		while (++j < SIDE)
		{
			write(1, (pcs + i)->config[j], SIDE);
			write(1, "\n", 1);
		}
		write(1, "\n", 1);
	}							// US
	free(pcs);
}
