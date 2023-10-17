#include <stdio.h>
#include "philo.h"

static t_result	run_philosophers(t_args *args)
{
	pthread_t	*threads;

	if (init_mutex(args) == FAILURE)
		return (FAILURE);
	threads = create_threads(args);
	if (threads == NULL)
		return (FAILURE);
	wait_threads(args, threads);
	destroy_threads(&threads);
	destroy_mutex(args);
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
