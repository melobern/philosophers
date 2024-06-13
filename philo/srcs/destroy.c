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

static void	destroy_threads(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->num_of_philos && table->philos[i].thread_created)
	{
		if (pthread_join(table->philos[i].thread, NULL))
			write(2, "Error: pthread_join failed\n", 28);
		i++;
	}
}

void	destroy_philo_table(t_table *table)
{
	int	i;

	i = 0;
	destroy_threads(table);
	while (i < table->num_of_philos && table->philos[i].mutex_created)
	{
		pthread_mutex_destroy(&(table->philos[i].l_fork));
		i++;
	}
	pthread_mutex_destroy(&(table->write_mutex));
	pthread_mutex_destroy(&(table->death_mutex));
	free(table->philos);
	table->philos = NULL;
}
