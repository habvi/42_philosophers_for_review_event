#ifndef PHILO_H
# define PHILO_H

# include <stdbool.h>

# define THREAD_SUCCESS	0

// todo: types
typedef struct s_args {
	int	number_of_philosophers;
	int	time_to_die;
	int	time_to_eat;
	int	time_to_sleep;
	int	number_of_times_each_philosopher_must_eat;
}	t_args;

/* args */
bool	is_valid_argc(const int argc);
t_args	set_args(const int argc, const char **argv);

#endif
