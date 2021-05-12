#include "philo_one.h"

void	*phi_life(void *a)
{
	long	num;
	long	next;

	num = (long)a;
	while (1)
	{
		if (g_data.must_eat == 0 \
		|| (g_data.must_eat != 0 && g_data.phil[num].meals < g_data.must_eat))
		{
			if (num == g_data.p)
				next = 0;
			else
				next = num + 1;
			get_forks(num);
			g_data.phil[num].meals++;
			put_down_forks(num);
			display_message(get_time(), num + 1, SLEEP);
			usleep(g_data.time_sleep * 1000);
			display_message(get_time(), num + 1, THINK);
		}
		else
			break ;
	}
	return (NULL);
}

void	*check_death(void *a)
{
	ms_type	time;
	int		i;

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

void	*finish_meal(void *a) // TODO: doesnt start if must_eat == 0
{
	int	i;

	while (1)
	{
		i = -1;
		while (++i < g_data.p)
		{
			if (g_data.phil[i].meals < g_data.must_eat)
				break ;
			else if (i + 1 == g_data.p)
			{
				display_message(get_time(), 0, FINISH);
				exit(EXIT_SUCCESS);
			}
		}
	}
	return (NULL);
}

int monitor_threads()
{
	void	*result;

	if (pthread_create(&g_data.death, NULL, check_death, NULL) == -1)
		return(ft_error("Can't create a thread"));
	if (g_data.must_eat != 0)
	{
		if (pthread_create(&g_data.meal, NULL, finish_meal, NULL) == -1)
			return (ft_error("Can't create a thread"));
	}
	if (pthread_join(g_data.death, &result) == -1)
		return(ft_error("Can't join a thread"));
	if (g_data.must_eat != 0)
	{
		if (pthread_join(g_data.meal, &result) == -1)
			return (ft_error("Can't join a thread"));
	}
	return (EXIT_SUCCESS);
}

int philo_threads()
{
	long i;

	i = -1;
	while (++i < g_data.p)
	{
		if (pthread_create(&g_data.phil[i].t, NULL, phi_life, (void *) i) == -1)
			return (ft_error("Can't create a thread"));
		if (pthread_detach(g_data.phil[i].t))
			return (ft_error("Can't detach a thread"));
	}
	return (EXIT_SUCCESS);
}

int	main(int argc, char **argv)
{
	long	i;

	if (init(argc, argv) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	if (philo_threads() == EXIT_FAILURE)
		return (EXIT_FAILURE);
	if (monitor_threads() == EXIT_FAILURE)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
