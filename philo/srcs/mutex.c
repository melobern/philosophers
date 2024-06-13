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

bool	mutex_lock(pthread_mutex_t *mutex)
{
	if (pthread_mutex_lock(mutex))
	{
		write(2, "Error: mutex lock failed\n", 25);
		return (false);
	}
	return (true);
}

bool	mutex_unlock(pthread_mutex_t *mutex)
{
	if (pthread_mutex_unlock(mutex))
	{
		write(2, "Error: mutex unlock failed\n", 27);
		return (false);
	}
	return (true);
}

int	assign_bool_mutex(bool *var, pthread_mutex_t *mutex, bool value)
{
	bool flag;

	flag = true;
	if (pthread_mutex_lock(mutex))
	{
		write(2, "Error: mutex lock failed\n", 25);
		return (-1);
	}
	if (*var != value)
		*var = value;
	else
		flag = false;
	if (pthread_mutex_unlock(mutex))
	{
		write(2, "Error: mutex unlock failed\n", 27);
		return (-1);
	}
	return (flag);
}

bool	mutex_check_if_can_eat(t_philo_thread *p)
{
	bool flag;

	flag = false;
//	if (p->is_eating == false
//		&& (p->meals_defined == false || p->meals_eaten <= p->meals_num))
if (p->meals_defined == false || p->meals_eaten <= p->meals_num)
{
		if (pthread_mutex_lock(p->death_mutex))
		{
			write(2, "Error: mutex lock failed\n", 25);
			return (false);
		}
		if (*(p->dead_detected) == false)
			flag = true;
		if (pthread_mutex_unlock(p->death_mutex))
		{
			write(2, "Error: mutex lock failed\n", 25);
			return (false);
		}
	}
	return (flag);
}