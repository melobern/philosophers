/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbernard <mbernard@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 12:02:33 by mbernard          #+#    #+#             */
/*   Updated: 2024/06/04 13:28:55 by mbernard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool check_overflows(char **av)
{
	int i;

	i = 1;
	while (av[i])
	{
		if (atoi(av[i]) < 0)
		{
			write(2, "Error: overflow in arguments\n", 29);
			return (1);
		}
		i++;
	}
	return (0);
}

void	assign_arguments_to_philo_table(t_philo_table *philo_table, char **av)
{
	if (check_overflows == 1)
		return ;
	else
	{
		philo_table->num_of_philos = ft_atoi(av[1]);
		philo_table->time_to_die = ft_atoi(av[2]);
		philo_table->time_to_eat = ft_atoi(av[3]);
		philo_table->time_to_sleep = ft_atoi(av[4]);
		philo_table->num_must_eat = ft_atoi(av[5]);

	}
}

int	main(int ac, char **av)
{
	t_philo_table philo_table;

	if (ac != 6)
		write(2, "Error: wrong number of arguments\n", 33);
	else
		assign_arguments_to_philo_table(&philo_table, av);
}
