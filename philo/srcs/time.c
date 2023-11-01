#include "philo.h"
#include "utils.h"

void	set_start_time(t_args *args)
{
	args->start_time = get_current_time_msec();
}

int64_t	get_elapsed_time(const t_philo *philo)
{
	const int64_t	start_time = philo->args->start_time;
	const int64_t	current_time = get_current_time_msec();
	const int64_t	elapsed_time = current_time - start_time;

	return (elapsed_time);
}

void	set_start_time_of_cycle(t_philo_var *philo_var)
{
	pthread_mutex_lock(&philo_var->for_start_time);
	philo_var->start_time_of_cycle = get_current_time_msec();
	pthread_mutex_unlock(&philo_var->for_start_time);
}

static int64_t	get_start_time_of_cycle(t_philo_var *philo_var)
{
	int64_t	start_time_of_cycle;

	pthread_mutex_lock(&philo_var->for_start_time);
	start_time_of_cycle = philo_var->start_time_of_cycle;
	pthread_mutex_unlock(&philo_var->for_start_time);
	return (start_time_of_cycle);
}

int64_t	get_elapsed_cycle_time(const t_philo *philo)
{
	const int64_t	now_time = get_current_time_msec();
	const int64_t	start_time_of_cycle = get_start_time_of_cycle(philo->var);
	const int64_t	elapsed_cycle_time = now_time - start_time_of_cycle;

	return (elapsed_cycle_time);
}
