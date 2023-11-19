#include "ft_deque.h"
#include "philo.h"
#include "utils.h"

t_result	add_threads_list(t_deque *threads, pthread_t new_thread)
{
	t_deque_node	*node;

	node = create_thread_node(new_thread);
	if (node == NULL)
		return (FAILURE);
	deque_add_back(threads, node);
	return (SUCCESS);
}

t_deque_node	*create_thread_node(pthread_t new_thread)
{
	pthread_t		*thread;
	t_deque_node	*node;

	thread = (pthread_t *)malloc(sizeof(pthread_t) * 1);
	if (thread == NULL)
		return (NULL);
	*thread = new_thread;
	node = deque_node_new((void *)thread);
	if (node == NULL)
	{
		ft_free((void **)&thread);
		return (NULL);
	}
	return (node);
}

static int64_t	get_error(t_philo *philo)
{
	return (philo->shared->is_thread_error);
}

bool	wait_start(t_philo *philo)
{
	pthread_mutex_t	*shared;

	shared = &philo->shared->shared;
	return (call_atomic(shared, get_error, philo));
}
