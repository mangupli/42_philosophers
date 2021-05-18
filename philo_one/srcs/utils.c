#include "philo_one.h"

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

time_t	get_print_time(time_t time_now)
{
	return (time_now - g_data.start_time);
}

int ft_usleep(time_t time_to_sleep)
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
