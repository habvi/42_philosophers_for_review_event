#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include "philo.h"
#include "utils.h"

static void	*thread_func(void *args)
{
	printf("\n--- thread start ---\n");
	put_args(args);
	printf("--- thread end ---\n\n");
	return (NULL);
}

// todo: exit -> return error
static pthread_t	create_thread(t_args *args)
{
	pthread_t	thread;

	if (pthread_create(&thread, NULL, thread_func, args) != THREAD_SUCCESS)
	{
		perror("pthread_create");
		exit(EXIT_FAILURE);
	}
	return (thread);
}

// todo: exit -> return error
static void	wait_thread(pthread_t thread)
{
	if (pthread_join(thread, NULL) != THREAD_SUCCESS)
	{
		perror("pthread_join");
		exit(EXIT_FAILURE);
	}
}

static void	run_philosophers(t_args args)
{
	pthread_t	thread;

	thread = create_thread(&args);
	wait_thread(thread);
}

int	main(int argc, char *argv[])
{
	t_args	args;

	if (!is_valid_argc(argc))
	{
		printf("Error: invalid arguments.\n");
		return (EXIT_FAILURE);
	}
	set_args(argc, argv, &args);
	run_philosophers(args);
	return (EXIT_SUCCESS);
}
