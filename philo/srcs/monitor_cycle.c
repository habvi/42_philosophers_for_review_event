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

	shared = &args->shared;
	pthread_mutex_lock(shared);
	if (is_time_to_die_exceeded(args, philo))
	{
		args->is_any_philo_died = true;
		put_log(philo, MSG_DIED, get_elapsed_time);
		pthread_mutex_unlock(shared);
		return (true);
	}
	pthread_mutex_unlock(shared);
	return (false);
}

// monitoring for death periodically with interval.
void	*monitor_cycle(void *thread_args)
{
	t_monitor		*monitor;
	unsigned int	i;
	t_args			*args;
	t_philo			*philo;

	monitor = (t_monitor *)thread_args;
	i = monitor->id;
	args = monitor->args;
	philo = args->philos[i];
	while (!is_any_philo_died(philo) && !args->is_error) // todo: is_error lock
	{
		if (check_and_set_time_to_die_exceeded(args, philo) == EXCEEDED)
			break ;
		usleep(500);
	}
	ft_free((void **)&monitor);
	return (NULL);
}
