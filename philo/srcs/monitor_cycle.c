#include <unistd.h> // usleep
#include "philo.h"
#include "utils.h"

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
	if (philo->is_self_dead) // todo: call_atomic()
		put_log(philo, MSG_DIED);
	ft_free((void **)&monitor);
	return (NULL);
}
