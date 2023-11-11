#include <unistd.h> // usleep
#include "philo.h"
#include "utils.h"

static bool	check_and_set_time_to_die_exceeded(t_args *args, t_philo *philo)
{
	pthread_mutex_t	*shared;
	const int64_t	current_time = get_current_time_msec();
	const int64_t	elapsed_time = current_time - philo->args->start_time;

	shared = &args->shared;
	pthread_mutex_lock(shared);
	if (is_starved(philo, current_time))
	{
		args->is_any_philo_died = true;
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
	philo = &args->philos[monitor->id];
	while (!is_simulation_over_atomic(philo))
	{
		if (check_and_set_time_to_die_exceeded(args, philo) == EXCEEDED)
			break ;
		usleep(500);
	}
	ft_free((void **)&monitor);
	return (NULL);
}
