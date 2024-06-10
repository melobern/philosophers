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
	if (*var == value)
		return (false);
	if (pthread_mutex_lock(mutex))
	{
		write(2, "Error: mutex lock failed\n", 25);
		return (-1);
	}
	*var = value;
	if (pthread_mutex_unlock(mutex))
	{
		write(2, "Error: mutex unlock failed\n", 27);
		return (-1);
	}
	return (true);
}
