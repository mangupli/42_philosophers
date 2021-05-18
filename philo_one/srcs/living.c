#include "philo_one.h"

void	put_down_forks(long num)
{
	long next;

	if (num == g_data.p - 1)
		next = 0;
	else
		next = num + 1;
	pthread_mutex_unlock(&g_data.phil[next].fork);
	pthread_mutex_unlock(&g_data.phil[num].fork);
}

void	get_forks_and_eat(long num)
{
	long next;

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
