#include <stdio.h> // printf
#include "philo.h"
#include "utils.h"

void	put_log(const int64_t elapsed_time, \
									const unsigned int id, const char *message)
{
	printf(SPEC_I64" %d %s\n", elapsed_time, id, message);
}

int64_t	put_log_flow(t_philo *philo, void (*set_time)(), const char *message)
{
	const int64_t	current_time = get_current_time_msec();
	const int64_t	elapsed_time = current_time - philo->args->start_time;

	if (is_simulation_over(philo))
		return (FAILURE);
	if (is_starved(philo, current_time))
	{
		// philo->args->is_any_philo_died = true;
		return (FAILURE);
	}
	if (set_time != NULL)
		set_time(philo, current_time);
	put_log(elapsed_time, philo->id, message);
	return (SUCCESS);
}

t_result	fatal_error(void)
{
	printf("%s\n", ERR_FATAL);
	return (FAILURE);
}
