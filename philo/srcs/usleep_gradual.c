#include <unistd.h> // usleep
#include "philo.h"
#include "utils.h"

static int64_t	calc_sleep_chunk_time(const int64_t end_time)
{
	const int64_t	remain_sleep_time = end_time - get_current_time_usec();

	return (ft_min(MAX_DURATION, remain_sleep_time / 2));
}

// sleep_time: usec.
void	usleep_gradual(int64_t sleep_time, t_philo *philo)
{
	int64_t	start_time;
	int64_t	end_time;
	int64_t	sleep_chunk_time;

	if (sleep_time <= 0)
		return ;
	start_time = get_current_time_usec();
	end_time = start_time + sleep_time;
	sleep_chunk_time = calc_sleep_chunk_time(end_time);
	while (sleep_chunk_time > 0 && !is_simulation_over_atomic(philo))
	{
		usleep(sleep_chunk_time);
		sleep_chunk_time = calc_sleep_chunk_time(end_time);
	}
}
