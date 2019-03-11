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
		exit (0);
	close(fd);
}

static int	move_piece(char *ln16)
{
	int	i;
	int	j;
	int	shiftup;
	int	shiftleft;

	shiftup = 0;
	i = -1;
	while (ln16[++i])
	{
		/* check for empty rows */
		if (ln16[i] == '#')
			break;
	}
	if (i > PIECESIDE)
		shiftup = (i / PIECESIDE);
	shiftleft = PIECESIDE;
	i = -1;
	/* check for empty positions to the left */
	while (++i < PIECESIDE)
	{
		j = -1;
		while (++j < PIECESIDE)
			if (ln16[i * PIECESIDE + j] == '#' && j < shiftleft)
				shiftleft = j;
	}
	return (shiftup * PIECESIDE + shiftleft);
}

static int	save_piece(char *ln16, t_tetra **pieces)
{
	int	i;
	int	x;
	int	y;
	int	shift;

	shift = move_piece(ln16);
	ln16 = ft_strcpy(ln16, ln16 + shift);
	i = PIECELEN - 1;
	while (shift--)
		ln16[i--] = '.';
	i = -1;
	x = 0;
	y = 0;
	while (ln16[++i])
	{
		if (ln16[i] != '#' && ln16[i] != '.')
			return (0);
		(*pieces)->config[y][x] = ln16[i];
		x++;
		if ((i + 1) % 4 == 0)
		{
			x = 0;
			y++;
		}
	}
	return (1);
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
		if (!(lstadd(pieces)) || !(save_piece(ft_strsub(line, i, PIECELEN), pieces)))
		{
			lstdel(pieces);
			exit(103);
		}
		npcs++;
		i += PIECELEN;
	}
	return (npcs);
}

int			main(int argc, char **argv)
{
	t_tetra	*pieces;
	int		npcs;
	int		i;		// KILLME
	t_tetra	*tmp;	// KILLME
//	char	*square;

	if (argc != 2)
		write(1, "usage: ./fillit <filename>\n", 27);
	npcs = create_tetra_list(argv[1], &pieces);

	/* print pieces list */
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
}
