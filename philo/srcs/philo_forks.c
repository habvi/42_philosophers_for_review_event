#include "philo.h"
#include "utils.h"

// The required philo->current_time within put_log() is
// set inside is_simulation_over(), thus preserving the order.
static int64_t	put_log_fork(t_philo *philo)
{
	if (is_simulation_over(philo))
		return (FAILURE);
	put_log(philo, MSG_FORK);
	return (SUCCESS);
}

void	take_fork(pthread_mutex_t *fork, t_philo *philo)
{
	pthread_mutex_t	*shared;

	pthread_mutex_lock(fork);
	if (is_simulation_over_atomic(philo))
		return ;
	shared = &philo->shared->shared;
	call_atomic(shared, put_log_fork, philo);
}

void	take_two_forks(t_philo *philo)
{
	take_fork(philo->fork1, philo);
	take_fork(philo->fork2, philo);
}

void	put_fork(pthread_mutex_t *fork)
{
	pthread_mutex_unlock(fork);
}

void	put_two_forks(t_philo *philo)
{
	put_fork(philo->fork1);
	put_fork(philo->fork2);
}
