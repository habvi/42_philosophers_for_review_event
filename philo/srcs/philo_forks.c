#include "philo.h"
#include "utils.h"

static int64_t	put_log_fork(t_philo *philo)
{
	return (put_log_flow(philo, NULL, MSG_FORK));
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
