#ifndef UTILS_H
# define UTILS_H

# include <stdbool.h>

# define TIME_ERROR (-1)

typedef struct s_args	t_args;
typedef struct s_philo	t_philo;

/* utils */
bool	ft_atoi(const char *str, int *num);
void	*ft_free(void **ptr);
bool	ft_isdigit(int c);

/* debug */
void	put_args(const t_args *args);
void	put(const t_philo *philo, const char *message);

/* time */
long	get_current_time(void);
long	get_elapsed_time(const t_philo *philo);

#endif
