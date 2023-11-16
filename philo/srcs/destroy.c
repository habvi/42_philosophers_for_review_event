#include "ft_deque.h"
#include "philo.h"
#include "utils.h"

static void	del_node(void *content)
{
	ft_free(&content);
}

// continue waiting even if one of join an error.
void	destroy_threads(t_deque **threads)
{
	t_deque_node	*node;
	pthread_t		*thread;

	if (threads == NULL)
		return ;
	while (!deque_is_empty(*threads))
	{
		node = deque_pop_front(*threads);
		thread = (pthread_t *)node->content;
		pthread_join(*thread, NULL);
		deque_clear_node(&node, del_node);
	}
	deque_clear_all(threads, del_node);
}

void	destroy_shared(const t_args *args, t_shared *shared)
{
	destroy_forks(&shared->forks, args->num_of_philos);
	pthread_mutex_destroy(&shared->shared);
}

void	destroy_args(const t_args *args)
{
	ft_free((void **)&args->philos);
}

void	destroy(const t_args *args, t_shared *shared, \
										t_deque **philos, t_deque **monitors)
{
	destroy_threads(philos);
	destroy_threads(monitors);
	destroy_shared(args, shared);
	destroy_args(args);
}
