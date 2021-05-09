#include "philo_one.h"

int display_message(ms_type ms, int no, int act)
{
	if (act == TAKE_FORK)
		printf("%llu %d %s\n", ms, no, "has taken a fork");
	if (act == EAT)
		printf("%llu %d %s\n", ms, no, "is eating");
	if (act == SLEEP)
		printf("%llu %d %s\n", ms, no, "is sleeping");
	if (act == THINK)
		printf("%llu %d %s\n", ms, no, "is thinking");
	if (act == DIE)
		printf("%llu %d %s\n", ms, no, "died");
	return (EXIT_SUCCESS);
}

void *philo_life(void *a)
{
	int num;

	num = -1;
	while (++num < g_data.p)
	{
		display_message(get_time(), num + 1, TAKE_FORK);
		display_message(get_time(), num + 1, TAKE_FORK);
		g_data.phil[num].last_meal = get_time();
		display_message(get_time(), num + 1, EAT);
		usleep(g_data.time_eat * 1000);
		display_message(get_time(), num + 1, SLEEP);
		usleep(g_data.time_sleep * 1000);
		display_message(get_time(), num + 1, THINK);
	}
	return (NULL);
}

void *check_death(void *a)
{
	ms_type time;
	int i;

	//pthread_detach(g_data.death);
	while (1)
	{
		time = get_time();
		i = -1;
		while (++i < g_data.p)
		{
			if (time - g_data.phil[i].last_meal >= g_data.time_die)
			{
				display_message(get_time(), i + 1, DIE);
				exit(EXIT_FAILURE);
			}
		}
	}
	return (NULL);
}

int main(int argc, char **argv)
{
	void *result;

	if (init(argc, argv) == EXIT_FAILURE)
		return (EXIT_FAILURE);

	if (pthread_create(&g_data.phil[0].t, NULL, philo_life, NULL) == -1)
		ft_error("Can't create a thread");
	if (pthread_join(g_data.phil[0].t, &result) == -1)
		ft_error("Can't join a thread");
	if (pthread_create(&g_data.death, NULL, check_death, NULL) == -1)
		ft_error("Can't create a thread");

	return (EXIT_SUCCESS);
}