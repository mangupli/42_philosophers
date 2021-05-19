#include "philo_two.h"

static int	create_philo_threads(void)
{
	long		i;

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

static void	*check_death(void *a)
{
	time_t	time;
	int		i;
	int		count_full;

	(void)a;
	while (1)
	{
		i = -1;
		count_full = 0;
		while (++i < g_data.p)
		{
			time = get_time();
			sem_wait(g_data.write);
			if (g_data.phil[i].last_meal + g_data.time_to_die < time)
				return (display_message(time, i, DIE));
			sem_post(g_data.write);
			count_full += g_data.phil[i].full;
			if (count_full == g_data.p)
			{
				sem_wait(g_data.write);
				return (display_message(time, i, FINISH));
			}
		}
	}
}

static int	create_monitor_thread(void)
{
	void	*result;

	if (pthread_create(&g_data.death, NULL, check_death, NULL) == -1)
		return (ft_error("Can'thread create a thread"));
	if (pthread_join(g_data.death, &result) == -1)
		return (ft_error("Can'thread join a thread"));
	return (EXIT_SUCCESS);
}

int	main(int argc, char **argv)
{
	if (init(argc, argv) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	if (g_data.must_eat != 0)
	{
		if (create_philo_threads() == EXIT_FAILURE)
			return (ft_exit(EXIT_FAILURE));
		if (create_monitor_thread() == EXIT_FAILURE)
			return (ft_exit(EXIT_FAILURE));
	}
	return (ft_exit(EXIT_SUCCESS));
}
