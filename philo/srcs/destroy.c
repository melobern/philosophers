/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destroy.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbernard <mbernard@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 08:40:29 by mbernard          #+#    #+#             */
/*   Updated: 2024/06/07 08:40:29 by mbernard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	destroy_threads(t_philo_table *philo_table)
{
	int	i;

	i = 0;
	while (i < philo_table->num_of_philos)
	{
		if (pthread_join(philo_table->philos[i].thread, NULL))
			write(2, "Error: pthread_join failed\n", 28);
		i++;
	}
}

void	destroy_philo_table(t_philo_table *philo_table)
{
	int	i;

	i = 0;
	destroy_threads(philo_table);
	while (i < philo_table->num_of_philos)
	{
		pthread_mutex_destroy(&(philo_table->philos[i].death_mutex));
		pthread_mutex_destroy(&(philo_table->philos[i].left_fork));
		i++;
	}
	pthread_mutex_destroy(&(philo_table->write_mutex));
	free(philo_table->philos);
}
