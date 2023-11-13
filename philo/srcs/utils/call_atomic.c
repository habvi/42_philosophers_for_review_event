#include <pthread.h>
#include <stdint.h>

int64_t	call_atomic(pthread_mutex_t *mutex, int64_t (*func)(), void *args)
{
	int64_t	ret;

	pthread_mutex_lock(mutex);
	ret = func(args);
	pthread_mutex_unlock(mutex);
	return (ret);
}
