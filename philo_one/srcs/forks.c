#include "philo_one.h"

/*
** Here I use the following solution for the dining philosopher problem:
** hierarchy of resources -> the resources (forks) are numbered 1 through
** number_of_philosophers. Each unit of work (philosopher) will always pick up
** the lower-numbered fork first, and then the higher-numbered fork,
** from among the two forks they plan to use.
*/

