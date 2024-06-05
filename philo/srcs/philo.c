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
		if (ft_atol_int(av[i]) < 0)
		{
			return (1);
		}
		i++;
	}
	return (0);
}

void	assign_arguments_to_philo_table(t_philo_table *philo_table, int value, int var)
{
	if (var == 1)
		philo_table->num_of_philos = value;
	else if (var == 2)
		philo_table->time_to_die = value;
	else if (var == 3)
		philo_table->time_to_eat = value;
	else if (var == 4)
		philo_table->time_to_sleep = value;
	else if (var == 5)
	{
		philo_table->number_of_meals = value;
		philo_table->meals_defined = true;
	}
}

void check_arguments_and_assign(char **av, t_philo_table *philo_table)
{
	int i;
	int atol_value;

	i = 1;
	philo_table->table_assigned = false;
	philo_table->meals_defined = false;
	while (av[i])
	{
		atol_value = ft_atol_int(av[i]);
		if (atol_value == -1)
		{
			write(2, "Error: arguments must be positive integers\n", 43);
			return ;
		}
		else if (atol_value == -2)
		{
			write(2, "Error: overflow in arguments\n", 29);
			return ;
		}
		if (i == 1 && atol_value < 2)
		{
			if (atol_value == 0)
				write(2, "Error: number of philosopher should be superior to 0\n", 53);
			else if (atol_value == 1)
				write(2, "0 1 died\n", 9);
			return ;
		}
		assign_arguments_to_philo_table(philo_table, atol_value, i);
		i++;
	}
	philo_table->table_assigned = true;
}

int	main(int ac, char **av)
{
	t_philo_table philo_table;

	if (ac < 5 || ac > 6)
	{
		write(2, "Error: wrong number of arguments\n", 33);
		return (1);
	}
	check_arguments_and_assign(av, &philo_table);
	if (!philo_table.table_assigned)
		return (1);
	printf("num_of_philos: %d\n", philo_table.num_of_philos);
	printf("time_to_die: %d\n", philo_table.time_to_die);
	printf("time_to_eat: %d\n", philo_table.time_to_eat);
	printf("time_to_sleep: %d\n", philo_table.time_to_sleep);
	if (philo_table.meals_defined)
		printf("number_of_meals: %d\n", philo_table.number_of_meals);
	return (0);
}
