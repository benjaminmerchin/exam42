#include <unistd.h>

int main(int ac, char **av)
{
    char tab[100];
    int i;
    int j;

    tab[0] = 0;
    if (ac != 3)
    {
        write(1, "\n", 1);
        return (0);
    }
    i = 0;
    while (av[1][i] != '\0')
    {
        j = 0; 
        while (tab[j] != 0)
        {
            if (tab[j] == av[1][i])
                break ;
            else
                j++;
        }
        if (tab[j] == 0)
        {
            tab[j] = av[1][i];
            tab[j + 1] = 0;
            write(1, &av[1][i], 1);
        }
        i++;
    }
    i = 0;
    while (av[2][i] != '\0')
    {
        j = 0; 
        while (tab[j] != 0)
        {
            if (tab[j] == av[2][i])
                break ;
            else
                j++;
        }
        if (tab[j] == 0)
        {
            tab[j] = av[2][i];
            tab[j + 1] = 0;
            write(1, &av[2][i], 1);
        }
        i++;
    }
    write(1, "\n", 1);
    return (0);
}