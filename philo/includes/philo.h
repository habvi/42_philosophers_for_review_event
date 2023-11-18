#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdbool.h>
# include "result.h"

# define MUTEX_SUCCESS	0
# define THREAD_SUCCESS	0

# define MAX_DURATION		500000
# define ADJUST_DURATION	200

# define MSG_FORK	"has taken a fork"
# define MSG_EAT	"is eating"
# define MSG_SLEEP	"is sleeping"
# define MSG_THINK	"is thinking"
# define MSG_DIED	"died"

# define ERR_INVALID_ARG	"Error: invalid arguments."
# define ERR_FATAL			"Error: fatal error."

# if defined(__linux__)
#  define SPEC_I64	"%ld"
# else
#  define SPEC_I64	"%lld"
# endif

# ifdef COLOR
#  define RED	"\033[31m"
#  define GREEN	"\033[32m"
#  define BLUE	"\033[34m"
#  define PINK	"\033[35m"
#  define END	"\033[0m"
# else
#  define RED
#  define GREEN
#  define BLUE
#  define PINK
#  define END
# endif

typedef struct s_philo		t_philo;
typedef struct s_deque		t_deque;
typedef struct s_deque_node	t_deque_node;

typedef struct s_args {
	unsigned int	num_of_philos;
	int64_t			time_to_die;
	int64_t			time_to_eat;
	int64_t			time_to_sleep;
	int64_t			time_to_think;
	unsigned int	num_of_each_philo_must_eat;
}	t_args;

typedef struct s_shared {
	pthread_mutex_t	shared;
	pthread_mutex_t	*forks;
	int64_t			start_time;
	bool			is_any_philo_dead;
	bool			is_thread_error;
	unsigned int	num_of_finish_eat;
}	t_shared;

typedef struct s_philo {
	unsigned int	id;
	t_args			args;
	t_shared		*shared;
	pthread_mutex_t	*fork1;
	pthread_mutex_t	*fork2;
	int64_t			start_time_of_philo;
	int64_t			start_time_of_cycle;
	unsigned int	eat_count;
	bool			is_self_dead;
	int64_t			current_time;
}	t_philo;

typedef struct s_monitor {
	unsigned int	id;
	t_philo			*philo;
}	t_monitor;

/* args */
bool			is_valid_argc(const int argc);
t_args			set_args(const int argc, const char **argv, t_result *result);

/* init */
t_philo			*init_philos(t_args *args);
t_result		init_shared(t_philo *philos, \
							t_shared *shared, const unsigned int num_of_philos);
t_result		init_mutex(t_shared *shared, const unsigned int num_of_philos);

/* set_time */
int64_t			calc_time_to_think(const t_args *args);

/* destroy */
void			destroy_philos(t_philo **philos);
void			destroy_shared(\
							t_shared *shared, const unsigned int num_of_philos);
void			destroy_forks(\
						pthread_mutex_t **forks, const unsigned int max_len);
void			destroy_threads(t_deque **threads);


/* thread */
t_result		add_threads_list(t_deque *threads, pthread_t new_thread);
t_deque_node	*create_thread_node(pthread_t new_thread);

/* philo_action */
int64_t			is_simulation_over(t_philo *philo);
bool			is_simulation_over_atomic(t_philo *philo);
int64_t			philo_action(t_philo *philo, int64_t (*action)(t_philo *));

/* philo_cycle */
void			*philo_solo_cycle(void *thread_args);
void			*philo_cycle(void *thread_args);

/* philo_behaviors */
void			take_fork(pthread_mutex_t *fork, t_philo *philo);
void			take_two_forks(t_philo *philo);
void			eating(t_philo *philo);
void			put_fork(pthread_mutex_t *fork);
void			put_two_forks(t_philo *philo);
void			sleeping(t_philo *philo);
void			thinking(t_philo *philo);

/* philo_simulate */
t_result		simulate_philos_cycle(t_philo *philos, \
							t_shared *shared, const unsigned int num_of_philos);

/* monitor*/
t_result		monitoring_death(t_philo *philos, \
							t_shared *shared, const unsigned int num_of_philos);
void			*monitor_cycle(void *thread_args);

/* put */
void			put_log(const t_philo *philo, const char *message);
int64_t			put_log_flow(\
					t_philo *philo, void (*set_time)(), const char *message);
t_result		fatal_error(void);

/* usleep */
void			usleep_gradual(int64_t sleep_time, t_philo *philo);

#endif
