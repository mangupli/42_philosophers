#include "philo_one.h"

int display_message(ms_type ms, int no, int act)
{
	ms_type time;

	time = ms - g_data.start_time;
	pthread_mutex_lock(&g_data.write);
	if (act == TAKE_FORK)
		print_msg(time, no, "has taken a fork");
	else if (act == EAT)
		print_msg(time, no, "is eating");
	else if (act == SLEEP)
		print_msg(time, no, "is sleeping");
	else if (act == THINK)
		print_msg(time, no, "is thinking");
	else if (act == DIE)
		print_msg(time, no, "died");
	pthread_mutex_unlock(&g_data.write);
	return (EXIT_SUCCESS);
}

int get_forks(long num, int flag)
{
	long next;

	if (num == g_data.p)
		next = 0;
	else
		next = num + 1;
	if (flag == UP)
	{
		pthread_mutex_lock(&g_data.lock);
		
		if (g_data.forks[num] == 1 || g_data.forks[next] == 1)
		{
			g_data.forks[num] = 0;
			display_message(get_time(), num + 1, TAKE_FORK);
			g_data.forks[next] = 0;
			display_message(get_time(), num + 1, TAKE_FORK);
			pthread_mutex_unlock(&g_data.lock);
		}
		else
		{
			pthread_mutex_unlock(&g_data.lock);
			return (EXIT_FAILURE);
		}
	}
	else if (flag == DOWN)
	{
		g_data.forks[num] = 1;
		g_data.forks[next] = 1;
	}
	return (EXIT_SUCCESS);
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
		if (get_forks(num, UP) == EXIT_FAILURE)
			continue;
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

void *check_death(void *a) // TODO: add meal limit
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

int main(int argc, char **argv) // TODO: 4 410 200 200 test doesnt pass
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
