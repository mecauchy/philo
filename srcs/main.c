#include "../include/philo.h"

void	philo_die(t_philo *philo)
{
	pthread_mutex_lock(philo->data->death);
	printf("%dms\t : Philosopher %d is dead\n", get_time() - philo->data->start_time, philo->id);
	// printf("Philosopher %d is dead\n", 16);
	philo->data->is_dead = 1;
	pthread_mutex_unlock(philo->data->death);
}

int	kill_philo(t_philo *philo)
{
	pthread_mutex_lock(philo->data->death);
	pthread_mutex_lock(philo->data->mutex);
	if (philo->data->is_dead == 1 || get_time_since_start(philo) - philo->last_eat > philo->data->time_to_die)
	{
		philo_die(philo);
		pthread_mutex_unlock(philo->data->death);
		pthread_mutex_unlock(philo->data->mutex);
		return (1);
	}
	pthread_mutex_unlock(philo->data->death);
	pthread_mutex_unlock(philo->data->mutex);
	return (0);
}

int	is_dead(t_philo *philo)
{
	/*
		- Check if the philosopher is dead
		- if the philosopher is dead, return 1
		- if the philosopher is not dead, return 0

		locks and unlocks the mutex
	*/
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
	printf("0 1 has taken a fork\n");
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
	init_data(&data, av);
	if (atoi(av[1]) == 1)
		return(one_philo(&data));
	init_fork(&data);
	init_philo(&data);
	join_thread(&data);
	return (0);
}
