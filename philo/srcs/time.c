#include <stdlib.h> // exit
#include <sys/time.h>
#include "philo.h"
#include "utils.h"

long	get_current_time(void)
{
	struct timeval	current_time;
	long			sec;
	long			micro_sec;
	long			milli_sec;

	if (gettimeofday(&current_time, NULL) == TIME_ERROR)
		exit(EXIT_FAILURE); // todo: erase
	sec = current_time.tv_sec;
	micro_sec = current_time.tv_usec;
	milli_sec = sec * 1000L + micro_sec / 1000L;
	// printf("%ld ", milli_sec);
	return (milli_sec);
}

long	get_elapsed_time(const t_philo *philo)
{
	const long	start_time = philo->args->start_time;
	const long	current_time = get_current_time();
	const long	elapsed_time = current_time - start_time;

	return (elapsed_time);
}

t_result	set_start_time_of_cycle(t_philo_var *philo_var)
{
	if (pthread_mutex_lock(&philo_var->for_start_time) != MUTEX_SUCCESS)
		return (FAILURE);
	philo_var->start_time_of_cycle = get_current_time();
	if (pthread_mutex_unlock(&philo_var->for_start_time) != MUTEX_SUCCESS)
		return (FAILURE);
	return (SUCCESS);
}

long	get_elapsed_cycle_time(const t_philo *philo)
{
	const long	start_time = philo->args->start_time;
	const long	start_time_of_cycle = philo->var->start_time_of_cycle;
	const long	elapsed_cycle_time = start_time_of_cycle - start_time;

	return (elapsed_cycle_time);
}
