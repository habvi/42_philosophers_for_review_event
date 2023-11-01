#include <stdio.h> // printf
#include "philo.h"

void	put_log(const t_philo *philo, const char *message)
{
	pthread_mutex_t	*for_log;
	int64_t			elapsed_time;

	for_log = &philo->args->for_log;
	pthread_mutex_lock(for_log);
	elapsed_time = get_elapsed_time(philo);
	printf("%ld %d %s\n", elapsed_time, philo->id, message);
	pthread_mutex_unlock(for_log);
}

t_result	fatal_error(void)
{
	printf("%s\n", ERR_FATAL);
	return (FAILURE);
}
