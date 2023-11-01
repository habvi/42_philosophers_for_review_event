#include <stdio.h> // printf
#include "philo.h"

// todo: put_error,wait,destroy
static t_result	fatal_error(void)
{
	printf("%s\n", ERR_FATAL);
	return (FAILURE);
}

// todo: allocate philos here?
static t_result	run_philosophers(t_args *args)
{
	pthread_t	*philo_threads;
	pthread_t	*monitor_threads;

	if (init_mutex(args) == FAILURE)
		return (FAILURE);
	set_start_time(args);
	philo_threads = simulate_philos_cycle(args);
	if (philo_threads == NULL)
		return (fatal_error()); 
	monitor_threads = monitoring_death(args);
	if (monitor_threads == NULL)
		return (fatal_error());
	destroy(args, &philo_threads, &monitor_threads);
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
