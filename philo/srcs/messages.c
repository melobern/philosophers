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

bool	everyone_has_eaten(t_philo_thread *p)
{
	if (p->meals_defined)
	{
		pthread_mutex_lock(p->death_mutex);
		if (p->table->finished_meals == p->num_of_philos)
		{
			pthread_mutex_unlock(p->death_mutex);
			return (true);
		}
		pthread_mutex_unlock(p->death_mutex);
	}
	return (false);
}

void	print_msg(t_philo_thread *p, char *msg, bool is_dead, bool is_eat)
{
	u_int64_t	time;

	time = get_time_in_ms();
	pthread_mutex_lock(p->death_mutex);
	if (*(p->dead_detected) == true)
	{
		pthread_mutex_unlock(p->death_mutex);
		return ;
	}
	if (is_dead)
		*(p->dead_detected) = true;
	pthread_mutex_unlock(p->death_mutex);
	if (is_eat)
		ft_usleep(1);
	if (is_dead)
		ft_usleep(2);
	if (everyone_has_eaten(p))
		return ;
	pthread_mutex_lock(p->write_mutex);
	printf("%lu\t%d\t%s", time - *(p->start_time), p->id, msg);
	pthread_mutex_unlock(p->write_mutex);
}
