#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdbool.h>
# include "result.h"

# define MUTEX_SUCCESS	0
# define THREAD_SUCCESS	0

# define MSG_FORK	"has taken a fork"
# define MSG_EAT	"is eating"
# define MSG_SLEEP	"is sleeping"
# define MSG_THINK	"is thinking"
# define MSG_DIED	"died"

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
	bool			is_any_philo_died;
	pthread_mutex_t	for_death;
}	t_args;

typedef struct s_philo_var {
	long	start_time_of_cycle;
}	t_philo_var;

typedef struct s_philo {
	int				id;
	t_args			*args;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	// not const
	t_philo_var		*var;
	// t_common_data	*data;
}	t_philo;

/* args */
bool		is_valid_argc(const int argc);
t_args		set_args(const int argc, const char **argv, t_result *result);

/* destroy */
void		destroy(t_args *args, pthread_t **threads);

/* mutex */
t_result	init_mutex(t_args *args);
void		destroy_mutex(t_args *args);

/* thread_create */
pthread_t	*create_threads(t_args *args);

/* threads */
void		wait_threads(const t_args *args, pthread_t *threads);
void		destroy_threads(pthread_t **threads);

/* philo_behaviors */
t_result	take_two_forks(const t_philo *philo);
t_result	eating(const t_philo *philo);
t_result	put_two_forks(const t_philo *philo);
t_result	sleeping(const t_philo *philo);
t_result	thinking(const t_philo *philo);

/* philo_cycle */
void		*philo_cycle(void *thread_args);

/* put */
void		put_log(const t_philo *philo, const char *message)
;

#endif
