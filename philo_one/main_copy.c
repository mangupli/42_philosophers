#include "philo_one.h"

int display_message(ms_type ms, int no, int act)
{
	pthread_mutex_lock(&g_data.write);
	if (act == TAKE_FORK)
		printf("%8.llu %d %s\n", ms - g_data.start_time, no, "has taken a fork");
	else if (act == EAT)
		printf("%8.llu %d %s\n", ms - g_data.start_time, no, "is eating");
	else if (act == SLEEP)
		printf("%8.llu %d %s\n", ms - g_data.start_time, no, "is sleeping");
	else if (act == THINK)
		printf("%8.llu %d %s\n", ms - g_data.start_time, no, "is thinking");
	else if (act == DIE)
		printf("%8.llu %d %s\n", ms - g_data.start_time, no, "died");
	pthread_mutex_unlock(&g_data.write);
	return (EXIT_SUCCESS);
}

void get_forks(long num, int flag)
{
	long next;

	

	if (num == g_data.p)
		next = 0;
	else
		next = num + 1;
	if (flag == UP)
	{
		pthread_mutex_lock(&g_data.lock);
		pthread_mutex_lock(&g_data.phil[num].fork);
		display_message(get_time(), num + 1, TAKE_FORK);
		pthread_mutex_lock(&g_data.phil[next].fork);
		display_message(get_time(), num + 1, TAKE_FORK);
		pthread_mutex_unlock(&g_data.lock);
	}
	else if (flag == DOWN)
	{
		pthread_mutex_unlock(&g_data.phil[num].fork);
		pthread_mutex_unlock(&g_data.phil[next].fork);
	}
}

void *philo_life(void *a)
{
	long num;
	long next;

	num = (long)a;
	while (1)
	{
		if (num == g_data.p)
		next = 0;
		else
		next = num + 1;
		get_forks(num, UP);
		g_data.phil[num].last_meal = get_time();
		display_message(g_data.phil[num].last_meal, num + 1, EAT);
		usleep(g_data.time_eat * 1000);
		get_forks(num, DOWN);
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
			if (g_data.phil[i].last_meal + g_data.time_die < time)
			{
				display_message(time, i + 1, DIE);
				exit(EXIT_FAILURE);
			}
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
			//usleep(100);
	}

	if (pthread_create(&g_data.death, NULL, check_death, NULL) == -1)
		ft_error("Can't create a thread");
	if (pthread_join(g_data.death, &result) == -1)
		ft_error("Can't join a thread");
	return (EXIT_SUCCESS);
}
