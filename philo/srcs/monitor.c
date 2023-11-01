#include "philo.h"
#include "utils.h"

// free monitor in monitor_cycle's last
static t_monitor	*set_monitor_info(const int i, t_args *args)
{
	t_monitor	*monitor;

	monitor = (t_monitor *)malloc(sizeof(t_monitor) * 1);
	if (monitor == NULL)
		return (NULL);
	monitor->id = i;
	monitor->args = args;
	return (monitor);
}

static t_result	create_each_monitor_thread(\
								pthread_t *thread, const int i, t_args *args)
{
	t_monitor	*monitor;

	monitor = set_monitor_info(i, args);
	if (monitor == NULL)
		return (FAILURE);
	if (pthread_create(thread, NULL, monitor_cycle, (void *)monitor) \
															!= THREAD_SUCCESS)
	{
		ft_free((void **)&monitor);
		return (FAILURE);
	}
	return (SUCCESS);
}

pthread_t	*monitoring_death(t_args *args, pthread_t **philo_threads)
{
	pthread_t	*monitors;
	int			i;

	monitors = (pthread_t *)malloc(sizeof(pthread_t) * args->num_of_philos);
	if (monitors == NULL)
	{
		destroy(args, philo_threads, NULL, 0);
		return (NULL);
	}
	i = 0;
	while (i < args->num_of_philos)
	{
		if (create_each_monitor_thread(&monitors[i], i, args) == FAILURE)
		{
			args->is_error = true;
			destroy(args, philo_threads, &monitors, i);
			return (NULL);
		}
		i++;
	}
	return (monitors);
}
