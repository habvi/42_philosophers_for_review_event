#include <stdio.h>
#include "philo.h"
#include "utils.h"

void	put_args(const t_args *args)
{
	printf("num of philo  : %d\n", args->num_of_philos);
	printf("time to die   : %ld\n", args->time_to_die);
	printf("time to eat   : %ld\n", args->time_to_eat);
	printf("time to sleep : %ld\n", args->time_to_sleep);
	printf("each philo must eat : %d\n", args->num_of_each_philo_must_eat);
}

static int64_t	put_sub(const char *message)
{
	printf("%s\n", message);
	return (SUCCESS);
}

void	put(const t_philo *philo, char *message)
{
	pthread_mutex_t	*shared;

	shared = &philo->args->shared;
	call_atomic(shared, put_sub, message);
}
