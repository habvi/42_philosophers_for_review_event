#include "philo.h"
#include "utils.h"

static bool	is_starved(t_philo *philo)
{
	int64_t	elapsed_cycle_time;

	philo->current_time = get_current_time_usec();
	elapsed_cycle_time = philo->current_time - philo->start_time_of_cycle;
	return (elapsed_cycle_time > philo->args.time_to_die);
}

static void	set_philo_dead(t_philo *philo)
{
	philo->is_self_dead = true;
	philo->shared->is_any_philo_dead = true;
}

int64_t	is_simulation_over(t_philo *philo)
{
	const t_shared	*shared = philo->shared;

	if (shared->is_any_philo_dead)
		return (true);
	if (shared->is_thread_error)
	{
		set_philo_dead(philo);
		return (true);
	}
	if (shared->num_of_finish_eat == philo->args.num_of_philos)
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

	shared = &philo->shared->shared;
	return (call_atomic(shared, is_simulation_over, philo));
}

int64_t	philo_action(t_philo *philo, int64_t (*action)(t_philo *))
{
	pthread_mutex_t	*shared;

	if (is_simulation_over_atomic(philo))
		return (FAILURE);
	shared = &philo->shared->shared;
	return (call_atomic(shared, action, (void *)philo));
}
