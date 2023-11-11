#include <stdio.h> // printf
#include "philo.h"

void	put_log(const int64_t elapsed_time, \
									const unsigned int id, const char *message)
{
	printf(SPEC_i64" %d %s\n", elapsed_time, id, message);
}

int64_t	put_log_flow(t_philo *philo, int64_t (*get_time)(), const char *message)
{
	const int64_t	elapsed_time = get_time(philo);

	if (is_simulation_over(philo))
		return (SUCCESS);
	put_log(elapsed_time, philo->id, message);
	return (SUCCESS);
}

t_result	fatal_error(void)
{
	printf("%s\n", ERR_FATAL);
	return (FAILURE);
}
