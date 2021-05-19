#include "philo_two.h"

static void	sleep_and_think(long num)
{
	sem_wait(g_data.write);
	display_message(get_time(), num, SLEEP);
	sem_post(g_data.write);
	ft_usleep(g_data.time_to_sleep);
	sem_wait(g_data.write);
	display_message(get_time(), num, THINK);
	sem_post(g_data.write);
}

static void	put_down_forks(long num)
{
	long	next;

	if (num == g_data.p - 1)
		next = 0;
	else
		next = num + 1;
	sem_post(g_data.forks);
	sem_post(g_data.forks);
}

static void	get_forks_and_eat(long num)
{
	long	next;

	if (num == g_data.p - 1)
		next = 0;
	else
		next = num + 1;
	sem_wait(g_data.forks);
	sem_wait(g_data.write);
	display_message(get_time(), num, TAKE_FORK);
	sem_post(g_data.write);
	sem_wait(g_data.forks);
	g_data.phil[num].last_meal = get_time();
	sem_wait(g_data.write);
	display_message(g_data.phil[num].last_meal, num, TAKE_FORK);
	display_message(g_data.phil[num].last_meal, num, EAT);
	sem_post(g_data.write);
	ft_usleep(g_data.time_to_eat);
}

void	*phi_life(void *a)
{
	long	num;
	int		meals;

	meals = 0;
	num = (long)a;
	if ((num + 1) % 2 == 0)
		ft_usleep(g_data.time_to_eat);
	while (1)
	{
		if (g_data.must_eat == -1 || g_data.phil[num].full != 1 )
		{
			get_forks_and_eat(num);
			meals++;
			if (g_data.must_eat >= 0 && meals >= g_data.must_eat)
				g_data.phil[num].full = 1;
			put_down_forks(num);
			sleep_and_think(num);
		}
		else
			break ;
	}
	return (NULL);
}
