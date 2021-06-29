#include "get_next_line.h"

int main(int ac, char **av)
{
    int fd;
    int retour;
    char *line;
    
    (void)av;
    if (ac != 1)
    {
        printf("Mauvais nbr d'arguments\n");
        return (0);
    }
//    fd = open(av[1], O_RDONLY);
    while ((retour = get_next_line(&line)) == 1)
    {
        printf("%s\n", line);
        write(1, "ok\n", 3);
        free(line);
    }
    if (line[0] != 0)
    {
        printf("%s\n", line);
        free(line);
    }
    return (0);
}
