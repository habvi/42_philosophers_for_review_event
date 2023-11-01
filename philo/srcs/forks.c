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
	// interval(philo->id);
	take_fork(philo->left_fork);
	if (is_any_philo_died(philo))
	{
		put_fork(philo->left_fork);
		return (BREAK);
	}
	put_log(philo, MSG_FORK);
	take_fork(philo->right_fork);
	if (is_any_philo_died(philo))
	{
		put_two_forks(philo);
		return (BREAK);
	}
	put_log(philo, MSG_FORK);
	return (SUCCESS);
}
