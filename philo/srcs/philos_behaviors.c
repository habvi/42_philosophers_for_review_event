#include <stdio.h>
#include <unistd.h> // usleep
#include "philo.h"
#include "utils.h"

// todo: usleep
t_result	eating(const t_philo *philo, long *current_time)
{
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	const long		start_time = philo->args->start_time;
	const long		time_to_eat = philo->args->time_to_eat;

	left_fork = &philo->args->left_fork;
	right_fork = &philo->args->right_fork;
	if (pthread_mutex_lock(left_fork) != MUTEX_SUCCESS)
	{
		perror("pthread_mutex_lock");
		return (FAILURE);
	}
	*current_time = get_current_time();
	printf("%ld   %d has taken a left fork\n", *current_time - start_time, philo->id);

	if (pthread_mutex_lock(right_fork) != MUTEX_SUCCESS)
	{
		perror("pthread_mutex_lock");
		return (FAILURE);
	}
	*current_time = get_current_time();
	printf("%ld  %d has taken a right fork\n", *current_time - start_time, philo->id);

	*current_time = get_current_time();
	printf("%ld  %d is eating\n", *current_time - start_time, philo->id);
	usleep(time_to_eat * 1000);

	if (pthread_mutex_unlock(left_fork) != MUTEX_SUCCESS)
	{
		perror("pthread_mutex_unlock");
		return (FAILURE);
	}
	if (pthread_mutex_unlock(right_fork) != MUTEX_SUCCESS)
	{
		perror("pthread_mutex_unlock");
		return (FAILURE);
	}
	return (SUCCESS);
}

// todo: usleep, return t_result
void	sleeping(const t_philo *philo, long *current_time)
{
	const long	start_time = philo->args->start_time;
	const long	time_to_sleep = philo->args->time_to_sleep;

	*current_time = get_current_time();
	printf("%ld  %d is sleeping\n", *current_time - start_time, philo->id);
	usleep(time_to_sleep * 1000);
}

// todo: return t_result
void	thinking(const t_philo *philo, long *current_time)
{
	const long	start_time = philo->args->start_time;

	*current_time = get_current_time();
	printf("%ld  %d is thinking\n", *current_time - start_time, philo->id);
}
