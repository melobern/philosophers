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

static bool	init_philo_table(t_philo_table *table)
{
	int	i;
	unsigned int	time;

	i = 0;
	time = get_time_in_ms();
	table->a_philo_has_died = false;
	table->philos = ft_calloc(table->num_of_philos, sizeof(t_philo_thread));
	if (!table->philos)
	{
		write(2, "Error: malloc failed at init_philo_table\n", 41);
		return (false);
	}
	while (i < table->num_of_philos)
	{
		table->philos[i].id = i + 1;
		table->philos[i].is_eating = false;
		table->philos[i].meals_eaten = 0;
		table->philos[i].last_meal = time;
		table->philos[i].is_dead = &(table->a_philo_has_died);
		table->philos[i].write_mutex = &(table->write_mutex);
		if (i < table->num_of_philos - 1)
			table->philos[i].right_fork = &(table->philos[i + 1].left_fork);
		else
			table->philos[i].right_fork = &(table->philos[0].left_fork);
		if (i < table->num_of_philos - 1)
			table->philos[i].right_fork_taken = &(table->philos[i + 1].left_fork_taken);
		else
			table->philos[i].right_fork_taken = &(table->philos[0].left_fork_taken);
		table->philos[i].dinner_started = &(table->dinner_started);
		printf("philo id: %d\n", table->philos[i].id);
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

static void	launch_diner(t_philo_table *philo_table)
{
	int	i;

	i = 0;

	philo_table->dinner_started = false;
	while (i < philo_table->num_of_philos)
	{
		if (pthread_create(&philo_table->philos[i].thread, NULL, &routine, &philo_table->philos[i]))
		{
			write(2, "Error: pthread_create failed\n", 30);
//			destroy_philo_table(philo_table);
			return ;
//			return (false);
		}
		pthread_mutex_init(&philo_table->philos[i].mutex, NULL);
		i++;
	}
	philo_table->dinner_started = true;
}

bool	init_mutex(t_philo_table *philo_table)
{
	int	i;

	i = 0;
	if (pthread_mutex_init(&(philo_table->write_mutex), NULL))
	{
		write(2, "Error: pthread_mutex_init failed\n", 34);
		return (false);
	}
	while (i < philo_table->num_of_philos)
	{
		pthread_mutex_init(&(philo_table->philos[i].death_mutex), NULL);
		pthread_mutex_init(&(philo_table->philos[i].left_fork), NULL);
		pthread_mutex_init(philo_table->philos[i].right_fork, NULL);
		i++;
	}
	return (true);
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
	if (init_mutex(&philo_table))
		launch_diner(&philo_table);
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
