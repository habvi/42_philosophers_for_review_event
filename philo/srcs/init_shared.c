#include "philo.h"

// even: take left_fork -> right_fork
// odd: take right_fork -> left_fork
static void	set_two_forks(t_philo *philo, \
						const unsigned int i, const unsigned int num_of_philos)
{
	if (i % 2 == 0)
	{
		philo->fork1 = &philo->shared->forks[i];
		philo->fork2 = &philo->shared->forks[(i + 1) % num_of_philos];
	}
	else
	{
		philo->fork1 = &philo->shared->forks[(i + 1) % num_of_philos];
		philo->fork2 = &philo->shared->forks[i];
	}
}

static void	set_shared_and_forks(\
			t_philo *philos, t_shared *shared, const unsigned int num_of_philos)
{
	unsigned int	i;

	i = 0;
	while (i < num_of_philos)
	{
		(&philos[i])->shared = shared;
		set_two_forks(&philos[i], i, num_of_philos);
		i++;
	}
}

t_result	init_shared(\
			t_philo *philos, t_shared *shared, const unsigned int num_of_philos)
{
	if (init_mutex(shared, num_of_philos) == FAILURE)
		return (FAILURE);
	set_shared_and_forks(philos, shared, num_of_philos);
	shared->start_time = 0;
	shared->is_any_philo_dead = false;
	shared->is_thread_error = false;
	shared->num_of_finish_eat = 0;
	return (SUCCESS);
}
