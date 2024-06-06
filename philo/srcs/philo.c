/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbernard <mbernard@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 12:02:33 by mbernard          #+#    #+#             */
/*   Updated: 2024/06/06 11:03:03 by mbernard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	destroy_philo_table(t_philo_table *philo_table)
{
//	int i;
//
//	i = 0;
//	while (i < philo_table->num_of_philos)
//	{
//		pthread_join(philo_table->philos[i].thread, NULL);
//		pthread_mutex_destroy(&philo_table->philos[i].mutex);
//		i++;
//	}
	// destroy_threads(philo_table);

	free(philo_table->philos);
}

static bool	init_philo_table(t_philo_table *philo_table)
{
	int	i;
	unsigned int	time;

	i = 0;
	time = get_time_in_ms();
	philo_table->philos = ft_calloc(philo_table->num_of_philos, sizeof(t_philo_thread));
	if (!philo_table->philos)
	{
		write(2, "Error: malloc failed at init_philo_table\n", 41);
		return (false);
	}
	while (i < philo_table->num_of_philos)
	{
		philo_table->philos[i].id = i;
		philo_table->philos[i].is_dead = false;
		philo_table->philos[i].is_eating = false;
		philo_table->philos[i].meals_eaten = 0;
		philo_table->philos[i].last_meal = time;
		i++;
	}
	return (true);
}

static void	Print_to_erase(t_philo_table *philo_table)
{
	printf("num_of_philos: %d\n", philo_table->num_of_philos);
	printf("time_to_die: %d\n", philo_table->time_to_die);
	printf("time_to_eat: %d\n", philo_table->time_to_eat);
	printf("time_to_sleep: %d\n", philo_table->time_to_sleep);
	if (philo_table->meals_defined)
		printf("number_of_meals: %d\n", philo_table->number_of_meals);
}

int	main(int ac, char **av)
{
	t_philo_table	philo_table;

	if (ac < 5 || ac > 6)
	{
		write(2, WRONG_NUMBER_OF_ARGUMENTS, 188);
		return (1);
	}
	if (check_arguments_and_assign(av, &philo_table) == false)
		return (1);
	Print_to_erase(&philo_table);
	if (init_philo_table(&philo_table) == false)
		return (1);

//	init_mutex(&philo_table);
//	launch_philo_threads(&philo_table);
/*
 * 		if (pthread_create(&philo_table->philos[i].thread, NULL, &routine, &philo_table->philos[i]))
		{
			write(2, "Error: pthread_create failed\n", 30);
			destroy_philo_table(philo_table);
			return (false);
		}
		pthread_mutex_init(&philo_table->philos[i].mutex, NULL);
*/
	destroy_philo_table(&philo_table);
	return (0);
}
