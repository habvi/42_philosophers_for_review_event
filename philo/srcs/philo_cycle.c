#include "philo.h"

static void	wait_start_cycle(t_args *args)
{
	pthread_mutex_lock(&args->start_cycle);
	pthread_mutex_unlock(&args->start_cycle);
}

bool	is_any_philo_died(const t_philo *philo)
{
	pthread_mutex_t	*for_death;
	bool			is_any_philo_died;

	for_death = &philo->args->for_death;
	pthread_mutex_lock(for_death);
	is_any_philo_died = philo->args->is_any_philo_died;
	pthread_mutex_unlock(for_death);
	return (is_any_philo_died);
}

static t_result	philo_action(\
						const t_philo *philo, void (*action)(const t_philo *))
{
	if (is_any_philo_died(philo))
		return (SUCCESS);
	action(philo);
	return (SUCCESS);
}

// todo: return t_result?
void	*philo_cycle(void *thread_args)
{
	const t_philo	*philo = (const t_philo *)thread_args;

	wait_start_cycle(philo->args);
	while (!is_any_philo_died(philo))
	{
		// philo_action(philo, &take_two_forks);
		philo_action(philo, &eating);
		// philo_action(philo, &put_two_forks);
		philo_action(philo, &sleeping);
		philo_action(philo, &thinking);
	}
	put_log(philo, MSG_DIED); // todo: erase
	return (NULL);
}
