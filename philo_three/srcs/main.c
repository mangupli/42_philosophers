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
	time_t		time;
	long int	num;

	num = (long int)a;
	while (1)
	{
		time = get_time();
		if (g_data.phil[num].last_meal + g_data.time_to_die < time)
			exit(EXIT_FAILURE);
	}
}

int	create_monitor_thread(long int num)
{
	if (pthread_create(&g_data.phil[num].death, NULL, check_death, \
					(void *)num) == -1)
		return (ft_error("Can'thread create a thread"));
	if (pthread_detach(g_data.phil[num].death) == -1)
		return (ft_error("Can'thread join a thread"));
	return (EXIT_SUCCESS);
}

void	parent_waiting(void)
{
	int		i;
	int		status;
	pid_t	pid;

	pid = waitpid(-1, &status, 0);
	if (WEXITSTATUS(status) == EXIT_FAILURE)
	{
		i = -1;
		while (++i < g_data.p)
		{
			if (pid == g_data.phil[i].pid)
				display_message(get_time(), i, DIE);
			kill(g_data.phil[i].pid, SIGKILL);
		}
	}
	if (WEXITSTATUS(status) == EXIT_SUCCESS)
	{
		g_data.count_full++;
		if (g_data.count_full < g_data.p)
			parent_waiting();
		else
		{
			display_message(get_time(), 0, FINISH);
			return ;
		}
	}
}

int	main(int argc, char **argv)
{
	if (init(argc, argv) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	if (g_data.must_eat != 0)
	{
		if (create_philo_processes() == EXIT_FAILURE)
			return (ft_exit(EXIT_FAILURE));
		parent_waiting();
	}
	return (ft_exit(EXIT_SUCCESS));
}
