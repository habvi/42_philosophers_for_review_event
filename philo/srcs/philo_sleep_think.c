#include "philo.h"

static int64_t	put_log_sleeping(t_philo *philo)
{
	return (put_log_flow(philo, get_elapsed_time, MSG_SLEEP));
}

void	sleeping(t_philo *philo)
{
	const unsigned int	time_to_sleep = philo->args->time_to_sleep;

	philo_action(philo, put_log_sleeping);
	usleep_gradual(time_to_sleep, philo);
}

static int64_t	put_log_thinking(t_philo *philo)
{
	return (put_log_flow(philo, get_elapsed_time, MSG_THINK));
}

void	thinking(t_philo *philo)
{
	philo_action(philo, put_log_thinking);
}
