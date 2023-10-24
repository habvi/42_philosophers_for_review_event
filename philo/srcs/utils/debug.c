#include <stdio.h>
#include "philo.h"

void	put_args(const t_args *args)
{
	printf("num of philo  : %d\n", args->num_of_philos);
	printf("time to die   : %d\n", args->time_to_die);
	printf("time to eat   : %d\n", args->time_to_eat);
	printf("time to sleep : %d\n", args->time_to_sleep);
	printf("each philo must eat : %d\n", \
							args->num_of_times_each_philo_must_eat);
}
