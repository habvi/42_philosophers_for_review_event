#include "philo.h"

// static void	interval(const int id)
// {
// 	if (id % 2)
// 		usleep(50);
// }

static int64_t	put_log_fork(t_philo *philo)
{
	return (put_log_flow(philo, get_elapsed_time, MSG_FORK));
}

void	take_fork(pthread_mutex_t *fork, t_philo *philo)
{
	pthread_mutex_lock(fork);
	philo_action(philo, put_log_fork);
}

void	take_two_forks(t_philo *philo)
{
	take_fork(philo->left_fork, philo);
	take_fork(philo->right_fork, philo);
}

void	put_fork(pthread_mutex_t *fork)
{
	pthread_mutex_unlock(fork);
}

void	put_two_forks(t_philo *philo)
{
	put_fork(philo->right_fork);
	put_fork(philo->left_fork);
}
