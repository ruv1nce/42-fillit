#include "fillit.h"

int	put_piece(char **map, t_tetra *pc);

void	print_tab(char **area)
{
	int	i;
	int	j;

	i = 0;
	while (area[i])
	{
//		printf("%s\n", *area);
		j = 0;
		while (area[i][j])
		{
			write(1, &area[i][j], 1);
			if (area[i][j])
				write(1, " ", 1);
			j++;
		}
		write(1, "\n", 1);
		i++;
	}
}


int main(void)
{
	t_tetra	pc;
    char **map;

    map = create_map(4);
	map[0][0] = 'A';
	map[0][1] = 'A';
	map[0][2] = 'A';
	map[0][3] = 'A';
	map[1][0] = 'C';
	map[2][0] = 'C';
	map[2][1] = 'C';
	map[2][2] = 'C';
	map[2][3] = 'C';
	map[3][0] = 'C';
	pc.put = 0;
	pc.c = 'B';
	pc.x[0] = 1;
	pc.y[0] = 0;
	pc.x[1] = 1;
	pc.y[1] = 1;
	pc.x[2] = 0;
	pc.y[2] = 2;
	pc.x[3] = 1;
	pc.y[3] = 2;
    print_tab(map);
	printf("%i\n", put_piece(map, &pc));
    print_tab(map);
}
