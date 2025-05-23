/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcauchy- <mcauchy-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 11:10:31 by mcauchy-          #+#    #+#             */
/*   Updated: 2025/03/20 13:26:22 by mcauchy-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	init_data(t_data *data, char **av)
{
	data->nb_philo = atoi(av[1]);
	data->time_to_die = atoi(av[2]);
	data->time_to_eat = atoi(av[3]);
	data->time_to_sleep = atoi(av[4]);
	if (av[5])
		data->nb_must_eat = atoi(av[5]);
	else
		data->nb_must_eat = 0;
	data->is_dead = 0;
	data->death = malloc(sizeof(pthread_mutex_t));
	data->mutex = malloc(sizeof(pthread_mutex_t));
	data->message = malloc(sizeof(pthread_mutex_t));
	data->fork = malloc(sizeof(pthread_mutex_t) * data->nb_philo);
	if (!data->death || !data->message || !data->mutex || !data->fork)
	{
		free_all(data);
		error_exit("malloc failed for mutexes");
	}
}

void	init_fork(t_data *data)
{
	int	i;

	i = -1;
	pthread_mutex_init(data->death, NULL);
	pthread_mutex_init(data->message, NULL);
	pthread_mutex_init(data->mutex, NULL);
	while (++i < data->nb_philo)
	{
		pthread_mutex_init(&data->fork[i], NULL);
	}
}

void	init_philo(t_data *data)
{
	int	i;

	i = -1;
	data->start_time = get_time();
	data->philo = malloc(sizeof(t_philo) * data->nb_philo);
	if (!data->philo)
		return ;
	while (++i < data->nb_philo)
	{
		data->philo[i].id = i + 1;
		data->philo[i].data = data;
		data->philo[i].meals = 0;
		data->philo[i].last_eat = data->start_time;
		assign_fork(data, i);
		if (pthread_create(&data->philo[i].thread, NULL,
				&routine, &data->philo[i]))
			return ;
	}
	monitoring(data);
}

void	free_all(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->nb_philo)
	{
		pthread_mutex_destroy(&data->fork[i]);
		i++;
	}
	pthread_mutex_destroy(data->death);
	pthread_mutex_destroy(data->mutex);
	pthread_mutex_destroy(data->message);
	if (data->philo)
		free(data->philo);
	if (data->fork)
		free(data->fork);
	if (data->death)
		free(data->death);
	if (data->mutex)
		free(data->mutex);
	if (data->message)
		free(data->message);
}
