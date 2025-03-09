#include "../include/philo.h"

void	*check_meals(t_data *data, int i)
{
	pthread_mutex_lock(data->philo[i].data->mutex);
	if (data->philo[i].meals >= data->nb_must_eat && data->nb_must_eat > 0)
	{
		data->philo->has_eat++;
		if (data->philo->has_eat == data->nb_philo)
		{
			data->is_dead = 1;
			pthread_mutex_unlock(data->philo[i].data->mutex);
			return (NULL);
		}
	}
	pthread_mutex_unlock(data->philo[i].data->mutex);
	return (&data->philo[i]);
}

void	*monitoring(t_data *data)
{
	int	i;

	i = 0;
	while (1)
	{
		i = 0;
		while (i < data->nb_philo)
		{
			if (!check_meals(data, i))
				return (NULL);
			if (kill_philo(&data->philo[i]))
				return (NULL);
			}
			usleep(400);
		}
	}