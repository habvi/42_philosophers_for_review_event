#include "philo.h"

// The required philo->current_time within put_log() is
// set inside is_simulation_over(), thus preserving the order.
static void	put_log_fork(t_philo *philo)
{
	if (is_simulation_over(philo))
		return ;
	put_log(philo, MSG_FORK);
}

void	take_fork(pthread_mutex_t *fork, t_philo *philo)
{
	pthread_mutex_t	*shared;

	pthread_mutex_lock(fork);
	shared = &philo->shared->shared;
	pthread_mutex_lock(shared);
	put_log_fork(philo);
	pthread_mutex_unlock(shared);
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
