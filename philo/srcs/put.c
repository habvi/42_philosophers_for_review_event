#include <stdio.h> // printf
#include "philo.h"

void	put_log(t_philo *philo, const char *message, \
											int64_t (*get_time)(t_philo *philo))
{
	int64_t	elapsed_time;

	elapsed_time = get_time(philo);
	printf("%ld %d %s\n", elapsed_time, philo->id, message);
}

t_result	fatal_error(void)
{
	printf("%s\n", ERR_FATAL);
	return (FAILURE);
}
