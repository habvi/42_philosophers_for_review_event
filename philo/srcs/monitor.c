#include "philo.h"
#include "utils.h"
#include <unistd.h> // usleep

// todo: before eating
static bool	is_time_to_die_exceeded(const t_args *args, const t_philo *philo)
{
	const long	elapsed_cycle_time = get_elapsed_cycle_time(philo);

	return (elapsed_cycle_time > args->time_to_die);
}

static t_result	set_philo_died(t_args *args, const t_philo *philo)
{
	pthread_mutex_t	*for_death;

	for_death = &args->for_death;
	if (pthread_mutex_lock(for_death) != MUTEX_SUCCESS)
		return (FAILURE);
	args->is_any_philo_died = true;
	put_log(philo, MSG_DIED);
	put(philo, "-----");
	if (pthread_mutex_unlock(for_death) != MUTEX_SUCCESS)
		return (FAILURE);
	return (SUCCESS);
}

static void	*monitor_cycle(void *thread_args)
{
	t_monitor		*monitor;
	int				i;
	t_args			*args;
	t_philo			*philo;

	monitor = (t_monitor *)thread_args;
	i = monitor->id;
	args = monitor->args;
	philo = args->philos[i];
	while (!is_any_philo_died(philo))
	{
		if (!is_time_to_die_exceeded(args, philo))
		{
			usleep(100);
			continue ;
		}
		if (set_philo_died(args, philo) == FAILURE)
		{
			ft_free((void **)&monitor);
			return (NULL); // todo
		}
		break ;
	}
	ft_free((void **)&monitor);
	return (NULL);
}

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

static t_result	create_each_monitor_thread(pthread_t *thread, const int i, t_args *args)
{
	t_monitor	*monitor;

	monitor = set_monitor_info(i, args);
	if (monitor == NULL)
		return (FAILURE);
	if (pthread_create(thread, NULL, monitor_cycle, (void *)monitor) != THREAD_SUCCESS)
		return (FAILURE);
	return (SUCCESS);
}

pthread_t	*monitor_death(t_args *args)
{
	pthread_t	*monitors;
	int			i;

	monitors = (pthread_t *)malloc(sizeof(pthread_t) * args->num_of_philos);
	if (monitors == NULL)
		return (NULL);
	i = 0;
	while (i < args->num_of_philos)
	{
		if (create_each_monitor_thread(&monitors[i], i, args) == FAILURE)
		{
			ft_free((void **)&monitors);
			return (NULL);
		}
		i++;
	}
	return (monitors);
}
