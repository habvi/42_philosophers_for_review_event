#include <unistd.h> // usleep
#include "philo.h"
#include "utils.h"

// todo: > ? >= ?
static bool	is_time_to_die_exceeded(const t_args *args, const t_philo *philo)
{
	const int64_t	elapsed_cycle_time = get_elapsed_cycle_time(philo);

	return (elapsed_cycle_time > args->time_to_die);
}

static t_result	set_and_put_philo_died(t_args *args, const t_philo *philo)
{
	pthread_mutex_t	*for_death;

	for_death = &args->for_death;
	if (pthread_mutex_lock(for_death) != MUTEX_SUCCESS)
		return (FAILURE);
	args->is_any_philo_died = true;
	put_log(philo, MSG_DIED);
	put(philo, "-----");
	if (pthread_mutex_unlock(for_death) != MUTEX_SUCCESS)
		return (FAILURE);
	return (SUCCESS);
}

void	*monitor_cycle(void *thread_args)
{
	t_monitor		*monitor;
	int				i;
	t_args			*args;
	t_philo			*philo;

	monitor = (t_monitor *)thread_args;
	i = monitor->id;
	args = monitor->args;
	philo = args->philos[i];
	while (!is_any_philo_died(philo))
	{
		if (!is_time_to_die_exceeded(args, philo))
		{
			usleep(500);
			continue ;
		}
		if (set_and_put_philo_died(args, philo) == FAILURE)
		{
			ft_free((void **)&monitor);
			return (NULL); // todo
		}
		break ;
	}
	ft_free((void **)&monitor);
	return (NULL);
}
