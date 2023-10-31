#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/time.h>
#include <stdbool.h>

int64_t	get_current_time_usec(void)
{
	struct timeval	current_time;
	long			sec;
	long			micro_sec;

	gettimeofday(&current_time, NULL);
	sec = current_time.tv_sec;
	micro_sec = current_time.tv_usec;
	return ((int64_t)sec * 1000LL * 1000LL + micro_sec);
}

int64_t	get_current_time_msec(void)
{
	return (get_current_time_usec() / 1000LL);
}

void	usleep_gradual(int64_t start_time, int64_t sleep_time)
{
	const int64_t	target_time = (start_time + sleep_time) * 1000LL;
	int64_t			diff_time;

	while (true)
	{
		diff_time = target_time - get_current_time_usec();
		if (diff_time >= 1000)
			usleep(1000);
		else
		{
			// if (diff_time > 0)
			// 	usleep(diff_time);
			break;
		}
	}
}

int main(void) {
	int64_t	start_time = get_current_time_msec();

	printf("start: %ld\n", get_current_time_msec() - start_time);
	usleep_gradual(start_time, 100);
	printf("start: %ld\n", get_current_time_msec() - start_time);
}