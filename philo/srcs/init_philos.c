#include "philo.h"
#include "utils.h"

static t_result	init_shared(t_shared *shared)
{
	ft_bzero((void *)shared, sizeof(*shared));
	if (pthread_mutex_init(&shared->shared, NULL) != MUTEX_SUCCESS)
		return (FAILURE);
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
						t_rule *rule, t_shared *shared, pthread_mutex_t *forks)
{
	unsigned int	i;
	t_philo			*philo;

	i = 0;
	while (i < rule->num_of_philos)
	{
		philo = &philos[i];
		philo->id = i;
		philo->rule = *rule;
		philo->shared = shared;
		set_two_forks(philo, i, forks, rule->num_of_philos);
		i++;
	}
}

t_philo	*init_philos(t_rule *rule, t_shared *shared, pthread_mutex_t **forks)
{
	t_philo	*philos;

	if (init_shared(shared) == FAILURE)
		return (NULL);
	if (init_forks(forks, rule->num_of_philos) == FAILURE)
	{
		destroy_mutex(shared, NULL, 0);
		return (NULL);
	}
	philos = (t_philo *)ft_calloc(rule->num_of_philos, sizeof(t_philo));
	if (philos == NULL)
	{
		destroy_mutex(shared, forks, rule->num_of_philos);
		return (NULL);
	}
	set_philos(philos, rule, shared, *forks);
	return (philos);
}
