#include "philo.h"
#include "utils.h"

static void	set_start_cycle_time(t_philo *philo, const int64_t current_time)
{
	philo->start_time_of_cycle = current_time;
}

static int64_t	put_log_eating(t_philo *philo)
{
	return (put_log_flow(philo, set_start_cycle_time, MSG_EAT));
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
	const int64_t	time_to_eat = philo->args->time_to_eat;
	pthread_mutex_t	*shared;

	if (philo_action(philo, put_log_eating) == FAILURE)
		return ;
	usleep_gradual(time_to_eat, philo);
	shared = &philo->args->shared;
	call_atomic(shared, count_eat_times, philo);
}
