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

void	print_message(t_philo_thread *p, char *msg, bool is_death)
{
	u_int64_t time;

	time = get_time_in_ms();
	pthread_mutex_lock(p->death_mutex);
	if (*(p->dead_detected) == true)
	{
		pthread_mutex_unlock(p->death_mutex);
		return ;
	}

	if (is_death)
	{
		*(p->dead_detected) = true;
		ft_usleep(1);
	}
	pthread_mutex_unlock(p->death_mutex);
	pthread_mutex_lock(p->write_mutex);
	printf("%lu\t%d\t%s", time - *(p->start_time), p->id, msg);
	pthread_mutex_unlock(p->write_mutex);
}
