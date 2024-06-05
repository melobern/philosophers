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

int	main(int ac, char **av)
{
	t_philo_table	philo_table;

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
