#include <unistd.h> // usleep
#include "philo.h"
#include "utils.h"

// left: smaller number, right: larger number
static void	set_two_forks(t_philo *philo, const int i, const t_args *args)
{
	if (i + 1 < args->num_of_philos)
	{
		philo->left_fork = &args->forks[i];
		philo->right_fork = &args->forks[i + 1];
	}
	else
	{
		philo->left_fork = &args->forks[0];
		philo->right_fork = &args->forks[args->num_of_philos - 1];
	}
}

static t_philo_var	*init_philo_var(void)
{
	t_philo_var	*var;

	var = (t_philo_var *)malloc(sizeof(t_philo_var) * 1);
	if (var == NULL)
		return (NULL);
	// todo: error?
	var->start_time_of_cycle = get_current_time();
	return (var);
}

static t_philo	*set_thread_info(const int i, t_args *args)
{
	t_philo	*philo;

	philo = (t_philo *)malloc(sizeof(t_philo) * 1);
	if (philo == NULL)
		return (NULL);
	philo->id = i;
	philo->args = args;
	set_two_forks(philo, i, args);
	philo->var = init_philo_var();
	if (philo->var == NULL)
	{
		ft_free((void **)&philo);
		return (NULL);
	}
	return (philo);
}

static t_result	create_each_philo_thread(pthread_t *thread, const int i, t_args *args)
{
	t_philo	*philo;

	philo = set_thread_info(i, args);
	if (philo == NULL)
		return (FAILURE);
	if (pthread_create(thread, NULL, philo_cycle, (void *)philo) != THREAD_SUCCESS)
		return (FAILURE);
	args->philos[i] = philo;
	return (SUCCESS);
}

pthread_t	*create_threads(t_args *args)
{
	pthread_t	*threads;
	int			i;

	threads = (pthread_t *)malloc(sizeof(pthread_t) * args->num_of_philos);
	if (threads == NULL)
		return (NULL);
	i = 0;
	while (i < args->num_of_philos)
	{
		if (create_each_philo_thread(&threads[i], i, args) == FAILURE)
		{
			ft_free((void **)&threads);
			return (NULL);
		}
		i++;
	}
	return (threads);
}
