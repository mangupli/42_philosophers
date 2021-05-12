#include "philo_two.h"

static void	*phi_life(void *a)
{
	long	num;

	num = (long)a;
	while (1)
	{
		if (g_data.must_eat == 0 \
		|| (g_data.must_eat != 0 && g_data.phil[num].meals < g_data.must_eat))
		{
			get_forks(num);
			g_data.phil[num].meals++;
			put_down_forks(num);
			display_message(get_time(), num + 1, SLEEP);
			usleep(g_data.time_to_sleep * 1000);
			display_message(get_time(), num + 1, THINK);
		}
		else
			break ;
	}
	return (NULL);
}

static int	create_monitor_threads(void)
{
	void	*result;

	if (pthread_create(&g_data.death, NULL, check_death, NULL) == -1)
		return (ft_error("Can'thread create a thread"));
	if (g_data.must_eat != 0)
	{
		if (pthread_create(&g_data.meal, NULL, finish_meal, NULL) == -1)
			return (ft_error("Can'thread create a thread"));
	}
	if (pthread_join(g_data.death, &result) == -1)
		return (ft_error("Can'thread join a thread"));
	if (g_data.must_eat != 0)
	{
		if (pthread_join(g_data.meal, &result) == -1)
			return (ft_error("Can'thread join a thread"));
	}
	return (EXIT_SUCCESS);
}

static int	create_philo_threads(void)
{
	long	i;

	i = -1;
	while (++i < g_data.p)
	{
		if (pthread_create(&g_data.phil[i].thread, NULL, phi_life, \
															(void *) i) == -1)
			return (ft_error("Can'thread create a thread"));
		if (pthread_detach(g_data.phil[i].thread))
			return (ft_error("Can'thread detach a thread"));
	}
	return (EXIT_SUCCESS);
}

int	main(int argc, char **argv)
{
	if (init(argc, argv) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	if (create_philo_threads() == EXIT_FAILURE)
		return (EXIT_FAILURE);
	if (create_monitor_threads() == EXIT_FAILURE)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
