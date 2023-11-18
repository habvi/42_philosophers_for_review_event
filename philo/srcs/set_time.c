#include "philo.h"
#include "utils.h"

void	set_start_time(t_args *args)
{
	args->start_time = get_current_time_usec();
}

static int64_t	calc_max_cycle_time(const t_args *args)
{
	return (ft_max(args->time_to_eat * 2, \
					args->time_to_eat + args->time_to_sleep));
}

int64_t	calc_time_to_think(const t_args *args)
{
	const int64_t	n = args->num_of_philos;
	const int64_t	max_cycle_time = calc_max_cycle_time(args);
	int64_t			num_of_cycle;
	int64_t			total_time_to_think;
	int64_t			time_to_think;

	if (max_cycle_time == 0)
		return (0);
	num_of_cycle = args->time_to_eat * n / max_cycle_time;
	if (num_of_cycle == 0)
		return (0);
	total_time_to_think = args->time_to_eat * n % max_cycle_time;
	time_to_think = total_time_to_think / num_of_cycle \
				+ max_cycle_time - (args->time_to_eat + args->time_to_sleep);
	return (time_to_think);
}
