#include <unistd.h> // usleep
#include "philo.h"
#include "utils.h"

void	*philo_solo_cycle(void *thread_args)
{
	t_philo	*philo;
	bool	is_thread_error;

	philo = (t_philo *)thread_args;
	is_thread_error = wait_start(philo);
	if (is_thread_error)
		return (NULL);
	take_fork(philo->fork1, philo);
	put_fork(philo->fork1);
	return (NULL);
}

static int64_t	calc_delay_time_in_odd(t_args args, const unsigned int id)
{
	const int64_t	base_time = args.time_to_eat * id;
	const int64_t	cycle_time = args.time_to_eat \
								+ args.time_to_sleep \
								+ args.time_to_think;

	if (cycle_time == 0)
		return (0);
	return (base_time % cycle_time);
}

static void	adjust_simulation_start(t_philo *philo)
{
	const unsigned int	num_of_philos = philo->args.num_of_philos;
	int64_t				delay_time;

	if (num_of_philos % 2 == 0)
	{
		if (philo->id % 2 == 1)
			usleep_gradual(philo->args.time_to_eat / 2, philo);
	}
	else
	{
		delay_time = calc_delay_time_in_odd(philo->args, philo->id);
		usleep_gradual(delay_time, philo);
	}
}

void	*philo_cycle(void *thread_args)
{
	t_philo	*philo;
	bool	is_thread_error;

	philo = (t_philo *)thread_args;
	is_thread_error = wait_start(philo);
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
