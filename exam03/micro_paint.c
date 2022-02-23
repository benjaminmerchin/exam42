#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

typedef struct s_a {
	FILE *file;
	int	ret;
	char **tab;
	int	ret_fscanf;

	int b_width;
	int b_height;
	char b_char;

	char type;
	float x;
	float y;
	float r_width;
	float r_height;
	char r_char;
} t_a;

void	ft_putchar(char c)
{
	write(1, &c, 1);
}

void	ft_putstr(char *str)
{
	int i;

	i = 0;
	while(str[i])
		ft_putchar(str[i++]);
}

void	am_i_inside(t_a *a, int i, int j)
{
	if (j < a->x || j > a->x + a->r_width || i < a->y || i > a->y + a->r_height)
		return ;
	if (j - a->x < 1.00000000 || 1.00000000 > (a->x + a->r_width - j) || i - a->y < 1.00000000 || 1.00000000 > (a->y + a->r_height - i))
		a->tab[i][j] = a->r_char;
	if (a->type == 'R')
		a->tab[i][j] = a->r_char;
}

void	add_operation(t_a *a)
{
	if (a->r_width <= 0.00000000 || a->r_height <= 0.00000000 || (a->type != 'r' && a->type != 'R'))
	{
		a->ret = 1;
		return ;
	}
	int i = 0;
	int j;
	while (i < a->b_height)
	{
		j = 0;
		while(j < a->b_width)
			am_i_inside(a, i, j++);
		i++;
	}
}

void	execute(t_a *a)
{
	if(fscanf(a->file, "%d %d %c\n", &a->b_width, &a->b_height, &a->b_char) != 3)
	{
		a->ret = 1;
		return ;
	}
	if (a->b_width < 1 || a->b_width > 300 || a->b_height < 1 || a->b_height > 300)
	{
		a->ret = 1;
		return ;	
	}
	a->tab = malloc(sizeof(char *) * a->b_height);
	int i = 0;
	int j;
	while (i < a->b_height)
	{
		a->tab[i] = malloc(sizeof(char) * a->b_width);
		j = 0;
		while(j < a->b_width)
			a->tab[i][j++] = a->b_char;
		i++;
	}
	while((a->ret_fscanf = fscanf(a->file, "%c %f %f %f %f %c\n", &a->type, &a->x, &a->y, &a->r_width, &a->r_height, &a->r_char)) == 6 && a->ret == 0)
	{
		add_operation(a);
	}
	if (a->ret_fscanf == -1 && a->ret == 0)
	{
		i = 0;
		while (i < a->b_height)
		{
			j = 0;
			while(j < a->b_width)
				ft_putchar(a->tab[i][j++]);
			ft_putchar('\n');
			i++;
		}
		return ;
	}
	a->ret = 1;
}

int main(int ac, char **av)
{
	t_a a;

	a.ret = 0;
	if (ac != 2)
	{
		ft_putstr("Error: argument\n");
		return (1);
	}
	if (!(a.file = fopen(av[1], "r")))
	{
		ft_putstr("Error: Operation file corrupted\n");
		return (1);
	}
	execute(&a);
	fclose(a.file);
	if (a.ret == 1)
		ft_putstr("Error: Operation file corrupted\n");
	return (a.ret);
}
