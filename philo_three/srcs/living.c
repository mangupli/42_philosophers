#include "philo_three.h"

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

void	*phi_life(int num)
{
	int		meals;
	int		full;

	if (create_monitor_thread(num) == EXIT_FAILURE)
	{
		ft_exit(EXIT_FAILURE);
		return (NULL);
	}
	meals = 0;
	full = 0;
	if ((num + 1) % 2 == 0)
		ft_usleep(g_data.time_to_eat);
	while (1)
	{
		get_forks_and_eat(num);
		meals++;
		if (g_data.must_eat >= 0 && meals >= g_data.must_eat)
			full = 1;
		put_down_forks(num);
		if (full == 1)
		{
			sem_post(g_data.write);
			exit(EXIT_SUCCESS);
		}
		sleep_and_think(num);
	}
	return (NULL);
}
