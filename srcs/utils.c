/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcauchy- <mcauchy-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 11:10:51 by mcauchy-          #+#    #+#             */
/*   Updated: 2025/03/18 11:10:52 by mcauchy-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	get_time_since_start(t_philo *philo)
{
	return (get_time() - philo->data->start_time);
}

int	get_time(void)
{
	struct timeval	tv;

	if (gettimeofday(&tv, NULL) < 0)
		return (-1);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

void	ft_usleep(int time)
{
	int	tmp;

	tmp = get_time() + time;
	while (get_time() < tmp)
		usleep(10);
}

void	mutex_message(char *message, t_philo *philo)
{
	pthread_mutex_lock(philo->data->message);
	printf("%d %d %s\n", get_time() - philo->data->start_time,
		philo->id, message);
	pthread_mutex_unlock(philo->data->message);
}

void	error_exit(char *message)
{
	printf("%s\n", message);
	exit(1);
}
