#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define THREAD_SUCCESS	0

void	*thread_func(void *arg)
{
	const int	thread_id = *(int *)arg;

	printf("%d start\n", thread_id);
	usleep(5000);
	printf("%d end\n", thread_id);
	return (NULL);
}

int	main(void)
{
	pthread_t	thread1;
	pthread_t	thread2;
	int			thread_id1;
	int			thread_id2;

	thread_id1 = 1;
	thread_id2 = 2;
	// create initial/main thread
	if (pthread_create(&thread1, NULL, thread_func, &thread_id1) != THREAD_SUCCESS)
	{
		perror("pthread_create");
		exit(EXIT_FAILURE);
	}
	// create 2nd thread
	if (pthread_create(&thread2, NULL, thread_func, &thread_id2) != THREAD_SUCCESS)
	{
		perror("pthread_create");
		exit(EXIT_FAILURE);
	}
	// wait both threads end
	if (pthread_join(thread1, NULL) != THREAD_SUCCESS)
	{
		perror("pthread_join");
		exit(EXIT_FAILURE);
	}
	if (pthread_join(thread2, NULL) != THREAD_SUCCESS)
	{
		perror("pthread_join");
		exit(EXIT_FAILURE);
	}
	printf("all threads done!\n");
	return (EXIT_SUCCESS);
}
