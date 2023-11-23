#include "philo.h"

static int64_t	put_log_sleeping(t_philo *philo)
{
	return (put_log_flow(philo, NULL, MSG_SLEEP));
}

void	sleeping(t_philo *philo)
{
	const int64_t	time_to_sleep = philo->rule.time_to_sleep;

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
	const int64_t	time_to_think = philo->rule.time_to_think;

	if (philo_action(philo, put_log_thinking) == FAILURE)
		return ;
	usleep_gradual(time_to_think, philo);
}
