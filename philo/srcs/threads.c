#include <stdio.h>
#include "philo.h"

// Wait all threads, even if any one of them an error.
void	wait_threads(const t_args *args, pthread_t *threads)
{
	int	i;

	i = 0;
	while (i < args->num_of_philos)
	{
		if (pthread_join(threads[i], NULL) != THREAD_SUCCESS)
			perror("pthread_join");
		i++;
	}
}
