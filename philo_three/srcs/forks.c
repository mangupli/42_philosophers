#include "philo_three.h"

/*
** Here I use the following solution for the dining philosopher problem:
** waiter -> before taking forks, philosopher smust ask waiter if it has 
** the right number of forks
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
