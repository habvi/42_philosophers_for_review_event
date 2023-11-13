#include <unistd.h> // usleep
#include "philo.h"
#include "utils.h"

// todo: don't need atomic...?
static int64_t	put_self_dead(t_philo *philo)
{
	if (philo->is_self_dead)
		put_log(philo, MSG_DIED);
	return (SUCCESS);
}

// monitoring for death periodically with interval.
void	*monitor_cycle(void *thread_args)
{
	t_monitor	*monitor;
	t_args		*args;
	t_philo		*philo;

	monitor = (t_monitor *)thread_args;
	args = monitor->args;
	philo = &args->philos[monitor->id];
	while (!is_simulation_over_atomic(philo))
		usleep(500);
	call_atomic(&args->shared, put_self_dead, philo);
	ft_free((void **)&monitor);
	return (NULL);
}
