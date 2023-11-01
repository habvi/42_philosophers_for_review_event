#include "philo.h"

void	eating(const t_philo *philo)
{
	const int	time_to_eat = philo->args->time_to_eat;
	t_result	result;

	result = take_two_forks(philo);
	if (result == BREAK)
		return ;

	// unneccessary?
	if (is_any_philo_died(philo))
	{
		put_two_forks(philo);
		return ;
	}
	// todo: use philo->var->start_time_of_cycle for put_log
	set_start_time_of_cycle(philo->var);
	put_log(philo, MSG_EAT);
	usleep_gradual(time_to_eat, philo);

	put_two_forks(philo);
}

void	sleeping(const t_philo *philo)
{
	const int	time_to_sleep = philo->args->time_to_sleep;

	put_log(philo, MSG_SLEEP);
	usleep_gradual(time_to_sleep, philo);
}

void	thinking(const t_philo *philo)
{
	put_log(philo, MSG_THINK);
}
