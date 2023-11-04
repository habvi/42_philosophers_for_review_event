#include <unistd.h> // usleep
#include "philo.h"
#include "utils.h"

// todo: > ? >= ?
static bool	is_time_to_die_exceeded(const t_args *args, const t_philo *philo)
{
	const int64_t	elapsed_cycle_time = get_elapsed_cycle_time(philo);

	return (elapsed_cycle_time > args->time_to_die);
}

static void	set_and_put_philo_died(t_args *args, const t_philo *philo)
{
	pthread_mutex_t	*for_death;

	for_death = &args->for_death;
	pthread_mutex_lock(for_death);
	args->is_any_philo_died = true;
	put_log(philo, MSG_DIED);
	put(philo, "-----"); // todo: erase
	pthread_mutex_unlock(for_death);
}

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
	while (!is_any_philo_died(philo) && !args->is_error) // todo: is_error lock?
	{
		if (is_time_to_die_exceeded(args, philo))
		{
			set_and_put_philo_died(args, philo);
			break ;
		}
		usleep(500);
	}
	ft_free((void **)&monitor);
	return (NULL);
}
