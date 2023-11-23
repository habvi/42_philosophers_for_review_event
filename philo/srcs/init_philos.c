#include "philo.h"
#include "utils.h"

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

static void	set_philos(t_philo *philos, \
						t_args *args, t_shared *shared, pthread_mutex_t *forks)
{
	unsigned int	i;
	t_philo			*philo;

	i = 0;
	while (i < args->num_of_philos)
	{
		philo = &philos[i];
		philo->id = i;
		philo->args = *args;
		philo->shared = shared;
		set_two_forks(philo, i, forks, args->num_of_philos);
		philo->start_time_of_philo = 0;
		philo->start_time_of_cycle = 0;
		philo->eat_count = 0;
		philo->is_self_dead = false;
		philo->current_time = get_current_time_usec();
		i++;
	}
}

t_philo	*init_philos(t_args *args, t_shared *shared, pthread_mutex_t **forks)
{
	t_philo	*philos;

	if (init_shared(shared) == FAILURE)
		return (NULL);
	if (init_forks(forks, args->num_of_philos) == FAILURE)
	{
		destroy_mutex(shared, NULL, 0);
		return (NULL);
	}
	philos = (t_philo *)malloc(sizeof(t_philo) * args->num_of_philos);
	if (philos == NULL)
	{
		destroy_mutex(shared, forks, args->num_of_philos);
		return (NULL);
	}
	set_philos(philos, args, shared, *forks);
	return (philos);
}
