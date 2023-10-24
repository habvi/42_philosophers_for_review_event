#include <stdio.h>
#include <stdlib.h> // exit
#include <sys/time.h>
#include "utils.h"

long	get_current_time(void)
{
	struct timeval	current_time;
	long			sec;
	long			micro_sec;
	long			milli_sec;

	if (gettimeofday(&current_time, NULL) == TIME_ERROR)
	{
		perror("gettimeofday");
		exit(EXIT_FAILURE); // todo: erase
	}
	sec = current_time.tv_sec;
	micro_sec = current_time.tv_usec;
	milli_sec = sec * 1000L + micro_sec / 1000L;
	// printf("%ld ", milli_sec);
	return (milli_sec);
}
