/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   messages.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbernard <mbernard@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 13:19:55 by mbernard          #+#    #+#             */
/*   Updated: 2024/06/06 13:19:55 by mbernard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_message(t_philo_table *table, t_philo_thread *philo, char *msg)
{
	unsigned int	time;

	time = get_time_in_ms();
	pthread_mutex_lock(&table->write_mutex);
	printf("%u %d %s\n", time - table->start_time, philo->id, msg);
	pthread_mutex_unlock(&table->write_mutex);
}
