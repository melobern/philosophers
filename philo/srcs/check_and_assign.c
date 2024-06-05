/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_and_assign.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbernard <mbernard@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 13:22:26 by mbernard          #+#    #+#             */
/*   Updated: 2024/06/05 13:57:00 by mbernard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	ft_skip_white_spaces(const char *str)
{
	int	x;

	x = 0;
	while (str[x] && ((str[x] > 8 && str[x] < 14) || str[x] == 32))
		x++;
	return (x);
}

static int	ft_atol_int(const char *str)
{
	long	i;
	long	nb;

	nb = 0;
	i = ft_skip_white_spaces(str);
	if (str[i] && (str[i] == '+' || str[i] == '-'))
		i++;
	while (str[i] >= '0' && str[i] <= '9')
	{
		nb = nb * 10 + (str[i] - '0');
		i++;
		if (nb > INT_MAX || nb < INT_MIN)
			return (-2);
	}
	if (str[0] && str[0] == '-')
		return (-1);
	return ((int)nb);
}

static void	assign_arguments_to_philo_table(t_philo_table *philo_table,
		int value, int var)
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

static bool	check_philos_number(int num_of_philos)
{
	if (num_of_philos == 0 || num_of_philos == 1)
	{
		if (num_of_philos == 0)
			write(2, "Error: number of philosopher should be superior to 0\n",
				53);
		else
			write(2, "0 1 died\n", 9);
		return (false);
	}
	return (true);
}

void	check_arguments_and_assign(char **av, t_philo_table *philo_table)
{
	int	i;
	int	atol_value;

	i = 1;
	philo_table->table_assigned = false;
	philo_table->meals_defined = false;
	while (av[i])
	{
		atol_value = ft_atol_int(av[i]);
		if (atol_value < 0)
		{
			if (atol_value == -1)
				write(2, "Error: arguments must be positive integers\n", 43);
			if (atol_value == -2)
				write(2, "Error: overflow in arguments\n", 29);
			return ;
		}
		assign_arguments_to_philo_table(philo_table, atol_value, i);
		i++;
	}
	if (check_philos_number(philo_table->num_of_philos) == false)
		return ;
	philo_table->table_assigned = true;
}
