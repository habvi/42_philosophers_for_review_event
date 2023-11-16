#include <unistd.h> // usleep
#include "philo.h"
#include "utils.h"

static int64_t	get_is_thread_error(const t_shared *shared)
{
	return (shared->is_thread_error);
}

static bool	wait_start_cycle(t_shared *shared)
{
	return (call_atomic(&shared->shared, get_is_thread_error, shared));
}

void	*philo_solo_cycle(void *thread_args)
{
	t_philo	*philo;
	bool	is_thread_error;

	philo = (t_philo *)thread_args;
	is_thread_error = wait_start_cycle(philo->shared);
	if (is_thread_error)
		return (NULL);
	take_fork(philo->fork1, philo);
	put_fork(philo->fork1);
	return (NULL);
}

static void	adjust_simulation_start(const t_philo *philo)
{
	const unsigned int	num_of_philos = philo->args.num_of_philos;
	const unsigned int	id = philo->id;
	unsigned int		x;
	const int64_t		cycle_time = philo->args.time_to_eat \
									+ philo->args.time_to_sleep \
									+ philo->args.time_to_think;

	if (num_of_philos % 2 == 0)
	{
		if (philo->id % 2 == 1)
			usleep(200);
	}
	else
	{
		if (id % 2 == 0)
			x = id / 2;
		else
			x = (num_of_philos / 2 + 1) + id / 2;
		usleep((philo->args.time_to_think * x) % cycle_time);
	}
}

void	*philo_cycle(void *thread_args)
{
	t_philo	*philo;
	bool	is_thread_error;

	philo = (t_philo *)thread_args;
	is_thread_error = wait_start_cycle(philo->shared);
	if (is_thread_error)
		return (NULL);
	adjust_simulation_start(philo);
	while (!is_simulation_over_atomic(philo))
	{
		take_two_forks(philo);
		eating(philo);
		put_two_forks(philo);
		sleeping(philo);
		thinking(philo);
	}
	return (NULL);
}
