#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdarg.h>

typedef struct  s_struct
{
    va_list args;
    int i;
    int ret;
    char *str;

    int d;
    unsigned int x;
    int s;

    int width_flag;
    int width;
    int prec_flag;
    int prec;
    int len;
}               t_struct;

void    struct_reset(t_struct *data)
{
    data->width_flag = 0;
    data->prec_flag = 0;
    data->width = 0;
    data->prec = 0;
    data->len = 0;
}

void ft_putchar(t_struct *data, char c)
{
    write(1, &c, 1);
    data->ret = data->ret + 1;
}

int len_int(int i)
{
    int len;
    
    len = 1;
    if (i < 0)
        i = -i;
    while (i >= 10)
    {
        i = i / 10;
        len++;
    }
    return(len);
}

int len_hex(int i)
{
    int len;
    
    len = 1;
    if (i < 0)
        i = -i;
    while (i >= 16)
    {
        i = i / 16;
        len++;
    }
    return(len);
}

void putnbrint(int nb, t_struct *data)
{
    char *base = "0123456789";
    
    if (nb < 0)
        nb = - nb;
    if (nb >= 10)
        putnbrint(nb / 10, data);
    ft_putchar(data, base[nb % 10]);
}

void putnbrhex(unsigned int nb, t_struct *data)
{
    char *base = "0123456789ABCDEF";
    
    if (nb < 0)
        nb = - nb;
    if (nb >= 16)
        putnbrint(nb / 16, data);
    ft_putchar(data, base[nb % 16]);
}

int ft_atoi(t_struct *data)
{
    int result;

    result = 0;
    while (data->str[data->i] >= '0' && data->str[data->i] <= '9')
    {
        result = result * 10 + data->str[data->i] - '0';
        data->i = data->i + 1;
    }
    return (result);
}

void hq_int(t_struct *data)
{
    int i;
    
    i = 0;
    data->d = va_arg(data->args, int);
    data->len = len_int(i);
    putnbrint(data->d, data);
}

void hq_hex(t_struct *data)
{
    int i;
    
    i = 0;
    data->x = va_arg(data->args, unsigned int);
    data->len = len_hex(i);
    putnbrhex(data->x, data);
}

void hq_str(t_struct *data)
{
    int i;
    
    i = 0;
    data->d = va_arg(data->args, int);
    data->len = len_int(i);
    putnbrint(data->d, data);
}

void parsor(t_struct *data)
{
    data->i = data->i + 1;
    struct_reset(data);
    if (data->str[data->i] >= '0' && data->str[data->i] <= '9')
    {
        data->width_flag = 1;
        data->width = ft_atoi(data);
    }
    if (data->str[data->i] == '.')
    {
        data->i = data->i + 1;
        data->prec_flag = 1;
        data->prec = ft_atoi(data);
    }
    if (data->str[data->i] == 'd')
        hq_int(data);
    if (data->str[data->i] == 's')
        hq_str(data);
    if (data->str[data->i] == 'x')
        hq_hex(data);
/*    printf("width %d \n", data->width);
    printf("prec %d \n", data->prec);*/
}

int ft_printf(const char *str, ... )
{
    t_struct data;

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
        data.i = data.i + 1;
    }
    va_end(data.args);
    return (data.ret);
}

int main(void)
{
    ft_printf("%123.1234dsas", 1);
    return (0);
}