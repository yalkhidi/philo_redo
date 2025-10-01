#ifndef PHILO_H
# define PHILO_H

# include <limits.h>
# include <pthread.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

typedef struct s_input t_input;

typedef struct s_philo
{
	pthread_t	thread;
	unsigned int	id;
	unsigned int	eating;
	unsigned int	dead;
	unsigned int	l_fork;
	unsigned int	r_fork;
	unsigned int	last_meal;
	unsigned int	meals_ate;
	unsigned long	start_time;
	pthread_mutex_t	meal_lock;
	pthread_mutex_t	write_lock;
	pthread_mutex_t	dead_lock;
	t_input	*input;
}	t_philo;

typedef struct s_input
{
	unsigned long	n_philo;
	unsigned long	t_die;
	unsigned long	t_eat;
	unsigned long	t_sleep;
	unsigned long	n_t_philo_eat;
	unsigned long	finished;
	pthread_mutex_t	*forks;
	t_philo	*philos;
}	t_input;


unsigned long   ft_atoi(const char *str);
bool    ft_isdigit(char d);
bool is_within_limits(unsigned long num);
void    print_message(char *message);
int	words_count(char const *s);
char	**ft_split(char const *s);
void	free_split(char **split);
bool    check_valid_chars(char **str);
bool	check_valid_operators(int ac, char **av);
unsigned long *get_input(int ac, char **av);
t_input *assign_inputs(unsigned long *input_array);
void	clean(t_input *input, char *message);
void	status_log(t_philo philo, char *status);
unsigned long   get_time(void);
void    init(t_input *input);
void    assign_philos(t_input *input);
void    create_threads(t_input *input);
void    *routine(void *arg);
void    *moniter(void *arg);
#endif