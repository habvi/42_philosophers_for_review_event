#include <unistd.h> // usleep
#include "philo.h"
#include "utils.h"

// sleep_time: msec.
void	usleep_gradual(int64_t sleep_time, t_philo *philo)
{
	const int64_t	start_time = get_current_time_usec();
	int64_t			remain_sleep_time;

	sleep_time *= 1000;
	while (start_time + sleep_time - get_current_time_usec() >= 1000)
	{
		if (is_any_philo_died(philo))
			break ;
		usleep(1000);
	}
	remain_sleep_time = start_time + sleep_time - get_current_time_usec();
	if (0 < remain_sleep_time && remain_sleep_time < 1000)
		usleep(remain_sleep_time);
}
