#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include "philo.h"
#include "result.h"
#include "utils.h"

static void	*thread_func(void *args)
{
	printf("\n--- thread start ---\n");
	put_args(args);
	printf("--- thread end ---\n\n");
	return (NULL);
}

// todo: exit -> return error
static pthread_t	*create_threads(t_args *args)
{
	pthread_t	*threads;
	int			i;

	threads = (pthread_t *)malloc(sizeof(pthread_t) * args->number_of_philosophers);
	if (threads == NULL)
		return (NULL);
	i = 0;
	while (i < args->number_of_philosophers)
	{
		if (pthread_create(&threads[i], NULL, thread_func, args) != THREAD_SUCCESS)
		{
			perror("pthread_create");
			exit(EXIT_FAILURE);
		}
		i++;
	}
	return (threads);
}

static void	wait_threads(const t_args *args, pthread_t *threads)
{
	int	i;

	i = 0;
	while (i < args->number_of_philosophers)
	{
		if (pthread_join(threads[i], NULL) != THREAD_SUCCESS)
			perror("pthread_join");
		i++;
	}
}

static void	destroy_threads(pthread_t **threads)
{
	free(*threads);
	threads = NULL;
}

static t_result	run_philosophers(t_args *args)
{
	pthread_t	*threads;

	threads = create_threads(args);
	if (threads == NULL)
		return (FAILURE);
	wait_threads(args, threads);
	destroy_threads(&threads);
	return (SUCCESS);
}

int	main(int argc, char *argv[])
{
	t_args		args;
	t_result	result;

	if (!is_valid_argc(argc))
	{
		printf("Error: invalid arguments.\n");
		return (FAILURE);
	}
	args = set_args(argc, (const char **)argv);
	result = run_philosophers(&args);
	return (result);
}
