#include "philo.h"

void	eating(const t_philo *philo)
{
	const unsigned int	time_to_eat = philo->args->time_to_eat;

	if (take_two_forks(philo) == BREAK)
		return ;
	// todo: use philo->var->start_time_of_cycle for put_log
	set_start_time_of_cycle(philo->var);
	put_log(philo, MSG_EAT);
	usleep_gradual(time_to_eat, philo);

	put_two_forks(philo);
}

void	sleeping(const t_philo *philo)
{
	const unsigned int	time_to_sleep = philo->args->time_to_sleep;

	put_log(philo, MSG_SLEEP);
	usleep_gradual(time_to_sleep, philo);
}

void	thinking(const t_philo *philo)
{
	put_log(philo, MSG_THINK);
}
