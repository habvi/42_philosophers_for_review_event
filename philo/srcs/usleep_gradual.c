#include <unistd.h> // usleep
#include "philo.h"
#include "utils.h"

// sleep_time: msec
void	usleep_gradual(int64_t sleep_time, const t_philo *philo)
{
	const int64_t	start_time = get_current_time_msec();
	const int64_t	target_time = (start_time + sleep_time) * 1000LL;
	int64_t			diff_time;

	while (true)
	{
		diff_time = target_time - get_current_time_usec();
		if (diff_time >= 1000 && !is_any_philo_died(philo))
			usleep(1000);
		else
		{
			// todo: need?
			// if (diff_time > 0)
			// 	usleep(diff_time);
			break ;
		}
	}
}
