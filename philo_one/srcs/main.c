#include "philo_one.h"

static void	*phi_life(void *a)
{
	long	num;
	int 	meals;

	meals = 0;
	num = (long)a;
	if ((num + 1) % 2 == 0)
		ft_usleep(g_data.time_to_eat);
	while (1)
	{
		get_forks_and_eat(num);
		meals++;
		if (g_data.must_eat >= 0 && meals >= g_data.must_eat)
			g_data.phil[num].full = 1;
		put_down_forks(num);
		pthread_mutex_lock(&g_data.write);
		display_message(get_time(), num, SLEEP);
		pthread_mutex_unlock(&g_data.write);
		ft_usleep(g_data.time_to_sleep);
		pthread_mutex_lock(&g_data.write);
		display_message(get_time(), num, THINK);
		pthread_mutex_unlock(&g_data.write);
	}
	return (NULL);
}

static int	create_philo_threads(void)
{
	long		i;

	i = -1;
	while (++i < g_data.p)
	{
		if (pthread_create(&g_data.phil[i].thread, NULL, phi_life, \
															(void *) i) == -1)
			return (ft_error("Can'thread create a thread"));
		if (pthread_detach(g_data.phil[i].thread))
			return (ft_error("Can'thread detach a thread"));
		//ft_usleep(10); // TODO: do I need it?
	}
	return (EXIT_SUCCESS);
}

void	*check_death(void *a)
{

	while (1)
		;
	return (NULL);
}


static int create_monitor_thread(void)
{
	void *result;

	if (pthread_create(&g_data.death, NULL, check_death, NULL) == -1)
		return(ft_error("Can'thread create a thread"));
	if (pthread_join(g_data.death, &result) == -1)
		return (ft_error("Can'thread join a thread"));
	return (EXIT_SUCCESS);
}

int	main(int argc, char **argv)
{
	if (init(argc, argv) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	if (create_philo_threads() == EXIT_FAILURE)
		return (EXIT_FAILURE);

	if (create_monitor_thread() == EXIT_FAILURE)
		return (EXIT_FAILURE);


	//free smth and destroy mutexes

	return (EXIT_SUCCESS);

}