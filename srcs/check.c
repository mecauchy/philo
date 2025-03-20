/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcauchy- <mcauchy-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 11:10:27 by mcauchy-          #+#    #+#             */
/*   Updated: 2025/03/20 13:38:24 by mcauchy-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
		if (atoi(av[i]) < 0)
			return (0);
	}
	return (1);
}

int	nb_must_eat(char **av)
{
	if (av[5] && atoi(av[5]) == 0)
		return (1);
	return (0);
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
		error_exit("Error: arguments must be digits");
	if (!check_nb_philo(av))
		error_exit("Error: number of arguments must be between 1 and 200");
	if (nb_must_eat(av))
		exit(0);
}
