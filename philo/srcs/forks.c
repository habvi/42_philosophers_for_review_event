#include "philo.h"

// static void	interval(const int id)
// {
// 	if (id % 2)
// 		usleep(50);
// }

static t_result	take_fork(pthread_mutex_t *fork)
{
	if (pthread_mutex_lock(fork) != MUTEX_SUCCESS)
		return (FAILURE);
	return (SUCCESS);
}

static t_result	put_fork(pthread_mutex_t *fork)
{
	if (pthread_mutex_unlock(fork) != MUTEX_SUCCESS)
		return (FAILURE);
	return (SUCCESS);
}

t_result	put_two_forks(const t_philo *philo)
{
	if (put_fork(philo->right_fork) == FAILURE)
		return (FAILURE);
	if (put_fork(philo->left_fork) == FAILURE)
		return (FAILURE);
	return (SUCCESS);
}

t_result	take_two_forks(const t_philo *philo)
{
	// interval(philo->id);
	if (take_fork(philo->left_fork) == FAILURE)
		return (FAILURE);
	if (is_any_philo_died(philo))
	{
		if (put_fork(philo->left_fork) == FAILURE)
			return (FAILURE);
		return (BREAK);
	}
	put_log(philo, MSG_FORK);
	if (take_fork(philo->right_fork) == FAILURE)
		return (FAILURE);
	if (is_any_philo_died(philo))
	{
		if (put_two_forks(philo) == FAILURE)
			return (FAILURE);
		return (BREAK);
	}
	put_log(philo, MSG_FORK);
	return (SUCCESS);
}
