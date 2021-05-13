#ifndef PHILO_THREE_H
# define PHILO_THREE_H

# include <semaphore.h> // semaphore functions
# include <pthread.h> // pthreads functions
# include <stdio.h> // printf
# include <string.h> // memset
# include <signal.h> // kill
# include <stdlib.h> // malloc, free, exit
# include <unistd.h> // write, usleep, fork
# include <sys/time.h> // gettimeofday
# include <sys/wait.h> // waitpid

# define TAKE_FORK 0
# define EAT 1
# define SLEEP 2
# define THINK 3
# define DIE 4
# define FINISH 5

typedef unsigned long long	t_ms;

typedef struct s_phil
{
	t_ms				last_meal;
	pid_t				pid;
	int					meals;
}						t_phil;

/*
 * p -> number of philosophers
 */

typedef struct s_data
{
	int					p;
	t_ms				start_time;
	int					time_to_eat;
	int					time_to_sleep;
	int					time_to_die;
	int					must_eat;
	t_phil				*phil;
	sem_t				*write;
	sem_t				*waiter;
	pthread_t			death;
	pthread_t			meal;
}						t_data;

t_data						g_data;

int		init(int argc, char **argv);
int		ft_atoi(const char *str);
int		ft_str_is_numeric(char *str);
int		ft_error(char *str);
t_ms	get_time(void);
int		ft_strlen(char *str);
int		display_message(t_ms ms, int no, int act);
void	get_forks(long num);
void	put_down_forks(long num);
void	*finish_meal(void *a);
void	*check_death(void *a);

#endif