/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbernard <mbernard@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 12:02:33 by mbernard          #+#    #+#             */
/*   Updated: 2024/06/07 08:31:29 by mbernard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

//static void	Print_to_erase(t_table *philo_table)
//{
//	printf("num_of_philos: %d\n", philo_table->num_of_philos);
//	printf("die_time: %d\n", philo_table->die_time);
//	printf("eat_time: %d\n", philo_table->eat_time);
//	printf("sleep_time: %d\n", philo_table->sleep_time);
//	if (philo_table->meals_defined)
//		printf("meals_num: %d\n", philo_table->meals_num);
//}

static void	launch_diner(t_table *philo_table)
{
	int	i;

	i = 0;
	philo_table->dinner_started = false;
	philo_table->dead_detected = false;
	while (i < philo_table->num_of_philos)
	{
		if (pthread_create(&philo_table->philos[i].thread,
				NULL,
				&routine,
				&philo_table->philos[i]))
		{
			write(2, "Error: pthread_create failed\n", 30);
			return ;
		}
		i++;
	}
	philo_table->dinner_started = true;
}

bool	init_mutex(t_table *philo_table)
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
		if (pthread_mutex_init(&(philo_table->philos[i].death_mutex), NULL)
			|| pthread_mutex_init(&(philo_table->philos[i].left_fork), NULL))
		{
			write(2, "Error: pthread_mutex_init failed\n", 34);
			return (false);
		}
		i++;
	}
	return (true);
}

int	main(int ac, char **av)
{
	t_table	philo_table;

	if (ac < 5 || ac > 6)
	{
		write(2, WRONG_NUMBER_OF_ARGUMENTS, 180);
		return (1);
	}
	if (check_arguments_and_assign(av, &philo_table) == false)
		return (1);
	if (philo_table.num_of_philos == 1)
	{
		write(1, "000000 1 has taken a fork\n", 26);
		ft_usleep(philo_table.die_time);
		printf("0000%u 1 died\n", philo_table.die_time + 1);
		return (0);
	}
	if (init_philo_table(&philo_table) == false)
		return (1);
	if (init_mutex(&philo_table))
		launch_diner(&philo_table);
	destroy_philo_table(&philo_table);
	return (0);
}
