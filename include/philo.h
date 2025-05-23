/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcauchy- <mcauchy-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 11:10:58 by mcauchy-          #+#    #+#             */
/*   Updated: 2025/03/20 13:17:38 by mcauchy-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H

# define PHILO_H

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

// ---------------------------------------------------------------------------
//					INITIALIZATION
// ---------------------------------------------------------------------------
void	init_data(t_data *data, char **av);
void	init_philo(t_data *data);
void	init_fork(t_data *data);
void	assign_fork(t_data *data, int i);

// ---------------------------------------------------------------------------
//					PARSING
// ---------------------------------------------------------------------------
int		check_digit(char **av);
int		check_time(char **av);
int		check_nb_philo(char **av);
int		nb_must_eat(char **av);
void	check_args(char **av);

// ---------------------------------------------------------------------------
//					ACTION PHILO
// ---------------------------------------------------------------------------
void	*routine(void *philo);
void	philo_think(t_philo *philo);
void	philo_sleep(t_philo *philo);
void	philo_eat(t_philo *philo);
void	take_fork(t_philo *philo);
int		is_dead(t_philo *philo);
int		kill_philo(t_philo *philo);
int		check_meals(t_data *data);

// ---------------------------------------------------------------------------
//					SYNCHRONISATION
// ---------------------------------------------------------------------------
void	mutex_message(char *message, t_philo *philo);
void	join_thread(t_data *data);
void	*monitoring(t_data *data);

// ---------------------------------------------------------------------------
//					UTILS
// ---------------------------------------------------------------------------
int		get_time(void);
int		get_time_since_start(t_philo *philo);
void	ft_usleep(int time);
void	error_exit(char *message);
void	free_all(t_data *data);

// ---------------------------------------------------------------------------
//					ONE
// ---------------------------------------------------------------------------
int		one_philo(t_data *data, char **av);

#endif