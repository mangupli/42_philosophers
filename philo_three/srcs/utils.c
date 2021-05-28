#include "philo_three.h"

int	ft_error(char *str)
{
	printf("%s\n", str);
	return (EXIT_FAILURE);
}

time_t	get_time(void)
{
	struct timeval	time;
	time_t			ms;

	if (gettimeofday(&time, NULL) == -1)
		return (EXIT_FAILURE);
	ms = (time.tv_sec * 1000) + (time.tv_usec / 1000);
	return (ms);
}

int	ft_usleep(time_t time_to_sleep)
{
	time_t	now;
	time_t	end;

	end = get_time() + time_to_sleep;
	now = get_time();
	while (now < end)
	{
		usleep(STEP_TIME);
		now = get_time();
	}
	return (EXIT_SUCCESS);
}

int	ft_exit(int exit_code)
{
	sem_unlink("sem_forks");
	sem_unlink("sem_write");
	exit(exit_code);
	return (exit_code);
}

void	*display_message(long ms, int no, int act)
{
	long	time;
	int		i;

	time = ms - g_data.start_time;
	printf("%ld  ", time);
	if (act == FINISH)
	{
		printf("my philosophers are full\n");
		return (NULL);
	}
	i = -1;
	while (++i < no)
		printf("			");
	no += 1;
	if (act == TAKE_FORK)
		printf("%d has taken a fork\n", no);
	else if (act == EAT)
		printf("%d is eating\n", no);
	else if (act == SLEEP)
		printf("%d is sleeping\n", no);
	else if (act == THINK)
		printf("%d is thinking\n", no);
	else if (act == DIE)
		printf("%d died\n", no);
	return (NULL);
}
