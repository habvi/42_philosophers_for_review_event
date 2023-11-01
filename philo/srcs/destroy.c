#include "philo.h"
#include "utils.h"

// Wait all threads, even if any one of them an error.
static void	wait_threads(const t_args *args, pthread_t *philos, pthread_t *monitors)
{
	int	i;

	i = 0;
	while (i < args->num_of_philos)
	{
		pthread_join(philos[i], NULL);
		pthread_join(monitors[i], NULL);
		i++;
	}
}

static void	destroy_philos(t_args *args)
{
	int	i;

	i = 0;
	while (i < args->num_of_philos)
	{
		pthread_mutex_destroy(&args->philos[i]->var->for_start_time);
		ft_free((void **)&args->philos[i]->var);
		ft_free((void **)&args->philos[i]);
		i++;
	}
	ft_free((void **)&args->philos);
}

void	destroy_forks(t_args *args)
{
	int	i;

	i = 0;
	while (i < args->num_of_philos)
	{
		pthread_mutex_destroy(&args->forks[i]);
		i++;
	}
	ft_free((void **)&args->forks);
}

static void	destroy_mutex(t_args *args)
{
	destroy_forks(args);
	pthread_mutex_destroy(&args->for_log);
	pthread_mutex_destroy(&args->for_death);
	pthread_mutex_destroy(&args->start_cycle);
}

void	destroy(t_args *args, pthread_t **threads, pthread_t **monitors)
{
	wait_threads(args, *threads, *monitors);
	ft_free((void **)threads);
	ft_free((void **)monitors);
	destroy_philos(args);
	destroy_mutex(args);
}
