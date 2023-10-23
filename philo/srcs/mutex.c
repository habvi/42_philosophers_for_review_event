#include <stdio.h>
#include "philo.h"

t_result	init_mutex(t_args *args)
{
	if (pthread_mutex_init(&args->left_fork, NULL) != MUTEX_SUCCESS)
	{
		perror("pthread_mutex_init");
		return (FAILURE);
	}
	if (pthread_mutex_init(&args->right_fork, NULL) != MUTEX_SUCCESS)
	{
		perror("pthread_mutex_init");
		return (FAILURE);
	}
	if (pthread_mutex_init(&args->for_log, NULL) != MUTEX_SUCCESS)
	{
		perror("pthread_mutex_init");
		return (FAILURE);
	}
	return (SUCCESS);
}

void	destroy_mutex(t_args *args)
{
	pthread_mutex_destroy(&args->left_fork);
	pthread_mutex_destroy(&args->right_fork);
	pthread_mutex_destroy(&args->for_log);
}
