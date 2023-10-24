#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdbool.h>
# include "result.h"

# define MUTEX_SUCCESS	0
# define THREAD_SUCCESS	0

typedef struct s_philo	t_philo;

// todo: types
typedef struct s_args {
	int				num_of_philos;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				num_of_times_each_philo_must_eat;
	// common data
	long			start_time;
	t_philo			**philos;
	pthread_mutex_t	*forks;
	pthread_mutex_t	for_log;
}	t_args;

typedef struct s_philo {
	int				id;
	t_args			*args;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
}	t_philo;

/* args */
bool		is_valid_argc(const int argc);
t_args		set_args(const int argc, const char **argv, t_result *result);

/* mutex */
t_result	init_mutex(t_args *args);
void		destroy_mutex(t_args *args);

/* thread_create */
pthread_t	*create_threads(t_args *args);

/* threads */
void		wait_threads(const t_args *args, pthread_t *threads);
void		destroy_threads(pthread_t **threads);

/* philos_behaviors */
t_result	eating(const t_philo *philo);
void		sleeping(const t_philo *philo);
void		thinking(const t_philo *philo);

#endif
