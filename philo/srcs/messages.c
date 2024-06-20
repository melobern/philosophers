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
		pthread_mutex_lock(p->meals_mutex);
		if (p->table->finished_meals == p->num_of_philos)
		{
			pthread_mutex_unlock(p->meals_mutex);
			return (true);
		}
		pthread_mutex_unlock(p->meals_mutex);
	}
	return (false);
}

void	print_msg(t_philo_thread *p, char *msg, bool is_dead, bool is_eat)
{
	pthread_mutex_lock(p->death_mutex);
	if (*(p->dead_detected) == true)
	{
		pthread_mutex_unlock(p->death_mutex);
		return ;
	}
	if (is_dead)
		*(p->dead_detected) = true;
	pthread_mutex_unlock(p->death_mutex);
	if (is_eat && p->meals_defined && p->meals_eaten == p->meals_num - 1)
		usleep(1000);
	if (is_dead)
		ft_usleep(3, NULL);
	if (everyone_has_eaten(p))
		return ;
	pthread_mutex_lock(p->write_mutex);
	if (is_dead || no_death_detected(p))
		printf("%lu\t%d\t%s", get_time_in_ms() - p->start_time, p->id, msg);
	pthread_mutex_unlock(p->write_mutex);
	if (is_eat)
		p->last_meal = get_time_in_ms();
}
