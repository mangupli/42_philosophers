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
	usleep(g_data.time_to_eat * 1000);
}
