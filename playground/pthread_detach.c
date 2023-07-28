#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define THREAD_SUCCESS	0

void	*thread_func(void *arg)
{
	const int	thread_id = *(int *)arg;

	printf("%d start\n", thread_id);
	usleep(50000);
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
	if (pthread_create(&thread1, NULL, thread_func, &thread_id1) != THREAD_SUCCESS)
	{
		perror("pthread_create");
		exit(EXIT_FAILURE);
	}
	if (pthread_create(&thread2, NULL, thread_func, &thread_id2) != THREAD_SUCCESS)
	{
		perror("pthread_create");
		exit(EXIT_FAILURE);
	}
	if (pthread_detach(thread1) != THREAD_SUCCESS)
	{
		perror("pthread_detach");
		exit(EXIT_FAILURE);
	}
	if (pthread_detach(thread2) != THREAD_SUCCESS)
	{
		perror("pthread_detach");
		exit(EXIT_FAILURE);
	}
	printf("main thread is continueing\n");
	usleep(80000);
	printf("main thread is done!\n");
	return (EXIT_SUCCESS);
}
