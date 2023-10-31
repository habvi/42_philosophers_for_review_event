#include "philo.h"
#include "utils.h"

// todo: usleep, return t_result
t_result	eating(const t_philo *philo)
{
	const int	time_to_eat = philo->args->time_to_eat;
	t_result	result;

	result = take_two_forks(philo);
	if (result == FAILURE || result == BREAK)
		return (result);

	// unneccessary?
	if (is_any_philo_died(philo))
	{
		if (put_two_forks(philo) == FAILURE)
			return (FAILURE);
		return (BREAK);
	}
	set_start_time_of_cycle(philo->var); // todo: use philo->var->start_time_of_cycle for put_log
	put_log(philo, MSG_EAT);
	usleep_gradual(time_to_eat, philo);

	if (put_two_forks(philo) == FAILURE)
		return (FAILURE);
	return (SUCCESS);
}

// todo: usleep, return t_result
t_result	sleeping(const t_philo *philo)
{
	const int	time_to_sleep = philo->args->time_to_sleep;

	put_log(philo, MSG_SLEEP);
	usleep_gradual(time_to_sleep, philo);
	return (SUCCESS);
}

// todo: return t_result
t_result	thinking(const t_philo *philo)
{
	put_log(philo, MSG_THINK);
	return (SUCCESS);
}
