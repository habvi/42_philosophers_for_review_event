#include <unistd.h> // usleep
#include "philo.h"
#include "utils.h"

// todo: > ? >= ?
static bool	is_time_to_die_exceeded(const t_args *args, const t_philo *philo)
{
	const int64_t	elapsed_cycle_time = \
							get_elapsed_cycle_time(philo->start_time_of_cycle);

	return (elapsed_cycle_time > args->time_to_die);
}

static bool	check_and_set_time_to_die_exceeded(t_args *args, t_philo *philo)
{
	pthread_mutex_t	*shared;
	int64_t			elapsed_time;

	shared = &args->shared;
	pthread_mutex_lock(shared);
	if (is_time_to_die_exceeded(args, philo))
	{
		args->is_any_philo_died = true;
		elapsed_time = get_elapsed_time(philo);
		put_log(elapsed_time, philo->id, MSG_DIED);
		pthread_mutex_unlock(shared);
		return (true);
	}
	pthread_mutex_unlock(shared);
	return (false);
}

// monitoring for death periodically with interval.
void	*monitor_cycle(void *thread_args)
{
	t_monitor	*monitor;
	t_args		*args;
	t_philo		*philo;

	monitor = (t_monitor *)thread_args;
	args = monitor->args;
	philo = args->philos[monitor->id];
	while (!is_simulation_over_atomic(philo))
	{
		if (check_and_set_time_to_die_exceeded(args, philo) == EXCEEDED)
			break ;
		usleep(500);
	}
	ft_free((void **)&monitor);
	return (NULL);
}
