#include <stdint.h>
#include <sys/time.h>
#include <unistd.h>

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
