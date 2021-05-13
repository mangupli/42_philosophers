#include "philo_two.h"

/*
** Here I use the following solution for the dining philosopher problem:
** hierarchy of resources -> the resources (waiter) are numbered 1 through
** number_of_philosophers. Each unit of work (philosopher) will always pick up
** the lower-numbered fork first, and then the higher-numbered fork,
** from among the two waiter they plan to use.
*/

void	put_down_forks(long num)
{
	(void)num;
	sem_post(g_data.waiter);
}

void	get_forks(long num)
{
	sem_wait(g_data.waiter);
	display_message(get_time(), num + 1, TAKE_FORK);
	display_message(get_time(), num + 1, TAKE_FORK);
	g_data.phil[num].last_meal = get_time();
	display_message(g_data.phil[num].last_meal, num + 1, EAT);
	usleep(g_data.time_to_eat * 1000);
}
