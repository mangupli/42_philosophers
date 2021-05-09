#include <pthread.h> //pthread functions
#include <stdio.h> // printf
#include <string.h> // memset
#include <stdlib.h> // malloc, free,
#include <unistd.h> // write, usleep
#include <sys/time.h> // gettimeofday

typedef unsigned long long ms_t;

#define TAKE_FORK 0
#define EAT 1
#define SLEEP 2
#define THINK 3
#define DIE 4

int	ft_atoi(const char *str)
{
	int	minus;
	int	i;
	int	result;

	i = 0;
	minus = 1;
	result = 0;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			minus = -1;
		i++;
	}
	while (str[i] <= 57 && str[i] >= 48)
	{
		result = result * 10 + (str[i] - 48);
		i++;
	}
	return (minus * result);
}

int display_message(ms_t ms, int no, int act)
{
	if (act == TAKE_FORK)
		printf("%llu %d %s\n", ms, no, "has taken a fork");
	if (act == EAT)
		printf("%llu %d %s\n", ms, no, "is eating");
	if (act == SLEEP)
		printf("%llu %d %s\n", ms, no, "is sleeping");
	if (act == THINK)
		printf("%llu %d %s\n", ms, no, "is thinking");
	if (act == DIE)
		printf("%llu %d %s\n", ms, no, "died");
	return (EXIT_SUCCESS);
}

ms_t get_time()
{
	struct timeval  time;
	ms_t ms;

	if (gettimeofday(&time, NULL) == -1)
		return (EXIT_FAILURE);
	ms = (time.tv_sec * 1000) + (time.tv_usec / 1000);
	return (ms);
}


int main(int argc, char **argv)
{
	if (argc < 5 || argc > 6)
		printf("Wrong number of arguments: expected 4 or 5\n"
		 "1.number_of_philosophers 2.time_to_die 3.time_to_eat "
			   "4.time_to_sleep 5.[number_of_times_each_philosopher_must_eat]\n");
	else
	{
		display_message(get_time(), ft_atoi(argv[1]), ft_atoi(argv[2]));
	}
	return (EXIT_SUCCESS);
}