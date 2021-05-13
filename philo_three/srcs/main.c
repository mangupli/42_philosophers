#include "philo_three.h"

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
			exit (EXIT_SUCCESS);
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

static int	create_philo_processes(void)
{
	long	i;
	int		status;
	int		ret;

	i = -1;
	ret = EXIT_SUCCESS;
	while (++i < g_data.p)
	{
		g_data.phil[i].pid = fork();
		if (g_data.phil[i].pid < 0)
			return (ft_error("Couldn't create a process"));
		if (g_data.phil[i].pid == 0)
			phi_life((void *)i);
	}
	ret = waitpid(-1, &status, 0);
	if (WIFEXITED(status))
		ret = WEXITSTATUS(status);
	else if (ret < 0)
		ret = EXIT_FAILURE;
	return (ret);
}

int	main(int argc, char **argv)
{
	if (init(argc, argv) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	if (create_philo_processes() == EXIT_FAILURE)
		return (EXIT_FAILURE);
	if (create_monitor_threads() == EXIT_FAILURE)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
