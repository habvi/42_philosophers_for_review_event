#include "philo.h"
#include "utils.h"

int64_t	call_atomic(pthread_mutex_t *mutex, int64_t (*func)(), void *args)
{
	int64_t	ret;

	pthread_mutex_lock(mutex);
	ret = func(args);
	pthread_mutex_unlock(mutex);
	return (ret);
}

static t_result	init_forks(t_args *args)
{
	pthread_mutex_t		*forks;
	const unsigned int	num_of_forks = args->num_of_philos;
	unsigned int		i;

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
	args->forks = forks;
	return (SUCCESS);
}

static t_result	init_other_mutex(t_args *args)
{
	if (pthread_mutex_init(&args->shared, NULL) != MUTEX_SUCCESS)
		return (FAILURE);
	return (SUCCESS);
}

t_result	init_mutex(t_args *args)
{
	if (init_forks(args) == FAILURE)
		return (FAILURE);
	if (init_other_mutex(args) == FAILURE)
	{
		destroy_forks(&args->forks, args->num_of_philos);
		return (FAILURE);
	}
	return (SUCCESS);
}
