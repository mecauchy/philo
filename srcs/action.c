/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcauchy- <mcauchy-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 11:09:41 by mcauchy-          #+#    #+#             */
/*   Updated: 2025/03/19 17:42:59 by mcauchy-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	philo_eat(t_philo *philo)
{
	pthread_mutex_lock(philo->data->mutex);
	philo->last_eat = get_time();
	pthread_mutex_unlock(philo->data->mutex);
	mutex_message("is eating", philo);
	usleep(philo->data->time_to_eat * 1000);
	pthread_mutex_lock(philo->data->mutex);
	philo->meals++;
	pthread_mutex_unlock(philo->data->mutex);
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
}

void	assign_fork(t_data *data, int i)
{
	data->philo[i].left_fork = &data->fork[i];
	data->philo[i].right_fork = &data->fork[(i + 1) % data->nb_philo];
}

void	take_fork(t_philo *philo)
{
	pthread_mutex_lock((pthread_mutex_t *)((!(philo->id % 2)
				* (long long int)philo->right_fork) + ((philo->id % 2 != 0)
				* (long long int)philo->left_fork)));
	if (is_dead(philo))
	{
		pthread_mutex_unlock((pthread_mutex_t *)((!(philo->id % 2)
					* (long long int)philo->right_fork) + ((philo->id % 2 != 0)
					* (long long int)philo->left_fork)));
		return ;
	}
	mutex_message("has taken a fork", philo);
	pthread_mutex_lock((pthread_mutex_t *)((!(philo->id % 2)
				* (long long int)philo->left_fork) + ((philo->id % 2 != 0)
				* (long long int)philo->right_fork)));
	if (is_dead(philo))
	{	
		pthread_mutex_unlock(philo->right_fork);
		pthread_mutex_unlock(philo->left_fork);
		return ;
	}
	mutex_message("has taken a fork", philo);
	philo_eat(philo);
}

void	philo_sleep(t_philo *philo)
{
	if (is_dead(philo))
		return ;
	mutex_message("is sleeping", philo);
	usleep(philo->data->time_to_sleep * 1000);
}

void	philo_think(t_philo *philo)
{
	if (is_dead(philo))
		return ;
	mutex_message("is thinking", philo);
	usleep(200);
}
