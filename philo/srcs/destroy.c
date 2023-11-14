#include "philo.h"
#include "utils.h"

// continue waiting even if one of join an error.
static void	wait_threads(\
			const t_args *args, pthread_t *threads, const unsigned int max_len)
{
	unsigned int	i;

	if (threads == NULL)
		return ;
	i = 0;
	while (i < args->num_of_philos && i < max_len)
	{
		pthread_join(threads[i], NULL);
		i++;
	}
}

void	destroy_threads(\
				t_args *args, pthread_t **threads, const unsigned int max_len)
{
	wait_threads(args, *threads, max_len);
	ft_free((void **)threads);
}

void	destroy_args(t_args *args)
{
	ft_free((void **)&args->philos);
	destroy_mutex(args);
}

void	destroy(t_args *args, \
		pthread_t **philos, pthread_t **monitors, const unsigned int max_len)
{
	destroy_threads(args, philos, max_len);
	destroy_threads(args, monitors, max_len);
	destroy_args(args);
}
