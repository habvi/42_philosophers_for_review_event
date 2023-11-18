#include "ft_deque.h"
#include "philo.h"
#include "utils.h"

static t_result	create_each_philo_thread(t_deque *threads, t_philo *philo)
{
	pthread_t	new_thread;

	if (philo->args.num_of_philos == 1)
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
static t_result	create_philo_thread(t_deque *threads, t_shared *shared, \
							t_philo *philos, const unsigned int num_of_philos)
{
	unsigned int	i;

	pthread_mutex_lock(&shared->shared);
	i = 0;
	while (i < num_of_philos)
	{
		if (create_each_philo_thread(threads, &philos[i]) == FAILURE)
		{
			shared->is_thread_error = true;
			pthread_mutex_unlock(&shared->shared);
			return (FAILURE);
		}
		i++;
	}
	pthread_mutex_unlock(&shared->shared);
	return (SUCCESS);
}

t_result	simulate_philos_cycle(\
			t_philo *philos, t_shared *shared, const unsigned int num_of_philos)
{
	t_deque		*threads;
	t_result	result;

	threads = deque_new();
	if (threads == NULL)
	{
		shared->is_thread_error = true;
		destroy_shared(shared, num_of_philos);
		return (FAILURE);
	}
	result = create_philo_thread(threads, shared, philos, num_of_philos);
	if (result == FAILURE)
		destroy_shared(shared, num_of_philos);
	destroy_threads(&threads);
	return (result);
}
