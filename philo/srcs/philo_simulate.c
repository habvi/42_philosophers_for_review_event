#include "ft_deque.h"
#include "philo.h"
#include "utils.h"

// even: take left_fork -> right_fork
// odd: take right_fork -> left_fork
static void	set_two_forks(t_philo *philo, \
						const unsigned int i, const unsigned int num_of_philos)
{
	if (num_of_philos == 1)
	{
		philo->fork1 = &philo->shared->forks[i];
		philo->fork2 = &philo->shared->forks[i];
		return ;
	}
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

static t_philo	*set_philo_info(\
						const unsigned int i, t_args *args, t_shared *shared)
{
	t_philo			*philo;
	const int64_t	current_time = get_current_time_usec();

	philo = &args->philos[i];
	philo->id = i;
	philo->args = *args;
	philo->shared = shared;
	set_two_forks(philo, i, args->num_of_philos);
	philo->start_time_of_cycle = current_time;
	philo->eat_count = 0;
	philo->is_self_dead = false;
	philo->current_time = current_time;
	return (philo);
}

static t_result	create_each_philo_thread(t_deque *threads, \
						const unsigned int i, t_args *args, t_shared *shared)
{
	t_philo		*philo;
	pthread_t	new_thread;

	philo = set_philo_info(i, args, shared);
	if (args->num_of_philos == 1)
	{
		if (pthread_create(&new_thread, NULL, philo_solo_cycle, (void *)philo) \
															!= THREAD_SUCCESS)
			return (FAILURE);
	}
	else
	{
		if (pthread_create(&new_thread, NULL, philo_cycle, (void *)philo) \
															!= THREAD_SUCCESS)
			return (FAILURE);
	}
	if (add_threads_list(threads, new_thread) == FAILURE)
		return (FAILURE);
	return (SUCCESS);
}

// simulation begins after all threads craeted.
static t_result	create_philo_thread(\
								t_deque *philos, t_args *args, t_shared *shared)
{
	unsigned int	i;

	pthread_mutex_lock(&shared->shared);
	i = 0;
	while (i < args->num_of_philos)
	{
		if (create_each_philo_thread(philos, i, args, shared) == FAILURE)
		{
			shared->is_thread_error = true;
			pthread_mutex_unlock(&shared->shared);
			destroy_threads(&philos);
			return (FAILURE);
		}
		i++;
	}
	pthread_mutex_unlock(&shared->shared);
	return (SUCCESS);
}

t_deque	*simulate_philos_cycle(t_args *args, t_shared *shared)
{
	t_deque	*threads;

	threads = deque_new();
	if (threads == NULL)
	{
		shared->is_thread_error = true;
		return (NULL);
	}
	if (create_philo_thread(threads, args, shared) == FAILURE)
	{
		destroy_args(args);
		destroy_shared(args, shared);
		return (NULL);
	}
	return (threads);
}
