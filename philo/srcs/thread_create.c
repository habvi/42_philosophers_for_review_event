#include <stdio.h>
#include <unistd.h> // usleep
#include "philo.h"
#include "utils.h"

// todo: return
static void	*thread_func(void *thread_args)
{
	t_thread_info	*thread_info;
	t_args			*args;

	thread_info = (t_thread_info *)thread_args;
	args = thread_info->args;

	if (pthread_mutex_lock(&args->left_fork) != MUTEX_SUCCESS)
	{
		perror("pthread_mutex_lock");
		return (NULL);
	}
	put_current_time();
	printf("%d has taken a left fork\n", thread_info->philo_id);

	if (pthread_mutex_lock(&args->right_fork) != MUTEX_SUCCESS)
	{
		perror("pthread_mutex_lock");
		return (NULL);
	}
	put_current_time();
	printf("%d has taken a right fork\n", thread_info->philo_id);

	put_current_time();
	printf("%d is eating\n", thread_info->philo_id);
	usleep(args->time_to_eat * 1000);

	if (pthread_mutex_unlock(&args->left_fork) != MUTEX_SUCCESS)
	{
		perror("pthread_mutex_unlock");
		return (NULL);
	}
	if (pthread_mutex_unlock(&args->right_fork) != MUTEX_SUCCESS)
	{
		perror("pthread_mutex_unlock");
		return (NULL);
	}

	put_current_time();
	printf("%d is sleeping\n", thread_info->philo_id);
	usleep(args->time_to_sleep * 1000);

	put_current_time();
	printf("%d is thinking\n", thread_info->philo_id);
	free(thread_info);
	return (NULL);
}

static t_thread_info	*set_thread_info(int i, t_args *args)
{
	t_thread_info	*thread_info;

	thread_info = (t_thread_info *)malloc(sizeof(t_thread_info) * 1);
	// todo: error
	if (thread_info == NULL)
		return (NULL);
	thread_info->philo_id = i;
	thread_info->args = args;
	return (thread_info);
}

// todo: exit -> return error
pthread_t	*create_threads(t_args *args)
{
	pthread_t		*threads;
	int				i;
	t_thread_info	*thread_info;

	threads = (pthread_t *)malloc(sizeof(pthread_t) * args->number_of_philos);
	if (threads == NULL)
		return (NULL);
	i = 0;
	while (i < args->number_of_philos)
	{
		thread_info = set_thread_info(i, args);
		if (pthread_create(&threads[i], NULL, thread_func, thread_info) != THREAD_SUCCESS)
		{
			perror("pthread_create");
			exit(EXIT_FAILURE);
		}
		i++;
	}
	return (threads);
}
