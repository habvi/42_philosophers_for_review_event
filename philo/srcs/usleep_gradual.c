#include <unistd.h> // usleep
#include "philo.h"
#include "utils.h"

// sleep_time: usec.
void	usleep_gradual(int64_t sleep_time, t_philo *philo)
{
	int64_t	start_time;
	int64_t	remain_sleep_time;

	if (sleep_time == 0)
		return ;
	start_time = get_current_time_usec();
	while (start_time + sleep_time - get_current_time_usec() >= 1000)
	{
		if (is_simulation_over_atomic(philo))
			break ;
		usleep(1000);
	}
	remain_sleep_time = start_time + sleep_time - get_current_time_usec();
	if (0 < remain_sleep_time && remain_sleep_time < 1000)
		usleep(remain_sleep_time);
}
