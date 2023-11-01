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

# define ERR_INVALID_ARG	"Error: invalid arguments."

typedef struct s_philo	t_philo;

// todo: types
typedef struct s_args {
	int				num_of_philos;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				num_of_times_each_philo_must_eat;
	// common data
	int64_t			start_time;
	t_philo			**philos;
	pthread_mutex_t	*forks;
	pthread_mutex_t	for_log;
	bool			is_any_philo_died;
	pthread_mutex_t	for_death;
	pthread_mutex_t	start_cycle;
}	t_args;

typedef struct s_philo_var {
	int64_t			start_time_of_cycle;
	pthread_mutex_t	for_start_time;
}	t_philo_var;

typedef struct s_philo {
	int				id;
	t_args			*args;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	// not const
	t_philo_var		*var;
}	t_philo;

typedef struct s_monitor {
	int		id;
	t_args	*args;
}	t_monitor;

/* args */
bool		is_valid_argc(const int argc);
t_args		set_args(const int argc, const char **argv, t_result *result);

/* destroy */
void		destroy_forks(t_args *args);
void		destroy(t_args *args, pthread_t **threads, pthread_t **monitors);

/* mutex */
t_result	init_mutex(t_args *args);

/* thread_create */
pthread_t	*create_threads(t_args *args);

/* philo_behaviors */
t_result	take_two_forks(const t_philo *philo);
t_result	eating(const t_philo *philo);
t_result	put_two_forks(const t_philo *philo);
t_result	sleeping(const t_philo *philo);
t_result	thinking(const t_philo *philo);

/* philo_cycle */
bool		is_any_philo_died(const t_philo *philo);
void		*philo_cycle(void *thread_args);

/* monitor*/
pthread_t	*monitor_death(t_args *args);
void		*monitor_cycle(void *thread_args);

/* time */
void		set_start_time(t_args *args);
int64_t		get_elapsed_time(const t_philo *philo);
int64_t		get_elapsed_cycle_time(const t_philo *philo);
t_result	set_start_time_of_cycle(t_philo_var *philo_var);
void	    usleep_gradual(int64_t sleep_time, const t_philo *philo);

/* put */
void		put_log(const t_philo *philo, const char *message)
;

#endif
