#include "philo.h"

static bool	wait_start_cycle(t_args *args)
{
	bool	is_error;

	pthread_mutex_lock(&args->start_cycle);
	is_error = args->is_error;
	pthread_mutex_unlock(&args->start_cycle);
	return (is_error);
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

static void	philo_action(const t_philo *philo, void (*action)(const t_philo *))
{
	if (is_any_philo_died(philo))
		return ;
	action(philo);
}

void	*philo_cycle(void *thread_args)
{
	const t_philo	*philo = (const t_philo *)thread_args;
	bool			is_error;

	is_error = wait_start_cycle(philo->args);
	if (is_error)
		return (NULL);
	while (!is_any_philo_died(philo))
	{
		philo_action(philo, &eating);
		philo_action(philo, &sleeping);
		philo_action(philo, &thinking);
	}
	// put_log(philo, MSG_DIED); // todo: erase
	return (NULL);
}
