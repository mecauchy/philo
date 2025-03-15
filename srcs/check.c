#include "../include/philo.h"

int	check_digit(char **av)
{
	int	i;
	int	j;

	i = 0;
	while (av[++i])
	{
		j = -1;
		while (av[i][++j])
		{
			if (av[i][j] < '0' || av[i][j] > '9')
				return (0);
		}
		if (atoi(av[i]) <= 0)
			return (0);
	}
	return (1);
}

int	check_time(char **av)
{
	int	i;

	i = 0;
	while (av[++i])
	{
		if (atoi(av[i]) > 6000)
			return (0);
	}
	return (1);
}

int	check_nb_philo(char **av)
{
	int	i;

	i = 0;
	while (av[++i])
	{
		if ((atoi(av[1]) < 1) || atoi(av[1]) > 200)
			return (0);
	}
	return (1);
}

void	check_args(char **av)
{
	if (!check_digit(av))
		error_exit("Error: arguments must be digits\n");
	if (!check_nb_philo(av))
		error_exit("Error: number of arguments must be between 1 and 200\n");
	if (!check_time(av))
		error_exit("Error: time must be less than 6000ms\n");
}