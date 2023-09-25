#include <stdio.h>
#include <stdlib.h> // exit
#include <sys/time.h>
#include "philo.h"
#include "utils.h"

void	put_args(const t_args *args)
{
	printf("num of philo  : %d\n", args->number_of_philosophers);
	printf("time to die   : %d\n", args->time_to_die);
	printf("time to eat   : %d\n", args->time_to_eat);
	printf("time to sleep : %d\n", args->time_to_sleep);
	printf("each philo must eat : %d\n", args->number_of_times_each_philosopher_must_eat);
}

void    put_current_time(void) {
	struct timeval  current_time;
	long			sec;
	long			micro_sec;
	long			milli_sec;

	if (gettimeofday(&current_time, NULL) == TIME_ERROR)
	{
		perror("gettimeofday");
		exit(EXIT_FAILURE); // todo: erase
	}
	sec = current_time.tv_sec;
	micro_sec = current_time.tv_usec;
	milli_sec = sec * 1000L + micro_sec / 1000L;
	printf("%ld ", milli_sec);
}
