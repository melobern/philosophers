/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbernard <mbernard@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 14:05:49 by mbernard          #+#    #+#             */
/*   Updated: 2024/06/14 10:56:04 by mbernard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	assign_bool_mutex(bool *var, pthread_mutex_t *m, bool val)
{
	bool	flag;

	flag = true;
	pthread_mutex_lock(m);
	if (*var != val)
		*var = val;
	else
		flag = false;
	pthread_mutex_unlock(m);
	return (flag);
}

bool	no_death_detected(t_philo_thread *p)
{
	bool	flag;

	flag = false;
	if (p->last_meal + p->die_time < get_time_in_ms())
		print_msg(p, DIED, 1, 0);
	pthread_mutex_lock(p->death_mutex);
	if (*(p->dead_detected) == false)
		flag = true;
	pthread_mutex_unlock(p->death_mutex);
	return (flag);
}
