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

