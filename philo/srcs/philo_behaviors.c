#include "philo.h"

static int64_t	get_elapsed_time_for_eating(t_philo *philo)
{
	const int64_t	start_time = philo->args->start_time;
	int64_t			current_time;
	int64_t			elapsed_time;

	set_start_time_of_cycle(philo);
	current_time = philo->start_time_of_cycle;
	elapsed_time = current_time - start_time;
	return (elapsed_time);
}

void	eating(t_philo *philo)
{
	const unsigned int	time_to_eat = philo->args->time_to_eat;
	pthread_mutex_t		*shared;

	shared = &philo->args->shared;
	if (take_two_forks(philo) == BREAK)
		return ;
	pthread_mutex_lock(shared);
	put_log(philo, MSG_EAT, get_elapsed_time_for_eating);
	pthread_mutex_unlock(shared);
	usleep_gradual(time_to_eat, philo);

	put_two_forks(philo);
}

void	sleeping(t_philo *philo)
{
	const unsigned int	time_to_sleep = philo->args->time_to_sleep;
	pthread_mutex_t		*shared;

	shared = &philo->args->shared;
	pthread_mutex_lock(shared);
	put_log(philo, MSG_SLEEP, get_elapsed_time);
	pthread_mutex_unlock(shared);
	usleep_gradual(time_to_sleep, philo);
}

void	thinking(t_philo *philo)
{
	pthread_mutex_t		*shared;

	shared = &philo->args->shared;
	pthread_mutex_lock(shared);
	put_log(philo, MSG_THINK, get_elapsed_time);
	pthread_mutex_unlock(shared);
}
