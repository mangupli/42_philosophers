#include "philo_one.h"

void	put_down_forks(long num)
{
	long	next;
	long	first;
	long	second;

	if (num == g_data.p)
		next = 0;
	else
		next = num + 1;
	if (next < num)
	{
		first = num;
		second = next;
	}
	else
	{
		first = next;
		second = num;
	}
	pthread_mutex_unlock(&g_data.phil[first].fork);
	pthread_mutex_unlock(&g_data.phil[second].fork);
}

void	get_forks(long num)
{
	long	next;
	long	first;
	long	second;

	if (num == g_data.p)
		next = 0;
	else
		next = num + 1;
	if (next > num)
	{
		first = num;
		second = next;
	}
	else
	{
		first = next;
		second = num;
	}
	pthread_mutex_lock(&g_data.phil[first].fork);
	display_message(get_time(), num + 1, TAKE_FORK);
	pthread_mutex_lock(&g_data.phil[second].fork);
	display_message(get_time(), num + 1, TAKE_FORK);
	g_data.phil[num].last_meal = get_time();
	display_message(g_data.phil[num].last_meal, num + 1, EAT);
	usleep(g_data.time_eat * 1000);
}