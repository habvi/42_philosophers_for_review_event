#include "philo.h"
#include "utils.h"

// todo: erase conditional branching 
// left: smaller number, right: larger number
static void	set_two_forks(\
					t_philo *philo, const unsigned int i, const t_args *args)
{
	if (args->num_of_philos == 1)
	{
		philo->left_fork = &args->forks[i];
		philo->right_fork = &args->forks[i];
		return ;
	}
	if (i + 1 < args->num_of_philos)
	{
		philo->left_fork = &args->forks[i];
		philo->right_fork = &args->forks[i + 1];
	}
	else
	{
		philo->left_fork = &args->forks[0];
		philo->right_fork = &args->forks[args->num_of_philos - 1];
	}
}

static t_philo	*set_philo_info(const unsigned int i, t_args *args)
{
	t_philo	*philo;

	philo = &args->philos[i];
	philo->id = i;
	philo->args = args;
	set_two_forks(philo, i, args);
	set_start_time_of_cycle(philo);
	philo->eat_count = 0;
	philo->is_self_dead = false;
	return (philo);
}

static t_result	create_each_philo_thread(\
						pthread_t *thread, const unsigned int i, t_args *args)
{
	t_philo	*philo;

	philo = set_philo_info(i, args);
	if (args->num_of_philos == 1)
	{
		if (pthread_create(thread, NULL, philo_solo_cycle, (void *)philo) \
															!= THREAD_SUCCESS)
			return (FAILURE);
	}
	else
	{
		if (pthread_create(thread, NULL, philo_cycle, (void *)philo) \
															!= THREAD_SUCCESS)
			return (FAILURE);
	}
	return (SUCCESS);
}

// simulation begins after all threads craeted.
static pthread_t	*simulate_philos_cycle_inter(t_args *args)
{
	pthread_t		*threads;
	unsigned int	i;

	threads = (pthread_t *)malloc(sizeof(pthread_t) * args->num_of_philos);
	if (threads == NULL)
		return (NULL);
	pthread_mutex_lock(&args->shared);
	i = 0;
	while (i < args->num_of_philos)
	{
		if (create_each_philo_thread(&threads[i], i, args) == FAILURE)
		{
			pthread_mutex_unlock(&args->shared);
			destroy_philos(args, &threads, i);
			return (NULL);
		}
		i++;
	}
	pthread_mutex_unlock(&args->shared);
	return (threads);
}

pthread_t	*simulate_philos_cycle(t_args *args)
{
	pthread_t	*threads;

	threads = simulate_philos_cycle_inter(args);
	if (threads == NULL)
	{
		args->is_thread_error = true;
		destroy_args(args);
		return (NULL);
	}
	return (threads);
}
