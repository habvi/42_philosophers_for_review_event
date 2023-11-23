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

void	destroy_forks(pthread_mutex_t **forks, const unsigned int max_len)
{
	unsigned int	i;

	i = 0;
	while (i < max_len)
	{
		pthread_mutex_destroy(&(*forks)[i]);
		i++;
	}
	ft_free((void **)forks);
}

void	destroy_mutex(t_shared *shared, \
					pthread_mutex_t **forks, const unsigned int num_of_philos)
{
	pthread_mutex_destroy(&shared->shared);
	if (forks != NULL)
		destroy_forks(forks, num_of_philos);
}

void	destroy_philos(\
					t_philo **philos, t_shared *shared, pthread_mutex_t **forks)
{
	destroy_mutex(shared, forks, (*philos)->args.num_of_philos);
	ft_free((void **)philos);
}
