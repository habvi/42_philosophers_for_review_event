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

static void	adjust_simulation_start(t_philo *philo)
{
	const unsigned int	num_of_philos = philo->args.num_of_philos;
	const unsigned int	id = philo->id;
	unsigned int		times;
	const int64_t		base_time = ft_max(0, philo->args.time_to_sleep \
											+ philo->args.time_to_think \
											- philo->args.time_to_eat);
	const int64_t		cycle_time = philo->args.time_to_eat \
									+ philo->args.time_to_sleep \
									+ philo->args.time_to_think;

	if (num_of_philos % 2 == 0)
	{
		if (id % 2 == 1)
			usleep_gradual(philo->args.time_to_eat / 2, philo);
	}
	else
	{
		times = id / 2;
		if (id % 2 == 1)
			times += num_of_philos / 2 + 1;
		if (cycle_time == 0)
			return ;
		usleep_gradual(base_time * times % cycle_time, philo);
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
