#include "philo.h"
#include "utils.h"

static void	destroy_philos(t_args *args)
{
	int	i;

	i = 0;
	while (i < args->num_of_philos)
	{
		ft_free((void **)&args->philos[i]->var);
		ft_free((void **)&args->philos[i]);
		i++;
	}
	ft_free((void **)&args->philos);
}

void	destroy(t_args *args, pthread_t **threads)
{
	ft_free((void **)threads);
	destroy_philos(args);
	destroy_mutex(args);
}
