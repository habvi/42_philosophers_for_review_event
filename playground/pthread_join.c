#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

/*
int pthread_create(pthread_t * thread, \
					pthread_attr_t * attr, \
					void * (*start_routine)(void *), \
					void * arg)
int pthread_detach(pthread_t th);
int pthread_join(pthread_t th, void **thread_return);

int pthread_mutex_init(pthread_mutex_t *mutex, const pthread_mutexattr_t *mutexattr);
int pthread_mutex_destroy(pthread_mutex_t *mutex);
int pthread_mutex_lock(pthread_mutex_t *mutex));
int pthread_mutex_unlock(pthread_mutex_t *mutex);
*/

#define THREAD_SUCCESS	0

static void	*thread_func(void *arg)
{
	const char	*str = (const char *)arg;

	printf("in thread_func: %s", str);
	return ((void *)strlen(str));
}

int	main(void)
{
	pthread_t	thread;
	char		*str;
	void		*res;

	str = "aaa, hellohello.\n";
	// create thread
	if (pthread_create(&thread, NULL, thread_func, str) != THREAD_SUCCESS)
	{
		perror("pthread_create");
		exit(EXIT_FAILURE);
	}
	printf("from main~\n");
	// wait thread
	if (pthread_join(thread, &res) != THREAD_SUCCESS)
	{
		perror("pthread_join");
		exit(EXIT_FAILURE);
	}
	printf("thread returned strlen str: [%ld]\n", (long)res);
	return (EXIT_SUCCESS);
}
