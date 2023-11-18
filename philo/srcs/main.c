#include "philo.h"

static t_result	run_philosophers(t_args *args)
{
	t_shared	shared;
	t_result	result;

	if (init_shared(args, &shared) == FAILURE)
		return (FAILURE);
	set_start_time(args);
	result = simulate_philos_cycle(args, &shared);
	if (result == FAILURE)
		return (fatal_error());
	result = monitoring_death(args, &shared);
	if (result == FAILURE)
		return (fatal_error());
	destroy(args, &shared);
	return (SUCCESS);
}

int	main(int argc, char *argv[])
{
	t_args		args;
	t_result	result;

	if (!is_valid_argc(argc))
		return (EXIT_FAILURE);
	args = set_args(argc, (const char **)argv, &result);
	if (result == FAILURE)
		return (EXIT_FAILURE);
	result = run_philosophers(&args);
	if (result == FAILURE)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
