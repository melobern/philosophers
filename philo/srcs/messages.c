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

<<<<<<< Updated upstream
void	print_message(t_philo_thread *philo, char *msg)
=======
void	print_msg(t_table *table, t_philo_thread *philo, char *msg)
>>>>>>> Stashed changes
{
	unsigned long	time;

	time = get_time_in_ms();
	pthread_mutex_lock(philo->write_mutex);
	printf("%lu %d %s", time - *(philo->start_time), philo->id, msg);
	pthread_mutex_unlock(philo->write_mutex);
}
