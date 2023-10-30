#include "philo.h"
#include "utils.h"

// todo: error
static t_result	wait_start_cycle(t_args *args)
{
	if (pthread_mutex_lock(&args->start_cycle) != MUTEX_SUCCESS)
		return (FAILURE);
	if (pthread_mutex_unlock(&args->start_cycle) != MUTEX_SUCCESS)
		return (FAILURE);
	return (SUCCESS);
}

// todo: error
static bool	is_any_philo_died(const t_philo *philo)
{
	pthread_mutex_t	*for_death;
	bool			is_any_philo_died;

	for_death = &philo->args->for_death;
	if (pthread_mutex_lock(for_death) != MUTEX_SUCCESS)
		return (false); // todo: FAILURE
	is_any_philo_died = philo->args->is_any_philo_died;
	if (pthread_mutex_unlock(for_death) != MUTEX_SUCCESS)
		return (false); // todo: FAILURE
	return (is_any_philo_died);
}

static bool	is_time_to_die_exceeded(const t_philo *philo)
{
	// const long	elapsed_time = get_elapsed_time(philo);

	// return (elapsed_time > philo->args->time_to_die);

	const long	elapsed_cycle_time = get_elapsed_cycle_time(philo);

	return (elapsed_cycle_time > philo->args->time_to_die);
}

static t_result	set_philo_death(const t_philo *philo)
{
	pthread_mutex_t	*for_death;

	for_death = &philo->args->for_death;
	if (pthread_mutex_lock(for_death) != MUTEX_SUCCESS)
		return (FAILURE);
	philo->args->is_any_philo_died = true;
	if (pthread_mutex_unlock(for_death) != MUTEX_SUCCESS)
		return (FAILURE);
	return (SUCCESS);
}

static t_result	philo_action(const t_philo *philo, t_result (*action)(const t_philo *))
{
	if (is_time_to_die_exceeded(philo))
	{
		if (set_philo_death(philo) == FAILURE)
			return (FAILURE);
	}
	if (is_any_philo_died(philo))
		return (SUCCESS);
	action(philo);
	return (SUCCESS);
}

// todo: return t_result?
void	*philo_cycle(void *thread_args)
{
	const t_philo	*philo = (const t_philo *)thread_args;

	if (wait_start_cycle(philo->args) == FAILURE)
		return (NULL); // todo
	while (!is_any_philo_died(philo))
	{
		// philo_action(philo, &take_two_forks);
		philo_action(philo, &eating);
		// philo_action(philo, &put_two_forks);
		philo_action(philo, &sleeping);
		philo_action(philo, &thinking);
	}
	put_log(philo, MSG_DIED);
	return (NULL);
}
