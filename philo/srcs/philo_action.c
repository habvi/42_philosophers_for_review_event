#include "philo.h"
#include "utils.h"

// todo: > ? >= ?
static bool	is_starved(t_philo *philo)
{
	int64_t	elapsed_cycle_time;

	philo->current_time = get_current_time_msec();
	elapsed_cycle_time = philo->current_time - philo->start_time_of_cycle;
	return (elapsed_cycle_time > philo->args->time_to_die);
}

static void	set_philo_dead(t_philo *philo)
{
	philo->is_self_dead = true;
	philo->args->is_any_philo_dead = true;
}

int64_t	is_simulation_over(t_philo *philo)
{
	const t_args	*args = philo->args;

	if (args->is_any_philo_dead)
		return (true);
	if (args->is_thread_error)
	{
		set_philo_dead(philo);
		return (true);
	}
	if (args->num_of_finish_eat == args->num_of_philos)
	{
		set_philo_dead(philo);
		return (true);
	}
	if (is_starved(philo))
	{
		set_philo_dead(philo);
		return (true);
	}
	return (false);
}

bool	is_simulation_over_atomic(t_philo *philo)
{
	pthread_mutex_t	*shared;

	shared = &philo->args->shared;
	return (call_atomic(shared, is_simulation_over, philo));
}

int64_t	philo_action(t_philo *philo, int64_t (*action)(t_philo *))
{
	if (is_simulation_over_atomic(philo))
		return (FAILURE);
	return (call_atomic(&philo->args->shared, action, (void *)philo));
}
