#include <stdio.h>
#include <unistd.h> // usleep
#include "philo.h"
#include "utils.h"

// todo: return
static void	*thread_func(void *thread_args)
{
	t_thread_info	*thread_info;
	t_args			*args;
	long			start_time;
	long			current_time;

	thread_info = (t_thread_info *)thread_args;
	args = thread_info->args;

	start_time = get_current_time();
	current_time = start_time;
	while ((current_time - start_time) < args->time_to_die)
	{
		if (pthread_mutex_lock(&args->left_fork) != MUTEX_SUCCESS)
		{
			perror("pthread_mutex_lock");
			return (NULL);
		}
		current_time = get_current_time();
		printf("%ld   %d has taken a left fork\n", current_time - start_time, thread_info->philo_id);

		if (pthread_mutex_lock(&args->right_fork) != MUTEX_SUCCESS)
		{
			perror("pthread_mutex_lock");
			return (NULL);
		}
		current_time = get_current_time();
		printf("%ld  %d has taken a right fork\n", current_time - start_time, thread_info->philo_id);

		current_time = get_current_time();
		printf("%ld  %d is eating\n", current_time - start_time, thread_info->philo_id);
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

		current_time = get_current_time();
		printf("%ld  %d is sleeping\n", current_time - start_time, thread_info->philo_id);
		usleep(args->time_to_sleep * 1000);

		current_time = get_current_time();
		printf("%ld  %d is thinking\n", current_time - start_time, thread_info->philo_id);
	}
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
