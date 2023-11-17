#include "ft_deque.h"
#include "philo.h"
#include "utils.h"

// free monitor in monitor_cycle's last
static t_monitor	*set_monitor_info(\
						const unsigned int i, t_args *args, t_shared *shared)
{
	t_monitor	*monitor;

	monitor = (t_monitor *)malloc(sizeof(t_monitor) * 1);
	if (monitor == NULL)
		return (NULL);
	monitor->id = i;
	monitor->args = *args;
	monitor->shared = shared;
	return (monitor);
}

static t_result	create_each_monitor_thread(t_deque *threads, \
						const unsigned int i, t_args *args, t_shared *shared)
{
	t_monitor	*monitor;
	pthread_t	new_thread;

	monitor = set_monitor_info(i, args, shared);
	if (monitor == NULL)
		return (FAILURE);
	if (pthread_create(&new_thread, NULL, monitor_cycle, (void *)monitor) \
															!= THREAD_SUCCESS)
	{
		ft_free((void **)&monitor);
		return (FAILURE);
	}
	if (add_threads_list(threads, new_thread) == FAILURE)
	{
		ft_free((void **)&monitor);
		return (FAILURE);
	}
	return (SUCCESS);
}

static int64_t	set_thread_error(t_shared *shared)
{
	shared->is_thread_error = true;
	return (SUCCESS);
}

static t_result	create_monitor_thread(\
							t_deque *monitors, t_args *args, t_shared *shared)
{
	unsigned int	i;

	i = 0;
	while (i < args->num_of_philos)
	{
		if (create_each_monitor_thread(monitors, i, args, shared) == FAILURE)
		{
			call_atomic(&shared->shared, set_thread_error, shared);
			destroy_threads(&monitors);
			return (FAILURE);
		}
		i++;
	}
	return (SUCCESS);
}

t_deque	*monitoring_death(\
						t_args *args, t_shared *shared, t_deque **philo_threads)
{
	t_deque	*threads;

	threads = deque_new();
	if (threads == NULL)
	{
		call_atomic(&shared->shared, set_thread_error, shared);
		return (NULL);
	}
	if (create_monitor_thread(threads, args, shared) == FAILURE)
	{
		destroy_threads(philo_threads);
		return (NULL);
	}
	return (threads);
}
