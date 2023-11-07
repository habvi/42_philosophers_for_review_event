#include "philo.h"

// static void	interval(const int id)
// {
// 	if (id % 2)
// 		usleep(50);
// }

static void	take_fork(pthread_mutex_t *fork)
{
	pthread_mutex_lock(fork);
}

static void	put_fork(pthread_mutex_t *fork)
{
	pthread_mutex_unlock(fork);
}

void	put_two_forks(const t_philo *philo)
{
	put_fork(philo->right_fork);
	put_fork(philo->left_fork);
}

t_result	take_two_forks(const t_philo *philo)
{
	pthread_mutex_t	*shared;

	// interval(philo->id);
	shared = &philo->args->shared;
	take_fork(philo->left_fork);
	pthread_mutex_lock(shared);
	if (is_any_philo_died(philo))
	{
		put_fork(philo->left_fork);
		pthread_mutex_unlock(shared);
		return (BREAK);
	}
	put_log(philo, MSG_FORK, get_elapsed_time);
	pthread_mutex_unlock(shared);

	take_fork(philo->right_fork);
	pthread_mutex_lock(shared);
	if (is_any_philo_died(philo))
	{
		put_two_forks(philo);
		pthread_mutex_unlock(shared);
		return (BREAK);
	}
	put_log(philo, MSG_FORK, get_elapsed_time);
	pthread_mutex_unlock(shared);
	return (SUCCESS);
}
