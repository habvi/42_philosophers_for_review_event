#include "philo.h"
#include "utils.h"

static void	set_philos(t_philo *philos, t_args *args)
{
	unsigned int	i;
	t_philo			*philo;

	i = 0;
	while (i < args->num_of_philos)
	{
		philo = &philos[i];
		philo->id = i;
		philo->args = *args;
		philo->shared = NULL;
		philo->fork1 = NULL;
		philo->fork2 = NULL;
		philo->start_time_of_philo = 0;
		philo->start_time_of_cycle = 0;
		philo->eat_count = 0;
		philo->is_self_dead = false;
		philo->current_time = get_current_time_usec();
		i++;
	}
}

t_philo	*init_philos(t_args *args)
{
	t_philo	*philos;

	philos = (t_philo *)malloc(sizeof(t_philo) * args->num_of_philos);
	if (philos == NULL)
		return (NULL);
	set_philos(philos, args);
	return (philos);
}
