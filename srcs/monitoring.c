/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcauchy- <mcauchy-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 11:10:46 by mcauchy-          #+#    #+#             */
/*   Updated: 2025/03/20 13:22:16 by mcauchy-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	check_meals(t_data *data)
{
	int	index;
	int	i;

	index = 1;
	if (data->nb_must_eat <= 0)
		return (0);
	i = -1;
	while (++i < data->nb_philo)
	{
		pthread_mutex_lock(data->philo[i].data->mutex);
		if (data->philo[i].meals < data->nb_must_eat)
		{
			index = 0;
			pthread_mutex_unlock(data->philo[i].data->mutex);
			break ;
		}
		pthread_mutex_unlock(data->philo[i].data->mutex);
	}
	return (index);
}

void	*routine(void *philo)
{
	t_philo	*ph;

	ph = (t_philo *)philo;
	while (!is_dead(ph))
	{
		take_fork(ph);
		if (is_dead(ph))
			return (NULL);
		philo_sleep(ph);
		if (is_dead(ph))
			return (NULL);
		philo_think(ph);
		usleep(200);
	}
	return (NULL);
}

void	*monitoring(t_data *data)
{
	int	i;

	while (1)
	{
		i = -1;
		while (++i < data->nb_philo)
		{
			if (kill_philo(&data->philo[i]))
				return (NULL);
		}
		if (check_meals(data))
		{
			pthread_mutex_lock(data->death);
			data->is_dead = 1;
			pthread_mutex_unlock(data->death);
			mutex_message("All philosophers have eaten enough", data->philo);
			return (NULL);
		}
		usleep(100);
	}
	return (NULL);
}
