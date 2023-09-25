#ifndef UTILS_H
# define UTILS_H

# include <stdbool.h>

# define TIME_ERROR (-1)

typedef struct s_args	t_args;

/* utils */
bool	ft_atoi(const char *str, int *num);
bool	ft_isdigit(int c);

/* debug */
void	put_args(const t_args *args);
void	put_current_time(void);

#endif
