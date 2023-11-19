#include <unistd.h> // usleep
#include "philo.h"
#include "utils.h"

static int64_t	put_philo_died(t_philo *philo)
{
	if (philo->is_self_dead)
		put_log(philo, MSG_DIED);
	return (SUCCESS);
}

// monitoring for death periodically with interval.
void	*monitor_cycle(void *thread_args)
{
	t_philo			*philo;
	bool			is_thread_error;
	pthread_mutex_t	*shared;

	philo = (t_philo *)thread_args;
	is_thread_error = wait_start(philo);
	if (is_thread_error)
		return (NULL);
	while (!is_simulation_over_atomic(philo))
		usleep(MONITOR_DURATION);
	shared = &philo->shared->shared;
	call_atomic(shared, put_philo_died, philo);
	return (NULL);
}
