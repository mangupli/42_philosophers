#ifndef PHILO_ONE_H
# define PHILO_ONE_H

# include <pthread.h> //pthread functions
# include <stdio.h> // printf
# include <string.h> // memset
# include <stdlib.h> // malloc, free,
# include <unistd.h> // write, usleep
# include <sys/time.h> // gettimeofday

# define TAKE_FORK 0
# define EAT 1
# define SLEEP 2
# define THINK 3
# define DIE 4
# define FINISH 5
# define STEP_TIME 60

typedef struct s_phil
{
	long				last_meal;
	pthread_t			thread;
	pthread_mutex_t		fork;
	int					meals;
	int 				id;
}						t_phil;

/*
 * p -> number of philosophers
 */

typedef struct s_data
{
	int					p;
	long				start_time;
	int					time_to_eat;
	int					time_to_sleep;
	int					time_to_die;
	int					must_eat;
	pthread_mutex_t		write;
	pthread_mutex_t		exit;
	t_phil				*phil;
	pthread_t			death;
	pthread_t			meal;
}						t_data;

t_data						g_data;

int		init(int argc, char **argv);
int		ft_atoi(const char *str);
int		ft_str_is_numeric(char *str);
int		ft_error(char *str);
time_t	get_time(void);
int		ft_strlen(char *str);
int		display_message(long ms, int no, int act);
void	get_forks(long num);
void	put_down_forks(long num);
void	*finish_meal(void *a);
void	*check_death(void *a);
int		ft_usleep(time_t time_to_sleep);
time_t	get_print_time(time_t time_now);

#endif