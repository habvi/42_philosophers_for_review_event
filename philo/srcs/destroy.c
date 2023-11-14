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

void	destroy_args(t_args *args)
{
	ft_free((void **)&args->philos);
	destroy_mutex(args);
}

void	destroy(t_args *args, t_deque **philos, t_deque **monitors)
{
	destroy_threads(philos);
	destroy_threads(monitors);
	destroy_args(args);
}
