#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define THREAD_SUCCESS	0
#define THREAD_FAILURE	1
#define NUM_THREADS		5

int	g_shared_num = 0;

void	*thread_func(void *arg)
{
	size_t	i;

	i = 0;
	while (i < 100000)
	{
		g_shared_num++;
		i++;
	}
	return (NULL);
}

int	create_threads(pthread_t *threads)
{
	size_t	i;

	i = 0;
	while (i < NUM_THREADS)
	{
		if (pthread_create(&threads[i], NULL, thread_func, NULL) != THREAD_SUCCESS)
		{
			perror("pthread_create");
			return (THREAD_FAILURE);
		}
		i++;
	}
	return (THREAD_SUCCESS);
}

int	join_threads(pthread_t *threads)
{
	size_t	i;

	i = 0;
	while (i < NUM_THREADS)
	{
		if (pthread_join(threads[i], NULL) != THREAD_SUCCESS)
		{
			perror("pthread_join");
			return (THREAD_FAILURE);
		}
		i++;
	}
	return (THREAD_SUCCESS);
}

int	main(void)
{
	pthread_t	threads[NUM_THREADS];

	if (create_threads(threads) != THREAD_SUCCESS)
		exit(EXIT_FAILURE);
	if (join_threads(threads) != THREAD_SUCCESS)
		exit(EXIT_FAILURE);
	printf("all threads done! shared_num... [%d]\n", g_shared_num);
	return (EXIT_SUCCESS);
}
