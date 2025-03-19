/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcauchy- <mcauchy-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 11:10:35 by mcauchy-          #+#    #+#             */
/*   Updated: 2025/03/19 17:33:43 by mcauchy-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	kill_philo(t_philo *philo)
{
	pthread_mutex_lock(philo->data->death);
	pthread_mutex_lock(philo->data->mutex);
	if (!philo->data->is_dead
		&& get_time() - philo->last_eat
		>= philo->data->time_to_die) // + 1 ou + 2 si aucue solution trouve quand ils sont cense clams // > philo->data... + 1
	{
		philo->data->is_dead = 1;
		pthread_mutex_unlock(philo->data->death);
		pthread_mutex_unlock(philo->data->mutex);
		mutex_message("died", philo);
		return (1);
	}
	pthread_mutex_unlock(philo->data->death);
	pthread_mutex_unlock(philo->data->mutex);
	return (0);
}

int	is_dead(t_philo *philo)
{
	pthread_mutex_lock(philo->data->death);
	if (philo->data->is_dead == 1)
	{
		pthread_mutex_unlock(philo->data->death);
		return (1);
	}
	pthread_mutex_unlock(philo->data->death);
	return (0);
}

int	one_philo(t_data *data, char **av)
{
	data->time_to_die = atoi(av[2]);
	if (data->time_to_die > 6000)
		error_exit("Error: time must be less than 6000ms\n");
	printf("0 1 has taken a fork\n");
	ft_usleep(data->time_to_die);
	printf("%d 1 died", data->time_to_die);
	return (0);
}

void	join_thread(t_data *data)
{
	int	i;

	i = -1;
	while (++i < data->nb_philo)
		pthread_join(data->philo[i].thread, NULL);
}

int	main(int ac, char **av)
{
	t_data	data;

	if (ac < 5 || ac > 6)
	{
		printf("Error: wrong number of arguments\n");
		return (1);
	}
	check_args(av);
	if (atoi(av[1]) == 1)
		return (one_philo(&data, av));
	init_data(&data, av);
	init_fork(&data);
	init_philo(&data);
	join_thread(&data);
	free_all(&data);
	return (0);
}
