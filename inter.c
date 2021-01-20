#include <unistd.h>
#include <stdio.h>

int main(int ac, char **av)
{
    int i;
    int j;
    int len;
    char tab[100];
    
    tab[0] = 0;
    if (ac != 3)
    {
        write(1, "\n", 1);
        return (0);
    }
    i = 0;
    while (av[1][i] != 0)
    {
        j = 0;
        while (tab[j] != 0)
        {
            if (tab[j] == av[1][i])
                break;
            j++;
        }
        if (tab[j] == 0)
        {
            tab[j] = av[1][i];
            tab[j + 1] = 0;
        }
        i++;
    }
    i = 0;
    len = 0;
    while (tab[len] != 0)
        len++;
//    printf("%d", len);
    while (i < len)
    {
        j = 0;
        while (av[2][j] != 0)
        {    
            if (tab[i] == av[2][j])
            {
                write(1, &av[2][j], 1);
                tab[i] = 0;
            }
            j++;
        }
        i++;
    }
    write(1, "\n", 1);
    return (0);
}