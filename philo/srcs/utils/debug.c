#include <stdio.h>
#include "philo.h"

void	put_rule(const t_rule *rule)
{
	printf("num of philo  : %d\n", rule->num_of_philos);
	printf("time to die   : "SPEC_I64"\n", rule->time_to_die);
	printf("time to eat   : "SPEC_I64"\n", rule->time_to_eat);
	printf("time to sleep : "SPEC_I64"\n", rule->time_to_sleep);
	printf("must eat : "SPEC_I64"\n", rule->num_of_each_philo_must_eat);
}

static void	put_message(const char *message)
{
	printf("%s\n", message);
}

void	put(const t_philo *philo, char *message)
{
	pthread_mutex_t	*shared;

	shared = &philo->shared->shared;
	pthread_mutex_lock(shared);
	put_message(message);
	pthread_mutex_unlock(shared);
}
