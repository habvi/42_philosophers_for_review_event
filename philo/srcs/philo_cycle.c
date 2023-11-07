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
	return (philo->args->is_any_philo_died);
}

bool	is_any_philo_died_atomic(const t_philo *philo)
{
	pthread_mutex_t	*shared;
	bool			is_any_philo_died;

	shared = &philo->args->shared;
	pthread_mutex_lock(shared);
	is_any_philo_died = philo->args->is_any_philo_died;
	pthread_mutex_unlock(shared);
	return (is_any_philo_died);
}

void	philo_action(t_philo *philo, int64_t (*action)(t_philo *))
{
	if (is_any_philo_died_atomic(philo))
		return ;
	call_atomic(&philo->args->shared, action, (void *)philo);
}

void	*philo_cycle(void *thread_args)
{
	t_philo	*philo;
	bool	is_error;

	philo = (t_philo *)thread_args;
	is_error = wait_start_cycle(philo->args);
	if (is_error)
		return (NULL);
	while (!is_any_philo_died_atomic(philo))
	{
		take_two_forks(philo);
		eating(philo);
		put_two_forks(philo);
		sleeping(philo);
		thinking(philo);
	}
	// put_log(philo, MSG_DIED); // todo: erase
	return (NULL);
}
