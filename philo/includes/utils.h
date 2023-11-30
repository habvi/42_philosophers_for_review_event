#ifndef UTILS_H
# define UTILS_H

# include <pthread.h>
# include <stdbool.h>
# include "result.h"

typedef struct s_rule	t_rule;
typedef struct s_philo	t_philo;

/* utils */
int64_t	call_atomic(pthread_mutex_t *mutex, int64_t (*func)(), void *args);
bool	ft_atoi_positive_uint(const char *str, unsigned int *num);
bool	ft_atoi_positive_int64(const char *str, int64_t *num);
void	*ft_free(void **ptr);
bool	ft_isdigit(int c);
int64_t	ft_max(const int64_t x, const int64_t y);
int64_t	ft_min(const int64_t x, const int64_t y);
int 	ft_strcmp(const char *s1, const char *s2);
bool	ft_streq(const char *s1, const char *s2);
int64_t	get_current_time_usec(void);

/* debug */
void	put_rule(const t_rule *rule);
void	put(const t_philo *philo, char *message);

#endif
