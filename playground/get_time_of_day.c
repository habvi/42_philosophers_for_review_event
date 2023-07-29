#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <unistd.h>

/*
int gettimeofday(struct timeval *tv, struct timezone *tz);

struct timeval {
	time_t      tv_sec;  // s
	suseconds_t tv_usec; // ms
};
*/

#define TIME_ERROR	(-1)

int	main(void)
{
	struct timeval	tv;
	static bool		is_first_time = true;
	long long		base_time;
	long long		now_time;
	size_t			i;

	i = 0;
	while (i < 10)
	{
		if (is_first_time)
		{
			if (gettimeofday(&tv, NULL) == TIME_ERROR)
			{
				perror("gettimeofday");
				exit(EXIT_FAILURE);
			}
			base_time = tv.tv_sec * 1000LL + tv.tv_usec / 1000;
			is_first_time = false;
			printf("%d\n", 0);
			i++;
			continue ;
		}
		usleep(100000);
		if (gettimeofday(&tv, NULL) == TIME_ERROR)
		{
			perror("gettimeofday");
			exit(EXIT_FAILURE);
		}
		now_time = tv.tv_sec * 1000LL + tv.tv_usec / 1000;
		printf("%lld\n", now_time - base_time);
		i++;
	}
}
