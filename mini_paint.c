#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <math.h>

typedef struct s_a {
	FILE *file;
	int	ret;
	char **tab;
	int	ret_fscanf;
	float dist;

	int b_width;
	int b_height;
	char b_char;

	char type;
	float x;
	float y;
	float radius;
	char c_char;
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

float	dist_calc(float i, float j, float x, float y)
{
	return ((x - j) * (x - j) + (y - i) * (y - i));
}

void	am_i_inside(t_a *a, int i, int j)
{
	a->dist = sqrtf(dist_calc((float)i, (float)j, a->x, a->y));
	if (a->dist > a->radius)
		return ;
	if (1.00000000 > a->radius - a->dist)
		a->tab[i][j] = a->c_char;
	if (a->type == 'C')
		a->tab[i][j] = a->c_char;
}

void	add_operation(t_a *a)
{
	if (a->radius <= 0.00000000 || (a->type != 'c' && a->type != 'C'))
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
	while((a->ret_fscanf = fscanf(a->file, "%c %f %f %f %c\n", &a->type, &a->x, &a->y, &a->radius, &a->c_char)) == 5 && a->ret == 0)
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
