# 42_philosophers
Dining philosophers problem resolved differently using mutexes and semaphores, threads and processes. Educational project to figure out the differences between those entities.

## philo_one

- one thread per philosopher
- one mutex per fork
- output is protected against multiple access by another mutex

## philo_two

- one thread per philosopher
- one semaphore to represent the number of forks
- output is protected against multiple access by another semaphore

## philo_one

- one process per philosopher
- one semaphore to represent the number of forks
- output is protected against multiple access by another semaphore

### how to start

In each directory there is a Makefile that creates executable. 
Exectuable with right number of arguments start a simulation where philosphers eat, sleep and think.

### arguments

1.number_of_philosophers: is the number of philosophers and also the number of forks

2.time_to_die: is in milliseconds, if a philosopher doesn’t start eating ’time_to_die’ milliseconds after starting his last meal or the beginning of the simulation, it dies

3.time_to_eat: is in milliseconds and is the time it takes for a philosopher to eat. During that time he will need to keep the two forks.

4.time_to_sleep: is in milliseconds and is the time the philosopher will spend sleeping.

5.number_of_times_each_philosopher_must_eat: argument is optional, if all philosophers eat at least ’number_of_times_each_philosopher_must_eat’ the simulation will stop. If not specified, the simulation will stop only at the death of a philosopher.

