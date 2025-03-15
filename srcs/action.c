#include "../include/philo.h"

/**
 * Allows a philosopher to eat.
 *
 * This function is called when a philosopher has acquired both forks. It locks the
 * philosopher's data mutex, unlocks it, and then sleeps for the duration of the
 * time_to_eat parameter. After the sleep, it increments the philosopher's number
 * of meals and unlocks the left and right forks.
 *
 * @param philo The philosopher who is eating.
 */
void	philo_eat(t_philo *philo)
{
	pthread_mutex_lock(philo->data->mutex);
	philo->last_eat = get_time();
	pthread_mutex_unlock(philo->data->mutex);
	mutex_message("is eating", philo);
	usleep(philo->data->time_to_eat * 1000);
	philo->nb_eat++;
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
}

void	assign_fork(t_data *data, int position)
{
		data->philo[position].left_fork = &data->fork[position];
		data->philo[position].right_fork = &data->fork[(position + 1) % data->nb_philo];
}

/**
 * Attempts to acquire both forks for a philosopher.
 *
 * This function first locks the mutex for the philosopher's right fork, or the left
 * fork if the philosopher's ID is odd. It then checks if the philosopher is dead. If
 * the philosopher is dead, it unlocks the fork and returns. Otherwise, it locks the
 * mutex for the philosopher's other fork.
 *
 * @param philo The philosopher who is trying to acquire the forks.
 */
void	take_fork(t_philo *philo)
{
	pthread_mutex_lock((pthread_mutex_t *)((!(philo->id % 2) * (long long int)philo->right_fork) + ((philo->id %2 != 0) * (long long int)philo->left_fork)));
	mutex_message("has taken a fork", philo);
	if (is_dead(philo))
	{
		pthread_mutex_unlock((pthread_mutex_t *)((!(philo->id % 2) * (long long int)philo->right_fork) + ((philo->id %2 != 0) * (long long int)philo->left_fork)));
		return ;
	}
	pthread_mutex_lock((pthread_mutex_t *)((!(philo->id % 2) * (long long int)philo->left_fork) + ((philo->id %2 != 0) * (long long int)philo->right_fork)));
	mutex_message("has taken a fork", philo);
	philo_eat(philo);
}

/**
 * Puts the philosopher in a sleeping state for a specified duration.
 *
 * This function checks if the philosopher is dead, and if not, simulates the philosopher
 * sleeping by sleeping for the duration specified by the `time_to_sleep` parameter.
 *
 * @param philo The philosopher who is sleeping.
 */
void	philo_sleep(t_philo *philo)
{
	if (is_dead(philo))
		return ;
	mutex_message("is sleeping", philo);
	usleep(philo->data->time_to_sleep * 1000);
}

/**
 * Puts the philosopher in a thinking state for a short period of time.
 *
 * This function checks if the philosopher is dead, and if not, simulates the philosopher
 * thinking by sleeping for a short duration. The sleep duration may be modified as needed.
 *
 * @param philo The philosopher who is thinking.
 */
void	philo_think(t_philo *philo)
{
	if (is_dead(philo))
		return ;
	mutex_message("is thinking", philo);
	usleep(200); // May be modified according to the need
}