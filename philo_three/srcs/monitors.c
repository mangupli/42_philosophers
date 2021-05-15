#include "philo_three.h"

void	*check_death(void *a)
{
	t_ms	time;
	long	num;

	num = (long)a;
	while (1)
	{
		time = get_time();
		if (g_data.phil[num].last_meal + g_data.time_to_die < time)
		{
			sem_wait(g_data.exit);
			display_message(time, i + 1, DIE);
			exit(EXIT_FAILURE);
		}	
	}
	return (NULL);
}

void	*finish_meal(void *a)
{
	int	i;
	long num;

	num = (long)a;
	while (1)
	{
		if (g_data.phil[num].meals >= g_data.must_eat)
		{
			sem_wait(g_data.exit);
			display_message(get_time(), 0, FINISH);
			exit(EXIT_SUCCESS);
		}
	}
	return (NULL);
}
