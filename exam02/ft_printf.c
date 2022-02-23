#include <unistd.h>
#include <stdio.h>
#include <stdarg.h>

typedef struct s_data {
    va_list args;
    int ret;
    int i;
    char *str;

    int width_flag;
    int width;    
    int prec_flag;
    int prec;
    int len;
}   t_data;

void ft_putchar(t_data *data, char c)
{
    write(1, &c, 1);
    data->ret++;
}

void struct_reset(t_data *data)
{
    data->width_flag = 0;
    data->width = 0;    
    data->prec_flag = 0;
    data->prec = 0;
    data->len = 0;
}

int lenhex(unsigned int nbr)
{
    int len = 1;

    while (nbr >= 16)
    {
        len++;
        nbr = nbr / 16;
    }
    return (len);
}

int lenint(long nbr)
{
    int len = 1;

    if (nbr < 0)
        nbr = -nbr;
    while (nbr >= 10)
    {
        len++;
        nbr = nbr / 10;
    }
    return (len);
}

void putnbrhex(t_data *data, unsigned int nbr)
{
    char *base = "0123456789abcdef";

    if (nbr >= 16)
        putnbrhex(data, nbr / 16);
    ft_putchar(data, base[nbr % 16]);
}

void putnbrint(t_data *data, long nbr)
{
    char *base = "0123456789";

    if (nbr >= 10)
        putnbrint(data, nbr / 10);
    ft_putchar(data, base[nbr % 10]);
}

int ft_atoi(t_data *data)
{
    int retour = 0;
    while (data->str[data->i] >= '0' && data->str[data->i] <= '9')
    {
        retour = retour * 10 + data->str[data->i] - '0';
        data->i++;
    }
    return (retour);
}

void putsp(t_data *data, int len)
{
    int i = 0;

    while (i < len)
    {
        ft_putchar(data, ' ');
    }
}

void putzero(t_data *data, int len)
{
    int i = 0;

    while (i < len)
    {
        ft_putchar(data, '0');
    }
}

int ft_strlen(char *str)
{
    int i;
    
    i = 0;
    while (str[i] != '\0')
        i++;
    return (i);
}

void hq_str(t_data *data)
{
    int i = 0;
    int j = 0;
    
    char *s = va_arg(data->args, char *);
    if (s == NULL)
        s = "(null)";
    data->len = ft_strlen(s);
    if (data->prec_flag && data->prec < data->len)
        data->len = data->prec;
    while (i < data->width - data->len)
    {
        ft_putchar(data, ' ');
        i++;
    }
    while (j < data->len)
    {
        ft_putchar(data, s[j]);
        j++;
    }
}

void hq_int(t_data *data)
{
    int i = 0;
    
    long d = (long)va_arg(data->args, int);
    data->len = lenint(d);
    if (d == 0)
        data->len = 1;
    if (d < 0)
        data->len++;
    while (i < data->width - data->len && i < data->width - data->prec)
    {
        ft_putchar(data, ' ');
        i++;
    }
    i = 0;
    if (d < 0)
    {
        ft_putchar(data, '-');
        d = -d;
    }
    while (i < data->prec - data->len && i < data->width - data->prec)
    {
        ft_putchar(data, '0');
        i++;
    }
    if (data->prec_flag && d == 0 && data->prec == 0)
    {
        if (data->width != 0)
            ft_putchar(data, ' ');
        return ;
    }
    putnbrint(data, d);
}

void hq_hex(t_data *data)
{
    int i = 0;
    
    unsigned int x = va_arg(data->args, unsigned int);
    data->len = lenhex(x);
    if (x == 0)
        data->len = 0;
    while (i < data->width - data->len && i < data->width - data->prec)
    {
        ft_putchar(data, ' ');
        i++;
    }
    i = 0;
    while (i < data->prec - data->len)
    {
        ft_putchar(data, '0');
        i++;
    }
    if (data->prec_flag && x == 0)
        return ;
    putnbrhex(data, x);
}

void parsor(t_data *data)
{
    data->i = data->i + 1;
    struct_reset(data);
    if ((data->str[data->i] >= '0' && data->str[data->i] <= '9') || data->str[data->i] <= '-')
    {
        if (data->str[data->i] <= '-')
            data->i++;
        data->width_flag = 1;
        data->width = ft_atoi(data);
    }
    if (data->str[data->i] == '.')
    {
        data->i++;
        if (data->str[data->i] == '-')
            data->i++;
        data->prec_flag = 1;
        data->prec = ft_atoi(data);
    }
    if (data->str[data->i] == 'd')
        hq_int(data);
    if (data->str[data->i] == 's')
        hq_str(data);
    if (data->str[data->i] == 'x')
        hq_hex(data);
//    printf(">>>%d<<<", data->prec);
}

int ft_printf(const char *str, ... )
{
    t_data data;

    data.ret = 0;
    data.i = 0;
    data.str = (char *)str;
    va_start(data.args, str);
    while (data.str[data.i] != 0)
    {
        if (data.str[data.i] == '%')
            parsor(&data);
        else 
            ft_putchar(&data, data.str[data.i]);
        data.i++;
    }
    va_end(data.args);
    return (data.ret);
}

int main(void)
{
    int a = 123;
    char *str = "%8.3d_____%1.0x_____%6.2s\n";

    ft_printf(str, a, a, str);
    printf("--------------------\n");
    printf(str, a, a, str);
    return (0);
}
