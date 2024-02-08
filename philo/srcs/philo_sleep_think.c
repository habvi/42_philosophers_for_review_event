#include "philo.h"
#include "utils.h"

static int64_t	put_log_sleeping(t_philo *philo)
{
	return (put_log_flow(philo, NULL, MSG_SLEEP));
}

void	sleeping(t_philo *philo)
{
	const int64_t	time_to_sleep = philo->rule.time_to_sleep;
	pthread_mutex_t	*shared;

	if (is_simulation_over_atomic(philo))
		return ;
	shared = &philo->shared->shared;
	if (call_atomic(shared, put_log_sleeping, philo) == FAILURE)
		return ;
	usleep_gradual(time_to_sleep, philo);
}

static int64_t	put_log_thinking(t_philo *philo)
{
	return (put_log_flow(philo, NULL, MSG_THINK));
}

void	thinking(t_philo *philo)
{
	pthread_mutex_t	*shared;

	if (is_simulation_over_atomic(philo))
		return ;
	shared = &philo->shared->shared;
	call_atomic(shared, put_log_thinking, philo);
}
