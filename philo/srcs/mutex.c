/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbernard <mbernard@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 14:05:49 by mbernard          #+#    #+#             */
/*   Updated: 2024/06/10 15:47:15 by mbernard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	assign_bool_mutex(bool *var, pthread_mutex_t *m, bool value)
{
	bool flag;

	flag = true;

	pthread_mutex_lock(m);
	if (*var != value)
		*var = value;
	else
		flag = false;
	pthread_mutex_unlock(m);
	return (flag);
}

bool	mutex_check_if_can_eat(t_philo_thread *p)
{
	bool flag;

	flag = false;
	//	if (p->is_eating == false
	//		&& (p->meals_defined == false || p->meals_eaten <= p->meals_num))
	if (p->meals_defined == false || p->meals_eaten < p->meals_num)
	{
			pthread_mutex_lock(p->death_mutex);
			if (*(p->dead_detected) == false)
				flag = true;
			pthread_mutex_unlock(p->death_mutex);
		}
	return (flag);
}