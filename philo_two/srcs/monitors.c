#include "philo_two.h"

static void ft_exit(int exit_code)
{
	exit(exit_code);
}

void	*check_death(void *a)
{
	t_ms	time;
	int		i;

	(void)a;
	while (1)
	{
		i = -1;
		while (++i < g_data.p)
		{
			time = get_time();
			if (g_data.phil[i].last_meal + g_data.time_to_die < time)
			{
				display_message(time, i + 1, DIE);
				ft_exit(EXIT_FAILURE);
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
		while (++i < g_data.p)
		{
			if (g_data.phil[i].meals < g_data.must_eat)
				break ;
			else if (i + 1 == g_data.p)
			{
				display_message(get_time(), 0, FINISH);
				ft_exit(EXIT_SUCCESS);
			}
		}
	}
	return (NULL);
}
