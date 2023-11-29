#include "ft_deque.h"
#include "philo.h"
#include "utils.h"

static t_result	create_each_philo_thread(t_deque *threads, t_philo *philo)
{
	pthread_t	new_thread;

	if (philo->rule.num_of_philos == 1)
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

t_result	create_each_monitor_thread(t_deque *threads, t_philo *philo)
{
	pthread_t	new_thread;

	if (pthread_create(&new_thread, NULL, monitor_cycle, (void *)philo) \
															!= THREAD_SUCCESS)
		return (FAILURE);
	if (add_threads_list(threads, new_thread) == FAILURE)
		return (FAILURE);
	return (SUCCESS);
}

static void	set_simulation_start_time(\
			t_shared *shared, t_philo *philos, const unsigned int num_of_philos)
{
	unsigned int	i;
	const int64_t	current_time = get_current_time_usec();

	shared->start_time = current_time;
	i = 0;
	while (i < num_of_philos)
	{
		philos[i].start_time_of_philo = current_time;
		philos[i].start_time_of_cycle = current_time;
		philos[i].current_time = current_time;
		i++;
	}
}

// simulation begins after all threads craeted.
static t_result	create_threads(t_deque *threads, t_shared *shared, \
							t_philo *philos, const unsigned int num_of_philos)
{
	unsigned int	i;

	i = 0;
	while (i < num_of_philos)
	{
		if (create_each_philo_thread(threads, &philos[i]) == FAILURE)
			return (FAILURE);
		if (create_each_monitor_thread(threads, &philos[i]) == FAILURE)
			return (FAILURE);
		i++;
	}
	set_simulation_start_time(shared, philos, num_of_philos);
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
		return (FAILURE);
	}
	pthread_mutex_lock(&shared->shared);
	result = create_threads(threads, shared, philos, num_of_philos);
	if (result == FAILURE)
		shared->is_thread_error = true;
	pthread_mutex_unlock(&shared->shared);
	destroy_threads(&threads);
	return (result);
}
