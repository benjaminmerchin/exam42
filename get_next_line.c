#include "get_next_line.h"

int ft_strlen(char *str)
{
    int i;

    i = 0;
    while (str[i] != 0)
        i++;
    return (i);
}

char *ft_strjoin(char *s1, char *s2)
{
    char *new;
    int i;

    new = malloc(ft_strlen(s1) + 2);
    if (!new)
    {
        free(s1);
        return (NULL);
    }
    i = 0;
    while (s1[i] != 0)
    {
        new[i] = s1[i];
        i++;
    }
    new[i] = s2[0];
    new[i + 1] = 0;
    free(s1);
    return (new);
}

int get_next_line(char **line)
{
    char buff[2];
    int ret;

    buff[1] = 0;
    *line = (char *)malloc(sizeof(char));
    if (!*line)
        return (-1);
    *line[0] = 0;
    while ((ret = read(0, buff, 1)) == 1)
    {
        if (buff[0] == '\n')
            break ;
        else
            *line = ft_strjoin(*line, buff);
        if (*line == NULL)
        {
            free(*line);
            return (-1);
        }
    }
    if (ret == 0)
        return (0);
    if (ret == -1)
    {
        free(*line);
        return (-1);
    }
    return (1);
}
