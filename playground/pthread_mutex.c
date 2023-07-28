#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define THREAD_SUCCESS	0
#define THREAD_FAILURE	1
#define NUM_THREADS		3
#define NUM_INCREMENT	100000

static int				g_shared_num = 0;
static pthread_mutex_t	mutex;

static int	init_mutexes(void)
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

static void	*thread_func(void *arg)
{
	size_t	i;

	i = 0;
	while (i < NUM_INCREMENT)
	{
		if (pthread_mutex_lock(&mutex) != THREAD_SUCCESS)
		{
			perror("pthread_mutex_lock");
			exit(EXIT_FAILURE);
		}
		g_shared_num++;
		if (pthread_mutex_unlock(&mutex) != THREAD_SUCCESS)
		{
			perror("pthread_mutex_unlock");
			exit(EXIT_FAILURE);
		}
		i++;
	}
	return (NULL);
}

static int	create_threads(pthread_t *threads)
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

static int	join_threads(pthread_t *threads)
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
