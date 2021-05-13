#include "philo_two.h"

static int	parse_arguments(int argc, char **argv)
{
	int	i;

	i = 0;
	while (++i < argc)
	{
		if (ft_str_is_numeric(argv[i]) == 0)
			return (EXIT_FAILURE);
	}
	g_data.p = ft_atoi(argv[1]);
	g_data.time_to_die = ft_atoi(argv[2]);
	g_data.time_to_eat = ft_atoi(argv[3]);
	g_data.time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		g_data.must_eat = ft_atoi(argv[5]);
	else
		g_data.must_eat = 0;
	return (EXIT_SUCCESS);
}

static int	validator(int argc, char **argv)
{
	if (argc < 5 || argc > 6)
	{
		printf("Wrong number of arguments: expected 4 or 5\n" \
			   "1.number_of_philosophers 2.time_to_die 3.time_to_eat " \
			   "4.time_to_sleep 5.number_of_times_each_philosopher_must_eat" \
																"(optional)\n");
		return (EXIT_FAILURE);
	}
	if (parse_arguments(argc, argv) == EXIT_FAILURE)
	{
		printf("Only numeric arguments are expected:\n"
			   "1.number_of_philosophers 2.time_to_die 3.time_to_eat "
			   "4.time_to_sleep 5.number_of_times_each_philosopher_must_eat" \
																"(optional)\n");
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

static int	init_phils(void)
{
	int	i;

	g_data.phil = (t_phil *)malloc(sizeof(t_phil) * g_data.p);
	if (g_data.phil == NULL)
		ft_error("Malloc returned error");
	i = -1;
	while (++i < g_data.p)
	{
		g_data.phil[i].last_meal = get_time();
		g_data.phil[i].meals = 0;
	}
	return (EXIT_SUCCESS);
}

static void	init_semaphores(void)
{
	sem_unlink("/semaphore");
	sem_unlink("/semaphore_write");
	g_data.waiter = sem_open("/semaphore", O_CREAT, 0666, g_data.p);
	if (g_data.waiter == SEM_FAILED)
		ft_error("Couldn't open a semaphore");
	g_data.write = sem_open("/semaphore_write", O_CREAT, 0666, 1);
	if (g_data.write == SEM_FAILED)
		ft_error("Couldn't open a semaphore");
}

int	init(int argc, char **argv)
{
	if (validator(argc, argv) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	if (init_phils() == EXIT_FAILURE)
		return (EXIT_FAILURE);
	init_semaphores();
	g_data.start_time = get_time();
	return (EXIT_SUCCESS);
}
