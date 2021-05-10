#include "philo_one.h"

int display_message(ms_type ms, int no, int act)
{
	//pthread_mutex_lock(&g_data.write);
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
	//pthread_mutex_unlock(&g_data.write);
	return (EXIT_SUCCESS);
}

void *philo_life(void *a)
{
	long num;

	num = (long)a;
	while (1)
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

	while (1)
	{
		i = -1;
		while (++i < g_data.p)
		{
			time = get_time();
			pthread_mutex_lock(&g_data.check);
			if (g_data.phil[i].last_meal + g_data.time_die < time)
			{
				display_message(time, i + 1, DIE);
				exit(EXIT_FAILURE);
			}
			pthread_mutex_unlock(&g_data.check);
		}
	}
	return (NULL);
}

int main(int argc, char **argv)
{
	void *result;
	long i;

	if (init(argc, argv) == EXIT_FAILURE)
		return (EXIT_FAILURE);

	i = -1;
	while (++i < g_data.p)
	{
		if (pthread_create(&g_data.phil[i].t, NULL, philo_life, (void *)i) == -1)
			ft_error("Can't create a thread");
		if (pthread_detach(g_data.phil[i].t))
			ft_error("Can't detach a thread");
			usleep(100);
	}

	if (pthread_create(&g_data.death, NULL, check_death, NULL) == -1)
		ft_error("Can't create a thread");
	if (pthread_join(g_data.death, &result) == -1)
			ft_error("Can't join a thread");
	return (EXIT_SUCCESS);
}


	// if (pthread_detach(g_data.death))
	// 	ft_error("Can't detach a thread");
	// 	usleep(100);

	// i = -1;
	// while (++i < g_data.p)
	// {
	// 	if (pthread_join(g_data.phil[i].t, &result) == -1)
	// 		ft_error("Can't join a thread");
	// }
