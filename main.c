/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dfonarev <dfonarev@42.us.org>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/21 00:28:20 by dfonarev          #+#    #+#             */
/*   Updated: 2019/03/21 01:39:57 by dfonarev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

void		kill_all(char **line, t_tetra **pcs, char **map, char **oldmap)
{
	if (line && *line)
		free(*line);
	if (pcs)
		free(*pcs);
	if (map)
		delete_map(map);
	if (oldmap)
		delete_map(oldmap);
	write(1, "error\n", 6);
	exit(0);
}

static void	read_file(char *file, char **line)
{
	int		fd;
	int		resume;
	char	*tmp;
	char	*tmp2;
	int		linecnt;

	fd = open(file, O_RDONLY);
	if (fd < 0)
		kill_all(NULL, NULL, NULL, NULL);
	*line = NULL;
	resume = 1;
	linecnt = 0;
	while ((resume = ft_gnl(fd, &tmp)) > 0)
	{
		linecnt = (linecnt == 4) ? 0 : linecnt + 1;
		if ((!(linecnt) && ft_strlen(tmp)) || (linecnt && ft_strlen(tmp) != 4))
			kill_all(line, NULL, NULL, NULL);
		tmp2 = *line;
		*line = ft_strjoin(*line, tmp);
		free(tmp2);
		free(tmp);
	}
	if (linecnt != 4)
		kill_all(line, NULL, NULL, NULL);
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
	len = ft_strlen(line);
	if (!(arrinit(pcs, len / LEN, 0)))
		kill_all(&line, NULL, NULL, NULL);
	ch = 'A';
	pccount = 0;
	i = 0;
	while (i < len)
	{
		if (!(save_piece(ft_strsub(line, i, LEN), (*pcs + pccount), ch)))
			kill_all(&line, pcs, NULL, NULL);
		pccount++;
		i += LEN;
		ch++;
	}
	free(line);
	return (pccount);
}

int			main(int argc, char **argv)
{
	t_tetra	*pcs;
	int		size;
	int		pccount;

	if (argc != 2)
	{
		write(1, "usage: ./fillit <filename>\n", 27);
		return (1);
	}
	pcs = NULL;
	pccount = create_arr(argv[1], &pcs);
	size = (ft_sqrt(pccount * 4, 1) + 2);
	mapinator(pcs, pccount, size);
}
