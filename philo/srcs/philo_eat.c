#include "philo.h"
#include "utils.h"

static void	set_start_cycle_time(t_philo *philo, const int64_t current_time)
{
	philo->start_time_of_cycle = current_time;
}

// The required philo->current_time within put_log() is
// set inside is_simulation_over(), thus preserving the order.
static int64_t	put_log_eating(t_philo *philo)
{
	if (is_simulation_over(philo))
		return (FAILURE);
	set_start_cycle_time(philo, philo->current_time);
	put_log(philo, MSG_EAT);
	return (SUCCESS);
}

static int64_t	count_eat_times(t_philo *philo)
{
	const unsigned int	must_eat = \
						(unsigned int)philo->rule.num_of_each_philo_must_eat;

	philo->eat_count++;
	if (philo->eat_count == must_eat)
		philo->shared->num_of_finish_eat++;
	return (SUCCESS);
}

void	eating(t_philo *philo)
{
	const int64_t	time_to_eat = philo->rule.time_to_eat;
	const int64_t	must_eat = philo->rule.num_of_each_philo_must_eat;
	pthread_mutex_t	*shared;

	if (is_simulation_over_atomic(philo))
		return ;
	shared = &philo->shared->shared;
	if (call_atomic(shared, put_log_eating, philo) == FAILURE)
		return ;
	usleep_gradual(time_to_eat, philo);
	if (must_eat != NOT_SET)
		call_atomic(shared, count_eat_times, philo);
}
