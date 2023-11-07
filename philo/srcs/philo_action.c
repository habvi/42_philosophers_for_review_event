#include "philo.h"

int64_t	call_atomic(pthread_mutex_t *mutex, int64_t (*func)(), void *args)
{
	int64_t	ret;

	pthread_mutex_lock(mutex);
	ret = func(args);
	pthread_mutex_unlock(mutex);
	return (ret);
}

static int64_t	get_is_any_philo_died(t_philo *philo)
{
	return (philo->args->is_any_philo_died);
}

bool	is_any_philo_died(t_philo *philo)
{
	pthread_mutex_t	*shared;

	shared = &philo->args->shared;
	return (call_atomic(shared, get_is_any_philo_died, philo));
}

void	philo_action(t_philo *philo, int64_t (*action)(t_philo *))
{
	if (is_any_philo_died(philo))
		return ;
	call_atomic(&philo->args->shared, action, (void *)philo);
}
