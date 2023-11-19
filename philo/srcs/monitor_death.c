#include "ft_deque.h"
#include "philo.h"
#include "utils.h"

static t_result	create_each_monitor_thread(t_deque *threads, t_philo *philo)
{
	pthread_t	new_thread;

	if (pthread_create(&new_thread, NULL, monitor_cycle, (void *)philo) \
															!= THREAD_SUCCESS)
		return (FAILURE);
	if (add_threads_list(threads, new_thread) == FAILURE)
		return (FAILURE);
	return (SUCCESS);
}

static int64_t	set_thread_error(t_shared *shared)
{
	shared->is_thread_error = true;
	return (SUCCESS);
}

static t_result	create_monitor_thread(t_deque *threads, t_philo *philos, \
							t_shared *shared, const unsigned int num_of_philos)
{
	unsigned int	i;

	i = 0;
	while (i < num_of_philos)
	{
		if (create_each_monitor_thread(threads, &philos[i]) == FAILURE)
		{
			call_atomic(&shared->shared, set_thread_error, shared);
			return (FAILURE);
		}
		i++;
	}
	return (SUCCESS);
}

t_result	monitoring_death(\
			t_philo *philos, t_shared *shared, const unsigned int num_of_philos)
{
	t_deque		*threads;
	t_result	result;

	threads = deque_new();
	if (threads == NULL)
	{
		call_atomic(&shared->shared, set_thread_error, shared);
		destroy_shared(shared, num_of_philos);
		return (FAILURE);
	}
	result = create_monitor_thread(threads, philos, shared, num_of_philos);
	if (result == FAILURE)
		destroy_shared(shared, num_of_philos);
	destroy_threads(&threads);
	return (result);
}
