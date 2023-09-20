#include <stdio.h>
#include "philo.h"

void	put_args(t_args *args)
{
	printf("num of philo  : %d\n", args->number_of_philosophers);
	printf("time to die   : %d\n", args->time_to_die);
	printf("time to eat   : %d\n", args->time_to_eat);
	printf("time to sleep : %d\n", args->time_to_sleep);
	printf("each philo must eat : %d\n", args->number_of_times_each_philosopher_must_eat);
}
