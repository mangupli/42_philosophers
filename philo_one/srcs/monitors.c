#include "philo_one.h"

void	*check_death(void *a)
{
	t_ms	time;
	int		i;

	(void)a;
	while (1)
	{
		i = -1;
		while (++i < (g_data.p - 1))
		{
			time = get_time();
			if (g_data.phil[i].last_meal + g_data.time_to_die < time)
			{
				display_message(time, i + 1, DIE);
				exit(EXIT_FAILURE);
			}
		}
	}
	return (NULL);
}

void	*finish_meal(void *a)
{
	int	i;

	(void)a;
	while (1)
	{
		i = -1;
		while (++i < (g_data.p - 1))
		{
			if (g_data.phil[i].meals < g_data.must_eat)
				break ;
			else if (i + 1 == (g_data.p - 1))
			{
				display_message(get_time(), 0, FINISH);
				exit(EXIT_SUCCESS);
			}
		}
	}
	return (NULL);
}
