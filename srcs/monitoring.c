#include "../include/philo.h"

int	check_meals(t_data *data)
{
	int	nb_meals;
	int	i;

	if (data->nb_must_eat <= 0)
		return (0);
	nb_meals = 0;
	i = -1;
	while (++i < data->nb_philo)
	{
		pthread_mutex_lock(data->philo[i].data->mutex);
		if (data->philo[i].meals >= data->nb_must_eat)
			nb_meals++;
		pthread_mutex_unlock(data->philo[i].data->mutex);
	}
	if (nb_meals == data->nb_philo)
	{
		pthread_mutex_lock(data->death);
		data->is_dead = 1;
		pthread_mutex_unlock(data->death);
		return (1);
	}
	return (0);
}

// void	*check_meals(t_data *data, int i)
// {
// 	pthread_mutex_lock(data->philo[i].data->mutex);
// 	if (data->philo[i].meals >= data->nb_must_eat && data->nb_must_eat > 0)
// 	{
// 		data->philo[i].has_eat++;
// 		if (data->philo->has_eat == data->nb_philo)
// 		{
// 			data->is_dead = 1;
// 			pthread_mutex_unlock(data->philo[i].data->mutex);
// 			return (NULL);
// 		}
// 	}
// 	pthread_mutex_unlock(data->philo[i].data->mutex);
// 	return (&data->philo[i]);
// }

void	*monitoring(t_data *data)
{
	int	i;

	while (!data->is_dead)
	{
		i = -1;
		while (++i < data->nb_philo)
		{
			if (kill_philo(&data->philo[i]))
			return (NULL);
		}
		if (check_meals(data))
			return (NULL);
		usleep(100);
	}
	return (NULL);
}