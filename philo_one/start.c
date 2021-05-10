#include "philo_one.h"

static int parse_arguments(int argc, char **argv)
{
	int i;

	i = 0;
	while (++i < argc)
	{
		if (ft_str_is_numeric(argv[i]) == 0)
			return (EXIT_FAILURE);
	}
	g_data.p = ft_atoi(argv[1]);
	g_data.time_die = ft_atoi(argv[2]);
	g_data.time_eat = ft_atoi(argv[3]);
	g_data.time_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		g_data.must_eat = ft_atoi(argv[5]);
	return (EXIT_SUCCESS);
}

int	validator(int argc, char **argv)
{
	if (argc < 5 || argc > 6)
	{
		printf("Wrong number of arguments: expected 4 or 5\n"
			   "1.number_of_philosophers 2.time_to_die 3.time_to_eat "
			   "4.time_to_sleep 5.[number_of_times_each_philosopher_must_eat]\n");
		return (EXIT_FAILURE);
	}
	if (parse_arguments(argc, argv) == EXIT_FAILURE)
	{
		printf("Only numeric arguments are expected:\n"
			   "1.number_of_philosophers 2.time_to_die 3.time_to_eat "
			   "4.time_to_sleep 5.[number_of_times_each_philosopher_must_eat]\n");
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

int init_phils(void)
{
	int		i;
	ms_type	time;

	g_data.phil = (t_phil *)malloc(sizeof(t_phil) * g_data.p);
	if (g_data.phil == NULL)
		ft_error("Malloc returned error");
	time = get_time();
	i = -1;
	while (++i < g_data.p)
	{
		g_data.phil[i].last_meal = time;
		pthread_mutex_init(&g_data.phil[i].fork, NULL);
	}
	return (EXIT_SUCCESS);
}

int	init_forks(void)
{
	int i;

	g_data.forks = (int *)malloc(sizeof(int) * g_data.p);
	if (g_data.forks == NULL)
		return (EXIT_FAILURE);
	i = -1;
	while (++i < g_data.p)
		g_data.forks[i] = 1;
	return (EXIT_SUCCESS);
}

int init(int argc, char **argv)
{
	if (validator(argc, argv) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	if (init_phils() == EXIT_FAILURE)
		return (EXIT_FAILURE);
	 if (init_forks() == EXIT_FAILURE)
	 	return (EXIT_FAILURE);
	pthread_mutex_init(&g_data.write, NULL);
	pthread_mutex_init(&g_data.lock, NULL);
	g_data.start_time = get_time();
	return (EXIT_SUCCESS);
}