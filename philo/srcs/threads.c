#include "philo.h"

// Wait all threads, even if any one of them an error.
void	wait_threads(const t_args *args, pthread_t *philos, pthread_t *monitors)
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
