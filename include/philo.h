#ifndef PHILO_H

#define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include <pthread.h>
# include <sys/time.h>

typedef struct s_philo
{
	int				id;
	int				meals;
	int				last_eat;
	int				has_eat;
	int				nb_eat;
	pthread_t		thread;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	struct s_data	*data;
}				t_philo;

typedef struct s_data
{
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				nb_must_eat;
	int				nb_philo;
	int				is_dead;
	int				start_time;
	t_philo			*philo;
	pthread_mutex_t	*fork;
	pthread_mutex_t	*death;
	pthread_mutex_t	*message;
	pthread_mutex_t	*mutex;
}				t_data;

int		one_philo(t_data *data);
int		is_dead(t_philo *philo);
void	init_philo(t_data *data);
void	*routine(void *philo);
void	init_fork(t_data *data);
void	init_data(t_data *data, char **av);
void	philo_think(t_philo *philo);
void	philo_sleep(t_philo *philo);
void	take_fork(t_philo *philo);
void	assign_fork(t_data *data, int i);
void	philo_eat(t_philo *philo);
void	mutex_message(char *message, t_philo *philo);
int		get_time(void);
int		get_time_since_start(t_philo *philo);
void	ft_usleep(int time);
void	error_exit(char *message);
void	*check_meals(t_data *data, int i);
int		kill_philo(t_philo *philo);
void	philo_die(t_philo *philo);
void	join_thread(t_data *data);
void	*monitoring(t_data *data);

#endif