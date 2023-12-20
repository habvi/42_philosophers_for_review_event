# philosophers
"Dining Philosophers Problem"  
Philosophers with threads and mutexes.

### Usage
```
./philo [num_of_philos] [time_to_die] [time_to_eat] [time_to_sleep] [num_of_times_each_philo_must_eat(option)]
```

```shell
$ cd philo/
$ make

# even num_of_philos
$ ./philo 4 410 200 200

# odd num_of_philos
$ ./philo 5 800 200 200
$ ./philo 5 800 200 200 10
```

<br>

External functions
- printf
- malloc, free
- write, memset
- usleep, gettimeofday
- pthread_create, pthread_join
- pthread_mutex_init, pthread_mutex_destroy, pthread_mutex_lock, pthread_mutex_unlock
