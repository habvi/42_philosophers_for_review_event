#include "philo.h"

static bool	wait_start_cycle(t_args *args)
{
	bool	is_error;

	pthread_mutex_lock(&args->shared);
	is_error = args->is_error;
	pthread_mutex_unlock(&args->shared);
	return (is_error);
}

bool	is_any_philo_died(const t_philo *philo)
{
	pthread_mutex_t	*shared;
	bool			is_any_philo_died;

	shared = &philo->args->shared;
	pthread_mutex_lock(shared);
	is_any_philo_died = philo->args->is_any_philo_died;
	pthread_mutex_unlock(shared);
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
