#include <stdio.h>
#include <unistd.h> // usleep
#include "philo.h"
#include "utils.h"

static bool	is_within_time_to_die(const t_philo *philo)
{
	const long	start_time = philo->args->start_time;
	const long	current_time = get_current_time();
	const long	elapsed_time = current_time - start_time;

	return (elapsed_time < philo->args->time_to_die);
}

static void	*philo_cycle(void *thread_args)
{
	t_philo	*philo;

	philo = (t_philo *)thread_args;
	// todo: temp
	while (is_within_time_to_die(philo))
	{
		// todo: error(free)
		eating(philo);
		sleeping(philo);
		thinking(philo);
	}
	free(philo);
	return (NULL);
}

static t_philo	*set_thread_info(int i, t_args *args)
{
	t_philo	*philo;

	philo = (t_philo *)malloc(sizeof(t_philo) * 1);
	// todo: error
	if (philo == NULL)
		return (NULL);
	philo->id = i;
	philo->args = args;
	return (philo);
}

// todo: exit -> return error
pthread_t	*create_threads(t_args *args)
{
	pthread_t	*threads;
	int			i;
	t_philo		*philo;

	threads = (pthread_t *)malloc(sizeof(pthread_t) * args->number_of_philos);
	if (threads == NULL)
		return (NULL);
	i = 0;
	while (i < args->number_of_philos)
	{
		philo = set_thread_info(i, args);
		if (pthread_create(&threads[i], NULL, philo_cycle, (void *)philo) != THREAD_SUCCESS)
		{
			perror("pthread_create");
			exit(EXIT_FAILURE);
		}
		i++;
	}
	return (threads);
}
