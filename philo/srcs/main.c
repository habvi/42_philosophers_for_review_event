#include "philo.h"

int	main(int argc, char *argv[])
{
	t_result		result;
	t_rule			rule;
	t_philo			*philos;
	t_shared		shared;
	pthread_mutex_t	*forks;

	if (!is_valid_argc(argc))
		return (error_args());
	result = set_rules(&rule, argc, (const char **)argv);
	if (result == FAILURE)
		return (error_args());
	philos = init_philos(&rule, &shared, &forks);
	if (philos == NULL)
		return (error_fatal());
	result = simulate_philos_cycle(philos, &shared, rule.num_of_philos);
	destroy_philos(&philos, &shared, &forks);
	if (result == FAILURE)
		return (error_fatal());
	return (EXIT_SUCCESS);
}
