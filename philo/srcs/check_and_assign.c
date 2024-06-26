/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_and_assign.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbernard <mbernard@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 13:22:26 by mbernard          #+#    #+#             */
/*   Updated: 2024/06/05 14:11:03 by mbernard         ###   ########.fr       */
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
	while (str[i])
	{
		if ((str[i] < '0' || str[i] > '9')
			&& !((str[i] > 8 && str[i] < 14) || str[i] == 32))
			return (-3);
		i++;
	}
	if (str[0] && str[0] == '-')
		return (-1);
	return ((int)nb);
}

static void	assign_arguments_to_philo_table(t_table *t, int num, int var)
{
	if (var == 1)
		t->num_of_philos = num;
	else if (var == 2)
		t->die_time = num;
	else if (var == 3)
		t->eat_time = num;
	else if (var == 4)
		t->sleep_time = num;
	else if (var == 5)
	{
		t->meals_num = num;
		t->meals_defined = true;
	}
}

static bool	check_philos_number(t_table *t, int num_of_philos)
{
	if (num_of_philos > 0 && num_of_philos <= 200
		&& t->die_time > 59 && t->eat_time > 59 && t->sleep_time > 59
		&& (t->meals_defined == 0 || t->meals_num > 0))
		return (true);
	if (num_of_philos > 200)
		write(2, PHILO_200_ERROR, 67);
	else if (num_of_philos == 0)
		write(2, PHILO_0_ERROR, 65);
	if (t->die_time < 60)
		write(2, TIME_TO_DIE_ERROR, 55);
	if (t->eat_time < 60)
		write(2, TIME_TO_EAT_ERROR, 55);
	if (t->sleep_time < 60)
		write(2, TIME_TO_SLEEP_ERROR, 57);
	if (t->meals_defined && t->meals_num == 0)
		write(2, NUMBER_OF_MEALS_ERROR, 58);
	return (false);
}

bool	check_arguments_and_assign(char **av, t_table *t)
{
	int	i;
	int	atol_value;

	i = 1;
	t->meals_defined = false;
	while (av[i])
	{
		atol_value = ft_atol_int(av[i]);
		if (atol_value < 0)
		{
			if (atol_value == -1)
				write(2, "Error: arguments must be positive integers\n", 43);
			if (atol_value == -2)
				write(2, "Error: overflow in arguments\n", 29);
			if (atol_value == -3)
				write(2, "Error: arguments must be integers\n", 35);
			return (false);
		}
		assign_arguments_to_philo_table(t, atol_value, i);
		i++;
	}
	if (check_philos_number(t, t->num_of_philos) == false)
		return (false);
	t->dead_detected = false;
	return (true);
}
