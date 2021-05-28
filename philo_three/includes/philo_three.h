#ifndef PHILO_THREE_H
# define PHILO_THREE_H

# include <pthread.h> //pthread functions
# include <semaphore.h> // semaphores
# include <stdio.h> // printf
# include <string.h> // memset
# include <stdlib.h> // malloc, free,
# include <unistd.h> // write, usleep
# include <sys/time.h> // gettimeofday
# include <signal.h> // kill

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
	pthread_t			death;
	pid_t				pid;
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
	sem_t				*write;
	sem_t				*forks;
	t_phil				*phil;
	int					count_full;
}						t_data;

t_data						g_data;

int		init(int argc, char **argv);
int		ft_atoi(const char *str);
int		ft_str_is_numeric(char *str);
int		ft_error(char *str);
time_t	get_time(void);
int		ft_strlen(char *str);
void	*display_message(long ms, int no, int act);
int		ft_usleep(time_t time_to_sleep);
int		ft_exit(int exit_code);
int		phi_life(int num);
int		create_monitor_thread(long int num);

#endif