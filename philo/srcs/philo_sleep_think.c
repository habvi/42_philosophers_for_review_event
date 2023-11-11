#include "philo.h"

static int64_t	put_log_sleeping(t_philo *philo)
{
	return (put_log_flow(philo, NULL, MSG_SLEEP));
}

void	sleeping(t_philo *philo)
{
	const unsigned int	time_to_sleep = philo->args->time_to_sleep;

	if (philo_action(philo, put_log_sleeping) == FAILURE)
		return ;
	usleep_gradual(time_to_sleep, philo);
}

static int64_t	put_log_thinking(t_philo *philo)
{
	return (put_log_flow(philo, NULL, MSG_THINK));
}

void	thinking(t_philo *philo)
{
	philo_action(philo, put_log_thinking);
}
