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

static void destroy_philo_table(t_philo_table *philo_table)
{
	// destroy_threads(philo_table);
	if (philo_table->philos)
		free(philo_table->philos);
}

static bool init_philo_table(t_philo_table *philo_table)
{
	philo_table->philos = malloc(sizeof(t_philo_thread) * philo_table->num_of_philos);
	if (!philo_table->philos)
	{
		write(2, "Error: malloc failed\n", 22);
		return (false);
	}
	for (int i = 0; i < philo_table->num_of_philos; i++)
	{
		philo_table->philos[i].id = i + 1;
		if (pthread_create(&philo_table->philos[i].thread, NULL, &philo_routine, &philo_table->philos[i]))
		{
			write(2, "Error: pthread_create failed\n", 30);
			destroy_philo_table(philo_table);
			return (false);
		}
	}
	return (true);
}

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
	if (init_philo_table(&philo_table) == false)
		return (1);
//	init_mutex(&philo_table);
//	launch_philo_threads(&philo_table);
	return (0);
}
