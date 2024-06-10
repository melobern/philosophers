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

static void	launch_diner(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->num_of_philos)
	{
		if (pthread_create(&table->philos[i].thread,
				NULL,
				&routine,
				&table->philos[i]))
		{
			write(2, "Error: pthread_create failed\n", 30);
			*table->philos[i].error_detected = true;
			return ;
		}
		table->philos[i].thread_created = true;
		i++;
	}
	if (assign_bool_mutex(&table->dinner_started,
						  &table->write_mutex,
						  true) == false)
		return ;
}

int	main(int ac, char **av)
{
	t_table	table;

	if (ac < 5 || ac > 6)
	{
		write(2, WRONG_NUMBER_OF_ARGUMENTS, 180);
		return (1);
	}
	if (check_arguments_and_assign(av, &table) == false)
		return (1);
	if (table.num_of_philos == 1)
	{
		printf("0 1 has taken a fork\n");
		ft_usleep(table.die_time);
		printf("%u 1 died\n", table.die_time + 1);
		return (0);
	}
	if (init_philo_table(&table) == false)
		return (1);
	if (init_mutex(&table))
		launch_diner(&table);
	destroy_philo_table(&table);
	return (0);
}
