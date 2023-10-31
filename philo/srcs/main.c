#include <stdio.h>
#include "philo.h"

// todo: allocate philos here
static t_result	run_philosophers(t_args *args)
{
	pthread_t	*threads;
	pthread_t	*monitors;

	if (init_mutex(args) == FAILURE)
		return (FAILURE);
	set_start_time(args);
	threads = create_threads(args);
	if (threads == NULL)
		return (FAILURE); // todo: wait,destroy
	monitors = monitor_death(args);
	if (monitors == NULL)
		return (FAILURE); // todo: wait,destroy
	wait_threads(args, threads, monitors);
	destroy(args, &threads, &monitors);
	return (SUCCESS);
}

int	main(int argc, char *argv[])
{
	t_args		args;
	t_result	result;

	if (!is_valid_argc(argc))
	{
		printf("Error: invalid arguments.\n");
		return (EXIT_FAILURE);
	}
	args = set_args(argc, (const char **)argv, &result);
	if (result == FAILURE)
		return (EXIT_FAILURE);
	result = run_philosophers(&args);
	if (result == FAILURE)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
