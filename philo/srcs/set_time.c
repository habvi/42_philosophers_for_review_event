#include "philo.h"
#include "utils.h"

void	set_start_time(t_args *args)
{
	args->start_time = get_current_time_usec();
}

int64_t	calc_time_to_think(const t_args *args)
{
	const int64_t	n = args->num_of_philos;
	const int64_t	cycle_time = args->time_to_eat + args->time_to_sleep;
	const int64_t	n_cycles = n * args->time_to_eat / cycle_time;
	const int64_t	total_time_to_think = n * args->time_to_eat % cycle_time;
	const int64_t	time_to_think = total_time_to_think / n_cycles;

	return (time_to_think);
}
