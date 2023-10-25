#include <stdio.h>
#include "philo.h"
#include "utils.h"

// todo: error
static void	set_start_time(t_args *args)
{
	args->start_time = get_current_time();
}

static t_result	run_philosophers(t_args *args)
{
	pthread_t	*threads;

	if (init_mutex(args) == FAILURE)
		return (FAILURE);
	set_start_time(args);
	threads = create_threads(args);
	if (threads == NULL)
		return (FAILURE); // todo: wait,destroy
	wait_threads(args, threads);
	destroy(args, &threads);
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
	return (result);
}
