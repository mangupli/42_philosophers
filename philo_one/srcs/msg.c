#include "philo_one.h"

void	ft_putchar(char c)
{
	write(1, &c, 1);
}

void	ft_putstr(char *s)
{
	if (s != NULL)
		write(1, s, ft_strlen(s));
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

static void	print_msg(t_ms time, int no, char *str)
{
	ft_putunbr(time);
	ft_putchar(' ');
	if (no)
	{
		ft_putunbr(no);
		ft_putchar(' ');
	}
	ft_putstr(str);
	ft_putchar ('\n');
}

int	display_message(t_ms ms, int no, int act)
{
	t_ms	time;

	time = ms - g_data.start_time;
	pthread_mutex_lock(&g_data.write);
	if (act == TAKE_FORK)
		print_msg(time, no, "has taken a fork");
	else if (act == EAT)
		print_msg(time, no, "is eating");
	else if (act == SLEEP)
		print_msg(time, no, "is sleeping");
	else if (act == THINK)
		print_msg(time, no, "is thinking");
	else if (act == DIE)
		print_msg(time, no, "died");
	else if (act == FINISH)
		print_msg(time, no, "my philosophers are full");
	pthread_mutex_unlock(&g_data.write);
	return (EXIT_SUCCESS);
}
