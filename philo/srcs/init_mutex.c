#include "philo.h"

static t_result	init_forks(t_shared *shared, const unsigned int num_of_forks)
{
	pthread_mutex_t	*forks;
	unsigned int	i;

	forks = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) * num_of_forks);
	if (forks == NULL)
		return (FAILURE);
	i = 0;
	while (i < num_of_forks)
	{
		if (pthread_mutex_init(&forks[i], NULL) != MUTEX_SUCCESS)
		{
			destroy_forks(&forks, i);
			return (FAILURE);
		}
		i++;
	}
	shared->forks = forks;
	return (SUCCESS);
}

static t_result	init_other_mutex(pthread_mutex_t *shared)
{
	if (pthread_mutex_init(shared, NULL) != MUTEX_SUCCESS)
		return (FAILURE);
	return (SUCCESS);
}

t_result	init_mutex(t_shared *shared, const unsigned int num_of_philos)
{
	if (init_forks(shared, num_of_philos) == FAILURE)
		return (FAILURE);
	if (init_other_mutex(&shared->shared) == FAILURE)
	{
		destroy_forks(&shared->forks, num_of_philos);
		return (FAILURE);
	}
	return (SUCCESS);
}
