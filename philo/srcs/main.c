#include "philo.h"

int	main(int argc, char *argv[])
{
	t_result		result;
	t_args			args;
	t_philo			*philos;
	t_shared		shared;
	pthread_mutex_t	*forks;

	if (!is_valid_argc(argc))
		return (EXIT_FAILURE);
	args = set_args(argc, (const char **)argv, &result);
	if (result == FAILURE)
		return (EXIT_FAILURE);
	philos = init_philos(&args, &shared, &forks);
	if (philos == NULL)
		return (error_fatal());
	result = simulate_philos_cycle(philos, &shared, args.num_of_philos);
	destroy_philos(&philos, &shared, &forks);
	if (result == FAILURE)
		return (error_fatal());
	return (EXIT_SUCCESS);
}
