#include <stdio.h>
#include <unistd.h> // usleep
#include "philo.h"
#include "utils.h"

// static void	interval(const int id)
// {
// 	if (id % 2)
// 		usleep(50);
// }

// todo: return t_result
static void	put_log(const t_philo *philo, const char *message)
{
	const long		start_time = philo->args->start_time;
	const long		current_time = get_current_time();
	const long		elapsed_time = current_time - start_time;
	pthread_mutex_t	*for_log;

	for_log = &philo->args->for_log;
	if (pthread_mutex_lock(for_log) != MUTEX_SUCCESS)
	{
		perror("pthread_mutex_lock");
		return ;
	}
	printf("%ld %d %s\n", elapsed_time, philo->id, message);
	if (pthread_mutex_unlock(for_log) != MUTEX_SUCCESS)
	{
		perror("pthread_mutex_unlock");
		return ;
	}
}

// todo: usleep
t_result	eating(const t_philo *philo)
{
	const long	time_to_eat = philo->args->time_to_eat;

	// interval(philo->id);
	if (pthread_mutex_lock(philo->left_fork) != MUTEX_SUCCESS)
	{
		perror("pthread_mutex_lock");
		return (FAILURE);
	}
	put_log(philo, "has taken a fork");

	if (pthread_mutex_lock(philo->right_fork) != MUTEX_SUCCESS)
	{
		perror("pthread_mutex_lock");
		return (FAILURE);
	}
	put_log(philo, "has taken a fork");

	put_log(philo, "is eating");
	usleep(time_to_eat * 1000);

	if (pthread_mutex_unlock(philo->left_fork) != MUTEX_SUCCESS)
	{
		perror("pthread_mutex_unlock");
		return (FAILURE);
	}
	if (pthread_mutex_unlock(philo->right_fork) != MUTEX_SUCCESS)
	{
		perror("pthread_mutex_unlock");
		return (FAILURE);
	}
	return (SUCCESS);
}

// todo: usleep, return t_result
void	sleeping(const t_philo *philo)
{
	const long	time_to_sleep = philo->args->time_to_sleep;

	put_log(philo, "is sleeping");
	usleep(time_to_sleep * 1000);
}

// todo: return t_result
void	thinking(const t_philo *philo)
{
	put_log(philo, "is thinking");
}
