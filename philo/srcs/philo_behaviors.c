#include <unistd.h> // usleep
#include "philo.h"
#include "utils.h"

// static void	interval(const int id)
// {
// 	if (id % 2)
// 		usleep(50);
// }

t_result	take_two_forks(const t_philo *philo)
{
	// interval(philo->id);
	if (pthread_mutex_lock(philo->left_fork) != MUTEX_SUCCESS)
		return (FAILURE);
	if (is_any_philo_died(philo))
	{
		if (pthread_mutex_unlock(philo->left_fork) != MUTEX_SUCCESS)
			return (FAILURE);
		return (BREAK);
	}
	put_log(philo, MSG_FORK);
	if (pthread_mutex_lock(philo->right_fork) != MUTEX_SUCCESS)
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

t_result	put_two_forks(const t_philo *philo)
{
	if (pthread_mutex_unlock(philo->left_fork) != MUTEX_SUCCESS)
		return (FAILURE);
	if (pthread_mutex_unlock(philo->right_fork) != MUTEX_SUCCESS)
		return (FAILURE);
	return (SUCCESS);
}

// todo: usleep, return t_result
t_result	eating(const t_philo *philo)
{
	const long	time_to_eat = philo->args->time_to_eat;
	t_result	result;

	result = take_two_forks(philo);
	if (result == FAILURE || result == BREAK)
		return (result);

	if (is_any_philo_died(philo))
	{
		if (put_two_forks(philo) == FAILURE)
			return (FAILURE);
		return (BREAK);
	}
	philo->var->start_time_of_cycle = get_current_time(); // use put_log
	put_log(philo, MSG_EAT);
	usleep(time_to_eat * 1000);

	if (put_two_forks(philo) == FAILURE)
		return (FAILURE);
	return (SUCCESS);
}

// todo: usleep, return t_result
t_result	sleeping(const t_philo *philo)
{
	const long	time_to_sleep = philo->args->time_to_sleep;

	put_log(philo, MSG_SLEEP);
	usleep(time_to_sleep * 1000);
	return (SUCCESS);
}

// todo: return t_result
t_result	thinking(const t_philo *philo)
{
	put_log(philo, MSG_THINK);
	return (SUCCESS);
}
