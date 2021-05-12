#include "philo_two.h"

int	ft_error(char *str)
{
	printf("%s\n", str);
	exit(EXIT_FAILURE);
	return (EXIT_FAILURE);
}

t_ms	get_time(void)
{
	struct timeval	time;
	t_ms			ms;

	if (gettimeofday(&time, NULL) == -1)
		return (EXIT_FAILURE);
	ms = (time.tv_sec * 1000) + (time.tv_usec / 1000);
	return (ms);
}
