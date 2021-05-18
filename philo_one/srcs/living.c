#include "philo_one.h"

static void	sleep_and_think(long num)
{
	pthread_mutex_lock(&g_data.write);
	display_message(get_time(), num, SLEEP);
	pthread_mutex_unlock(&g_data.write);
	ft_usleep(g_data.time_to_sleep);
	pthread_mutex_lock(&g_data.write);
	display_message(get_time(), num, THINK);
	pthread_mutex_unlock(&g_data.write);
}

static void	put_down_forks(long num)
{
	long	next;

	if (num == g_data.p - 1)
		next = 0;
	else
		next = num + 1;
	pthread_mutex_unlock(&g_data.phil[next].fork);
	pthread_mutex_unlock(&g_data.phil[num].fork);
}

static void	get_forks_and_eat(long num)
{
	long	next;

	if (num == g_data.p - 1)
		next = 0;
	else
		next = num + 1;
	pthread_mutex_lock(&g_data.phil[num].fork);
	pthread_mutex_lock(&g_data.write);
	display_message(get_time(), num, TAKE_FORK);
	pthread_mutex_unlock(&g_data.write);
	pthread_mutex_lock(&g_data.phil[next].fork);
	g_data.phil[num].last_meal = get_time();
	pthread_mutex_lock(&g_data.write);
	display_message(g_data.phil[num].last_meal, num, TAKE_FORK);
	display_message(g_data.phil[num].last_meal, num, EAT);
	pthread_mutex_unlock(&g_data.write);
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
		if (g_data.must_eat == -1 \
		|| (g_data.must_eat != -1 && meals < g_data.must_eat))
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
