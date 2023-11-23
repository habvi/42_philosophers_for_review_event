#include "philo.h"
#include "utils.h"

bool	is_valid_argc(const int argc)
{
	if (!(argc == 5 || argc == 6))
	{
		error_args();
		return (false);
	}
	return (true);
}

static int64_t	calc_max_cycle_time(const t_rule *rule)
{
	return (ft_max(rule->time_to_eat * 2, \
					rule->time_to_eat + rule->time_to_sleep));
}

// to live longer, wait for thinking time. (usec)
static int64_t	calc_time_to_think(const t_rule *rule)
{
	const int64_t	n = rule->num_of_philos;
	int64_t			max_cycle_time;
	int64_t			num_of_cycle;
	int64_t			total_time_to_think;
	int64_t			time_to_think;

	if (n % 2 == 0)
		return (0);
	max_cycle_time = calc_max_cycle_time(rule);
	if (max_cycle_time == 0)
		return (0);
	num_of_cycle = rule->time_to_eat * n / max_cycle_time;
	if (num_of_cycle == 0)
		return (0);
	total_time_to_think = rule->time_to_eat * n % max_cycle_time;
	time_to_think = total_time_to_think / num_of_cycle \
				+ max_cycle_time - (rule->time_to_eat + rule->time_to_sleep);
	return (time_to_think);
}

// time_to_die, eat, sleep : convert msec to usec.
static t_result	set_argv(const int argc, const char **argv, t_rule *rule)
{
	bool	is_correct_num;

	is_correct_num = true;
	is_correct_num &= ft_atoi_positive_uint(argv[1], &rule->num_of_philos);
	is_correct_num &= (rule->num_of_philos >= 1);
	is_correct_num &= ft_atoi_positive_int64(argv[2], &rule->time_to_die);
	is_correct_num &= ft_atoi_positive_int64(argv[3], &rule->time_to_eat);
	is_correct_num &= ft_atoi_positive_int64(argv[4], &rule->time_to_sleep);
	rule->num_of_each_philo_must_eat = NOT_SET;
	if (argc == 6)
		is_correct_num &= ft_atoi_positive_int64(\
									argv[5], &rule->num_of_each_philo_must_eat);
	if (!is_correct_num)
		return (FAILURE);
	rule->time_to_die *= 1000;
	rule->time_to_eat *= 1000;
	rule->time_to_sleep *= 1000;
	rule->time_to_think = calc_time_to_think(rule);
	return (SUCCESS);
}

t_rule	set_rule(const int argc, const char **argv, t_result *result)
{
	t_rule	rule;

	*result = set_argv(argc, argv, &rule);
	if (*result == FAILURE)
		error_args();
	return (rule);
}
