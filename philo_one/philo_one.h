#ifndef PHILO_ONE_H
# define PHILO_ONE_H

#include <pthread.h> //pthread functions
#include <stdio.h> // printf
#include <string.h> // memset
#include <stdlib.h> // malloc, free,
#include <unistd.h> // write, usleep
#include <sys/time.h> // gettimeofday

typedef unsigned long long ms_type;

/*
 * t -> thread structure
 */

typedef struct s_phil
{
	ms_type				last_meal;
	pthread_t			t;
	pthread_mutex_t		fork;
}						t_phil;

/*
 * p -> number of philosophers
 */

typedef struct s_data
{
	int 				p;
	ms_type				start_time;
	int					time_eat;
	int					time_sleep;
	int					time_die;
	int					must_eat;
	pthread_mutex_t		write;
	pthread_mutex_t		lock;
	t_phil				*phil;
	int					*forks;
	pthread_t			death;
}						t_data;

t_data g_data;

#define TAKE_FORK 0
#define EAT 1
#define SLEEP 2
#define THINK 3
#define DIE 4

#define UP 0
#define DOWN 1

int		init(int argc, char **argv);
int		ft_atoi(const char *str);
int		ft_str_is_numeric(char *str);
int		validator(int argc, char **argv);
void	ft_error(char *str);
ms_type	get_time(void);


void print_msg(ms_type time, int no, char *str); //test

#endif