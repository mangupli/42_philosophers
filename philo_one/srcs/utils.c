#include "philo_one.h"

int	ft_error(char *str)
{
	printf("%s\n", str);
	return (EXIT_FAILURE);
}

long	get_time(void)
{
	struct timeval	time;
	long			ms;

	if (gettimeofday(&time, NULL) == -1)
		return (EXIT_FAILURE);
	ms = (time.tv_sec * 1000) + (time.tv_usec / 1000);
	return (ms);
}