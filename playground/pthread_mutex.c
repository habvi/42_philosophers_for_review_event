#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define THREAD_SUCCESS	0
#define THREAD_FAILURE	1
#define NUM_THREADS		3

int				g_shared_num = 0;
pthread_mutex_t	mutex;

int	init_mutexes(void)
{
	size_t	i;

	i = 0;
	while (i < NUM_THREADS)
	{
		if (pthread_mutex_init(&mutex, NULL) != THREAD_SUCCESS)
		{
			perror("pthread_mutex_init");
			return (THREAD_FAILURE);
		}
		i++;
	}
	return (THREAD_SUCCESS);
}

void	*thread_func(void *arg)
{
	size_t	i;

	i = 0;
	while (i < 100000)
	{
		pthread_mutex_lock(&mutex);
		g_shared_num++;
		pthread_mutex_unlock(&mutex);
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

	if (init_mutexes() != THREAD_SUCCESS)
		exit(EXIT_FAILURE);
	if (create_threads(threads) != THREAD_SUCCESS)
		exit(EXIT_FAILURE);
	if (join_threads(threads) != THREAD_SUCCESS)
		exit(EXIT_FAILURE);
	pthread_mutex_destroy(&mutex);
	printf("all threads done! shared_num... [%d]\n", g_shared_num);
	return (EXIT_SUCCESS);
}
