#include "philo.h"
#include "utils.h"

// continue waiting even if one of join an error.
static void	wait_philo_threads(const t_args *args, pthread_t *threads)
{
	t_philo			**philos;
	unsigned int	i;

	if (threads == NULL)
		return ;
	philos = args->philos;
	i = 0;
	while (i < args->num_of_philos && philos[i])
	{
		pthread_join(threads[i], NULL);
		i++;
	}
}

// continue waiting even if one of join an error.
static void	wait_monitor_threads(\
			const t_args *args, pthread_t *threads, const unsigned int max_len)
{
	unsigned int	i;

	i = 0;
	while (i < args->num_of_philos && i < max_len)
	{
		pthread_join(threads[i], NULL);
		i++;
	}
}

static void	destroy_each_philos(t_args *args)
{
	t_philo			**philos;
	unsigned int	i;

	philos = args->philos;
	i = 0;
	while (i < args->num_of_philos && philos[i])
	{
		ft_free((void **)&philos[i]);
		i++;
	}
	ft_free((void **)&args->philos);
}

void	destroy_forks(pthread_mutex_t **forks, const unsigned int max_len)
{
	unsigned int	i;

	i = 0;
	while (i < max_len)
	{
		pthread_mutex_destroy(&(*forks)[i]);
		i++;
	}
	ft_free((void **)forks);
}

static void	destroy_mutex(t_args *args)
{
	destroy_forks(&args->forks, args->num_of_philos);
	pthread_mutex_destroy(&args->shared);
}

void	destroy(t_args *args, \
		pthread_t **philos, pthread_t **monitors, const unsigned int max_len)
{
	wait_philo_threads(args, *philos);
	wait_monitor_threads(args, *monitors, max_len);
	ft_free((void **)philos);
	ft_free((void **)monitors);
	destroy_each_philos(args);
	destroy_mutex(args);
}

void	destroy_all(t_args *args, pthread_t **philos, pthread_t **monitors)
{
	destroy(args, philos, monitors, args->num_of_philos);
}
