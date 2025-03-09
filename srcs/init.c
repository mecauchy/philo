#include "../include/philo.h"

void	init_data(t_data *data, char **av)
{
	printf("hre002");
	data->nb_philo = atoi(av[1]);
	data->time_to_die = atoi(av[2]);
	data->time_to_eat = atoi(av[3]);
	data->time_to_sleep = atoi(av[4]);
	if (av[5])
		data->nb_must_eat = atoi(av[5]);
	else
		data->nb_must_eat = -1;
	data->is_dead = 0;
	data->philo->has_eat = 0;
	if (data->time_to_die > 6000 || data->time_to_eat > 6000 || data->time_to_sleep > 6000)
		error_exit("Error: time must be less than 6000ms\n");
	data->death = 0;
	data->fork = malloc(sizeof(pthread_mutex_t) * data->nb_philo);
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
		data->philo[i].nb_eat = 0;
		data->philo[i].data = data;
		data->philo[i].meals = 0;
		assign_fork(data, i);
		if (pthread_create(&data->philo[i].thread, NULL,
				&routine, &data->philo[i]))
			return ;
	}
	monitoring(data);
}
void free_all(t_data *data)
{
    int i;

    i = 0;
    while (i < data->nb_philo)
    {
        pthread_mutex_destroy(&data->fork[i]);
        i++;
    }
    pthread_mutex_destroy(data->death);
    pthread_mutex_destroy(data->mutex);
    free(data->philo);
    free(data->fork);
    free(data->death);
    free(data->mutex);
}