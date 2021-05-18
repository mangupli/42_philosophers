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

static void	print_msg(long time, int no, char *str)
{
	int i;

	ft_putunbr(time);
	ft_putchar(' ');
	i = -1;
	while (++i < no)
		ft_putstr("                ");
	if (no)
	{
		ft_putunbr(no + 1);
		ft_putchar(' ');
	}
	ft_putstr(str);
	ft_putchar ('\n');
}

int	display_message(long ms, int no, int act)
{
	long	time;
	int 	i;

	time = ms - g_data.start_time;
	printf("%ld  ", time);
	i = -1;
	while (++i < no)
		printf("			");
	no += 1;
	if (act == TAKE_FORK)
		printf("%d has taken a fork\n", no);
	else if (act == EAT)
		printf("%d is eating\n", no);
	else if (act == SLEEP)
		printf("%d is sleeping\n", no);
	else if (act == THINK)
		printf("%d is thinking\n", no);
	else if (act == DIE)
		printf("%d died\n", no);
	else if (act == FINISH)
		printf("my philosophers are full\n");
	return (EXIT_SUCCESS);
}
