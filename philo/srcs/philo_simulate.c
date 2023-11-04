#include "philo.h"
#include "utils.h"

// left: smaller number, right: larger number
static void	set_two_forks(\
					t_philo *philo, const unsigned int i, const t_args *args)
{
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

static t_philo_var	*init_philo_var(void)
{
	t_philo_var	*var;

	var = (t_philo_var *)malloc(sizeof(t_philo_var) * 1);
	if (var == NULL)
		return (NULL);
	if (pthread_mutex_init(&var->for_start_time, NULL) != MUTEX_SUCCESS)
	{
		ft_free((void **)&var);
		return (NULL);
	}
	set_start_time_of_cycle(var);
	return (var);
}

static t_philo	*set_philo_info(const unsigned int i, t_args *args)
{
	t_philo	*philo;

	philo = (t_philo *)malloc(sizeof(t_philo) * 1);
	if (philo == NULL)
		return (NULL);
	philo->id = i;
	philo->args = args;
	set_two_forks(philo, i, args);
	philo->var = init_philo_var();
	if (philo->var == NULL)
	{
		ft_free((void **)&philo);
		return (NULL);
	}
	return (philo);
}

static t_result	create_each_philo_thread(\
						pthread_t *thread, const unsigned int i, t_args *args)
{
	t_philo	*philo;

	philo = set_philo_info(i, args);
	if (philo == NULL)
	{
		args->philos[i] = NULL;
		return (FAILURE);
	}
	if (pthread_create(thread, NULL, philo_cycle, (void *)philo) \
															!= THREAD_SUCCESS)
	{
		ft_free((void **)&philo);
		args->philos[i] = NULL;
		return (FAILURE);
	}
	args->philos[i] = philo;
	return (SUCCESS);
}

// simulation begins after all threads craeted. controlled by start_cycle mutex.
pthread_t	*simulate_philos_cycle(t_args *args)
{
	pthread_t		*threads;
	unsigned int	i;

	threads = (pthread_t *)malloc(sizeof(pthread_t) * args->num_of_philos);
	if (threads == NULL)
		return (NULL);
	pthread_mutex_lock(&args->start_cycle);
	i = 0;
	while (i < args->num_of_philos)
	{
		if (create_each_philo_thread(&threads[i], i, args) == FAILURE)
		{
			args->is_error = true;
			pthread_mutex_unlock(&args->start_cycle);
			destroy(args, &threads, NULL, 0);
			return (NULL);
		}
		i++;
	}
	pthread_mutex_unlock(&args->start_cycle);
	return (threads);
}
