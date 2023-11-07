#include "philo.h"

// only for eating.
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

static int64_t	print_log_eating(t_philo *philo)
{
	put_log(philo, MSG_EAT, set_and_get_elapsed_time);
	return (SUCCESS);
}

void	eating(t_philo *philo)
{
	const unsigned int	time_to_eat = philo->args->time_to_eat;

	philo_action(philo, print_log_eating);
	usleep_gradual(time_to_eat, philo);
}

static int64_t	print_log_sleeping(t_philo *philo)
{
	put_log(philo, MSG_SLEEP, get_elapsed_time);
	return (SUCCESS);
}

void	sleeping(t_philo *philo)
{
	const unsigned int	time_to_sleep = philo->args->time_to_sleep;

	philo_action(philo, print_log_sleeping);
	usleep_gradual(time_to_sleep, philo);
}

static int64_t	print_log_thinking(t_philo *philo)
{
	put_log(philo, MSG_THINK, get_elapsed_time);
	return (SUCCESS);
}

void	thinking(t_philo *philo)
{
	philo_action(philo, print_log_thinking);
}
