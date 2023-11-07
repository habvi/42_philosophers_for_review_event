#include "philo.h"

static int64_t	set_and_get_elapsed_time(t_philo *philo)
{
	const int64_t	start_time = philo->args->start_time;
	int64_t			current_time;
	int64_t			elapsed_time;

	set_start_time_of_cycle(philo);
	current_time = philo->start_time_of_cycle;
	elapsed_time = current_time - start_time;
	return (elapsed_time);
}

static int64_t	put_log_eating(t_philo *philo)
{
	return (put_log_flow(philo, set_and_get_elapsed_time, MSG_EAT));
}

static int64_t	count_eat_times(t_philo *philo)
{
	const unsigned int	must_eat = philo->args->num_of_each_philo_must_eat;

	philo->eat_count++;
	if (philo->eat_count == must_eat)
		philo->args->num_of_finish_eat++;
	return (SUCCESS);
}

void	eating(t_philo *philo)
{
	const unsigned int	time_to_eat = philo->args->time_to_eat;
	pthread_mutex_t		*shared;

	philo_action(philo, put_log_eating);
	usleep_gradual(time_to_eat, philo);
	shared = &philo->args->shared;
	call_atomic(shared, count_eat_times, philo);
}
