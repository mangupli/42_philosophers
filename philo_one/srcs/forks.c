#include "philo_one.h"

/*
** Here I use the following solution for the dining philosopher problem:
** hierarchy of resources -> the resources (forks) are numbered 1 through
** number_of_philosophers. Each unit of work (philosopher) will always pick up
** the lower-numbered fork first, and then the higher-numbered fork,
** from among the two forks they plan to use.
*/


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
	pthread_mutex_lock(&g_data.write);
	display_message(get_time(), num, TAKE_FORK);
	g_data.phil[num].last_meal = get_time();
	display_message(g_data.phil[num].last_meal, num, EAT);
	pthread_mutex_unlock(&g_data.write);
	ft_usleep(g_data.time_to_eat);
}
