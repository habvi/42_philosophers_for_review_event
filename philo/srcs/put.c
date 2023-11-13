#include <stdio.h> // printf
#include "philo.h"

// call in lock
void	put_log(const t_philo *philo, const char *message)
{
	const int64_t	elapsed_time = \
								philo->current_time - philo->args->start_time;

	printf(SPEC_I64" %d %s\n", elapsed_time, philo->id, message);
}

// call in lock
// set philo->current_time in is_simulation_over()
// set_time() is only used eating
int64_t	put_log_flow(t_philo *philo, void (*set_time)(), const char *message)
{

	if (is_simulation_over(philo))
		return (FAILURE);
	if (set_time != NULL)
		set_time(philo, philo->current_time);
	put_log(philo, message);
	return (SUCCESS);
}

t_result	fatal_error(void)
{
	printf("%s\n", ERR_FATAL);
	return (FAILURE);
}
