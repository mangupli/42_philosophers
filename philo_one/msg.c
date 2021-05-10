#include "philo_one.h"

int ft_strlen(char *str)
{
    int i;

    i = 0;
    while (str[i])
        i++;
    return (i);
}

void	ft_putstr(char *s)
{
	if (s != NULL)
		write(1, s, ft_strlen(s));
}

void ft_putchar(char c)
{
    write(1, &c, 1);
}

void	ft_putunbr(uintmax_t n)
{
	char	c;

	if (n < 10)
	{
		c = n + '0';
		ft_putchar(c);
	}
	else
	{
		ft_putunbr(n / 10);
		ft_putunbr(n % 10);
	}
}

void print_msg(ms_type time, int no, char *str)
{
    ft_putunbr(time);
    ft_putchar(' ');
    ft_putunbr(no);
    ft_putchar(' ');
    ft_putstr(str);
    ft_putchar ('\n');
}