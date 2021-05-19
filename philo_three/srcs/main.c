#include "philo_three.h"

static int	create_philo_processes(void)
{
	int	i;

	i = -1;
	while (++i < g_data.p)
	{
		g_data.phil[i].pid = fork();
		if (g_data.phil[i].pid < 0)
			return (EXIT_FAILURE);
		if (g_data.phil[i].pid == 0)
			phi_life(i);
	}
	return (EXIT_SUCCESS);
}

static void	*check_death(void *a)
{
	time_t	time;
	long int num;

	num = (long int)a;
	while (1)
	{
		time = get_time();
		sem_wait(g_data.write);
		if (g_data.phil[num].last_meal + g_data.time_to_die < time)
		{
			display_message(time, num, DIE);
			ft_exit(EXIT_FAILURE);
			return (NULL);
		}
		sem_post(g_data.write);
	}
}

int	create_monitor_thread(long int num)
{
	if (pthread_create(&g_data.phil[num].death, NULL, check_death, (void *)num) == -1)
		return (ft_error("Can'thread create a thread"));
	if (pthread_detach(g_data.phil[num].death) == -1)
		return (ft_error("Can'thread join a thread"));
	return (EXIT_SUCCESS);
}

int	main(int argc, char **argv)
{
	pid_t	pid;
	int		i;

	if (init(argc, argv) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	if (g_data.must_eat != 0)
	{
		if (create_philo_processes() == EXIT_FAILURE)
			return (ft_exit(EXIT_FAILURE));
	}
	if (g_data.must_eat == -1)
	{
		pid = waitpid(-1, NULL, 0);
		i = -1;
		while (++i < g_data.p)
		{
			if (g_data.phil[i].pid != pid)
				kill(g_data.phil[i].pid, SIGKILL);
		}
	}
	else
	{
		i = -1;
		while (++i < g_data.p)
		{
			waitpid(g_data.phil[i].pid, NULL, 0);
		}
		display_message(get_time(), 0, FINISH);
	}
	return (ft_exit(EXIT_SUCCESS));
}
