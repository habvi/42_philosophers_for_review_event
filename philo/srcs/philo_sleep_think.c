#include "philo.h"
#include "utils.h"

// The required philo->current_time within put_log() is
// set inside is_simulation_over(), thus preserving the order.
static t_result	put_log_sleeping(t_philo *philo)
{
	if (is_simulation_over(philo))
		return (FAILURE);
	put_log(philo, MSG_SLEEP);
	return (SUCCESS);
}

void	sleeping(t_philo *philo)
{
	const int64_t	time_to_sleep = philo->rule.time_to_sleep;
	pthread_mutex_t	*shared;
	t_result		result;

	shared = &philo->shared->shared;
	pthread_mutex_lock(shared);
	result = put_log_sleeping(philo);
	pthread_mutex_unlock(shared);
	if (result == FAILURE)
		return ;
	usleep_gradual(time_to_sleep, philo);
}

// The required philo->current_time within put_log() is
// set inside is_simulation_over(), thus preserving the order.
static int64_t	put_log_thinking(t_philo *philo)
{
	if (is_simulation_over(philo))
		return (FAILURE);
	put_log(philo, MSG_THINK);
	return (SUCCESS);
}

void	thinking(t_philo *philo)
{
	pthread_mutex_t	*shared;

	shared = &philo->shared->shared;
	call_atomic(shared, put_log_thinking, philo);
}
