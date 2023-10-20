#include <stdio.h>
#include <unistd.h> // usleep
#include "philo.h"
#include "utils.h"

// todo: usleep
t_result	eating(t_philo *philo, t_args *args, long start_time, long *current_time)
{
	if (pthread_mutex_lock(&args->left_fork) != MUTEX_SUCCESS)
	{
		perror("pthread_mutex_lock");
		return (FAILURE);
	}
	*current_time = get_current_time();
	printf("%ld   %d has taken a left fork\n", *current_time - start_time, philo->id);

	if (pthread_mutex_lock(&args->right_fork) != MUTEX_SUCCESS)
	{
		perror("pthread_mutex_lock");
		return (FAILURE);
	}
	*current_time = get_current_time();
	printf("%ld  %d has taken a right fork\n", *current_time - start_time, philo->id);

	*current_time = get_current_time();
	printf("%ld  %d is eating\n", *current_time - start_time, philo->id);
	usleep(args->time_to_eat * 1000);

	if (pthread_mutex_unlock(&args->left_fork) != MUTEX_SUCCESS)
	{
		perror("pthread_mutex_unlock");
		return (FAILURE);
	}
	if (pthread_mutex_unlock(&args->right_fork) != MUTEX_SUCCESS)
	{
		perror("pthread_mutex_unlock");
		return (FAILURE);
	}
	return (SUCCESS);
}

// todo: usleep, return t_result
void	sleeping(t_philo *philo, t_args *args, long start_time, long *current_time)
{
	*current_time = get_current_time();
	printf("%ld  %d is sleeping\n", *current_time - start_time, philo->id);
	usleep(args->time_to_sleep * 1000);
}

// todo: return t_result
void	thinking(t_philo *philo, long start_time, long *current_time)
{
	*current_time = get_current_time();
	printf("%ld  %d is thinking\n", *current_time - start_time, philo->id);
}
