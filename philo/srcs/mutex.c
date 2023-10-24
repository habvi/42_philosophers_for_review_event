#include <stdio.h>
#include "philo.h"
#include "utils.h"

static void	destroy_forks(t_args *args)
{
	int	i;

	i = 0;
	while (i < args->num_of_philos)
	{
		pthread_mutex_destroy(&args->forks[i]);
		i++;
	}
	ft_free((void **)&args->forks);
}

void	destroy_mutex(t_args *args)
{
	destroy_forks(args);
	pthread_mutex_destroy(&args->for_log);
}

static t_result	init_forks(t_args *args)
{
	pthread_mutex_t	*forks;
	const int		num_of_forks = args->num_of_philos;
	int				i;

	forks = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) * num_of_forks);
	if (forks == NULL)
		return (FAILURE);
	i = 0;
	while (i < num_of_forks)
	{
		if (pthread_mutex_init(&forks[i], NULL) != MUTEX_SUCCESS)
		{
			destroy_forks(args);
			return (FAILURE);
		}
		i++;
	}
	args->forks = forks;
	return (SUCCESS);
}

static t_result	init_other_mutex(t_args *args)
{
	if (pthread_mutex_init(&args->for_log, NULL) != MUTEX_SUCCESS)
		return (FAILURE);
	return (SUCCESS);
}

t_result	init_mutex(t_args *args)
{
	if (init_forks(args) == FAILURE)
		return (FAILURE);
	if (init_other_mutex(args) == FAILURE)
	{
		destroy_forks(args);
		return (FAILURE);
	}
	return (SUCCESS);
}
