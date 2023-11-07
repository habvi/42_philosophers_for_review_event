#include "philo.h"

int64_t	call_atomic(pthread_mutex_t *mutex, int64_t (*func)(), void *args)
{
	int64_t	ret;

	pthread_mutex_lock(mutex);
	ret = func(args);
	pthread_mutex_unlock(mutex);
	return (ret);
}

int64_t	is_simulation_over(t_philo *philo)
{
	const t_args	*args = philo->args;

	if (args->is_any_philo_died)
		return (true);
	if (args->is_thread_error)
		return (true);
	if (args->num_of_finish_eat == args->num_of_philos)
		return (true);
	return (false);
}

bool	is_simulation_over_atomic(t_philo *philo)
{
	pthread_mutex_t	*shared;

	shared = &philo->args->shared;
	return (call_atomic(shared, is_simulation_over, philo));
}

void	philo_action(t_philo *philo, int64_t (*action)(t_philo *))
{
	if (is_simulation_over_atomic(philo))
		return ;
	call_atomic(&philo->args->shared, action, (void *)philo);
}
