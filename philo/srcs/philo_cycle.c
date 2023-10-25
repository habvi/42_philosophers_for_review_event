#include "philo.h"
#include "utils.h"

static bool	is_within_time_to_die(const t_philo *philo)
{
	const long	elapsed_time = get_elapsed_time(philo);

	return (elapsed_time < philo->args->time_to_die);
}

void	*philo_cycle(void *thread_args)
{
	t_philo	*philo;

	philo = (t_philo *)thread_args;
	// todo: temp
	while (is_within_time_to_die(philo))
	{
		// todo: error(free)
		eating(philo);
		sleeping(philo);
		thinking(philo);
	}
	return (NULL);
}
