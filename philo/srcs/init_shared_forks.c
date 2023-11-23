#include "philo.h"

static t_result	init_shared(t_shared *shared)
{
	if (pthread_mutex_init(&shared->shared, NULL) != MUTEX_SUCCESS)
		return (FAILURE);
	shared->start_time = 0;
	shared->is_any_philo_dead = false;
	shared->is_thread_error = false;
	shared->num_of_finish_eat = 0;
	return (SUCCESS);
}

static t_result	init_forks(\
					pthread_mutex_t **forks, const unsigned int num_of_forks)
{
	unsigned int	i;

	*forks = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) * num_of_forks);
	if (*forks == NULL)
		return (FAILURE);
	i = 0;
	while (i < num_of_forks)
	{
		if (pthread_mutex_init(&((*forks)[i]), NULL) != MUTEX_SUCCESS)
		{
			destroy_forks(forks, i);
			return (FAILURE);
		}
		i++;
	}
	return (SUCCESS);
}

// even: take left_fork -> right_fork
// odd: take right_fork -> left_fork
static void	set_two_forks(t_philo *philo, const unsigned int i, \
					pthread_mutex_t *forks, const unsigned int num_of_philos)
{
	if (i % 2 == 0)
	{
		philo->fork1 = &forks[i];
		philo->fork2 = &forks[(i + 1) % num_of_philos];
	}
	else
	{
		philo->fork1 = &forks[(i + 1) % num_of_philos];
		philo->fork2 = &forks[i];
	}
}

static void	set_mutex_to_philo(t_philo *philos, t_shared *shared, \
					pthread_mutex_t *forks, const unsigned int num_of_philos)
{
	unsigned int	i;

	i = 0;
	while (i < num_of_philos)
	{
		(&philos[i])->shared = shared;
		set_two_forks(&philos[i], i, forks, num_of_philos);
		i++;
	}
}

t_result	init_shared_and_forks(t_philo *philos, t_shared *shared, \
					pthread_mutex_t **forks, const unsigned int num_of_philos)
{
	if (init_shared(shared) == FAILURE)
		return (FAILURE);
	if (init_forks(forks, num_of_philos) == FAILURE)
	{
		destroy_mutex(shared, NULL, 0);
		return (FAILURE);
	}
	set_mutex_to_philo(philos, shared, *forks, num_of_philos);
	return (SUCCESS);
}
