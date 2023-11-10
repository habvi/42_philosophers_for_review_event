#include "philo.h"

static int64_t	get_is_thread_error(t_args *args)
{
	return (args->is_thread_error);
}

static bool	wait_start_cycle(t_args *args)
{
	return (call_atomic(&args->shared, get_is_thread_error, args));
}

void	*philo_solo_cycle(void *thread_args)
{
	t_philo	*philo;
	bool	is_thread_error;

	philo = (t_philo *)thread_args;
	is_thread_error = wait_start_cycle(philo->args);
	if (is_thread_error)
		return (NULL);
	take_fork(philo->left_fork, philo);
	put_fork(philo->left_fork);
	return (NULL);
}

void	*philo_cycle(void *thread_args)
{
	t_philo	*philo;
	bool	is_thread_error;

	philo = (t_philo *)thread_args;
	is_thread_error = wait_start_cycle(philo->args);
	if (is_thread_error)
		return (NULL);
	while (!is_simulation_over_atomic(philo))
	{
		take_two_forks(philo);
		eating(philo);
		put_two_forks(philo);
		sleeping(philo);
		thinking(philo);
	}
	// put_log(get_elapsed_time(philo), philo->id, MSG_DIED); // todo: erase
	return (NULL);
}
