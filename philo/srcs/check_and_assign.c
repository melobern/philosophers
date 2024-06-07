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

static void	assign_arguments_to_philo_table(t_philo_table *p, int num, int var)
{
	if (var == 1)
		p->num_of_philos = num;
	else if (var == 2)
		p->die_time = num;
	else if (var == 3)
		p->eat_time = num;
	else if (var == 4)
		p->sleep_time = num;
	else if (var == 5)
	{
		p->num_of_meals = num;
		p->meals_defined = true;
	}
}

static bool	check_philos_number(t_philo_table *t, int num_of_philos)
{
	if (num_of_philos > 1 && num_of_philos <= 200
		&& t->die_time > 59 && t->eat_time > 59 && t->sleep_time > 59
		&& (t->meals_defined == 0 || t->num_of_meals > 0))
		return (true);
	if (num_of_philos == 1 && t->die_time > 59 && t->eat_time > 59
		&& t->sleep_time > 59 && (t->meals_defined == 0 || t->num_of_meals > 0))
	{
		printf("%lu 1 has taken a fork\n", get_time_in_ms());
		ft_usleep(t->die_time);
		printf("%lu 1 died\n", get_time_in_ms());
		return (false);
	}
	if (num_of_philos > 200)
		write(2, PHILO_200_ERROR, 56);
	else if (num_of_philos == 0)
		write(2, "Error: number of philosophers should be superior to 0\n", 54);
	if (t->die_time < 60)
		write(2, "Error: time to die should be superior to 59\n", 44);
	if (t->eat_time < 60)
		write(2, "Error: time to eat should be superior to 59\n", 44);
	if (t->sleep_time < 60)
		write(2, "Error: time to sleep should be superior to 59\n", 46);
	if (t->meals_defined && t->num_of_meals == 0)
		write(2, "Error: number of meals should be superior to 0\n", 47);
	return (false);
}

bool	check_arguments_and_assign(char **av, t_philo_table *p)
{
	int	i;
	int	atol_value;

	i = 1;
	p->meals_defined = false;
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
		assign_arguments_to_philo_table(p, atol_value, i);
		i++;
	}
	if (check_philos_number(p, p->num_of_philos) == false)
		return (false);
	p->a_philo_has_died = false;
	return (true);
}
