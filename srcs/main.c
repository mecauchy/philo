#include "../include/philo.h"

int	kill_philo(t_philo *philo)
{
	pthread_mutex_lock(philo->data->mutex);
	if (!philo->data->is_dead
		&& get_time() - philo->last_eat
		>= philo->data->time_to_die)
	{
		philo->data->is_dead = 1;
		pthread_mutex_unlock(philo->data->mutex);
		mutex_message("is dead", philo);
		return (1);
	}
	pthread_mutex_unlock(philo->data->mutex);
	return (0);
}

/*
	- Check if the philosopher is dead
	- if the philosopher is dead, return 1
	- if the philosopher is not dead, return 0

	locks and unlocks the mutex
*/
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

int	one_philo(t_data *data)
{
	printf("Philosopher 1 has taken a fork\n");
	ft_usleep(data->time_to_die);
	printf("Philosopher 1 is dead after %dms\n", data->time_to_die);
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
	init_data(&data, av);
	if (atoi(av[1]) == 1)
		return (one_philo(&data));
	init_fork(&data);
	init_philo(&data);
	join_thread(&data);
	free_all(&data);
	return (0);
}
