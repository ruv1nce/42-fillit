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
	char	ch;
	
	read_file(file, &line);
//	printf("%s\n", line);	// 	KILLME
	len = ft_strlen(line);
//	printf("len = %i\n", len);	// 	KILLME
	arrinit(pcs, len / LEN);
	ch = 'A';
	pccount = 0;
	i = 0;
	while (i < len)
	{
		if (!(save_piece(ft_strsub(line, i, LEN), (*pcs + pccount), ch)))
			exit(108);
		pccount++;
		i += LEN;
		ch++;
	}
	return (pccount);
}

int			main(int argc, char **argv)
{
	t_tetra	*pcs;
	int		size;
	int		pccount;
	char	**map;
	char	**oldmap;
//	int		i;	// KILLME

	if (argc != 2)
		write(1, "usage: ./fillit <filename>\n", 27);
	pcs = NULL;
	pccount = create_arr(argv[1], &pcs);
//	printf("pccount = %i\n", pccount);	// KILLME
	size = (ft_sqrt(pccount * 4, 1) + 1);
	if (size < 4)
		size = 4;
//	printf("size = %i\n", size);	// KILLME

	/* print pieces */
/*	i = -1;
	while (++i < pccount)
	{
		printf("\npiece %i\n", i);
		printf("  |0 1 2 3\n--|-------\nx |%i %i %i %i\ny |%i %i %i %i\n", pcs[i].x[0], pcs[i].x[1], pcs[i].x[2], pcs[i].x[3], pcs[i].y[0], pcs[i].y[1], pcs[i].y[2], pcs[i].y[3]);
	}
*/
	map = NULL;
	oldmap = NULL;
	while (size && (size * size > pccount * 4))
	{
		map = create_map(size);
		arrinit(&pcs, pccount);
//		printf("empty map:\n");	// KILLME
//		print_map(map);	// KILLME
		if ((size = fillit(map, size, pcs, pccount, 0)))
		{
			if (oldmap)
				delete_map(oldmap);
			oldmap = map;
//			printf("filled map:\n");	// KILLME
//			print_map(map);	// KILLME
		}
	}
//	delete_map(map);
//	printf("result:\n");	// KILLME
	print_map(oldmap);
	delete_map(oldmap);

	free(pcs);
}
