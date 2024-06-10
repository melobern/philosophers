/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbernard <mbernard@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 08:44:55 by mbernard          #+#    #+#             */
/*   Updated: 2024/06/07 19:26:42 by mbernard         ###   ########.fr       */
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

bool wait_dinner(t_philo_thread *philo, u_int64_t time)
{
	u_int64_t	limit_time;

	while (1)
	{
		if (time == 1 || mutex_lock(philo->write_mutex) == false)
			return (false);
		if (*philo->dinner_started == true)
		{
			if (mutex_unlock(philo->write_mutex) == false)
				return (false);
			break ;
		}
		if (*(philo->error_detected) == true)
		{
			if (mutex_unlock(philo->write_mutex) == false)
				return (false);
			return (false);
		}
		if (mutex_unlock(philo->write_mutex) == false)
			return (false);
		limit_time = get_time_in_ms();
		if (time + 100 < limit_time || limit_time == 1)
			return (false);
	}
	return (true);
}

void	*routine(void *arg)
{
	t_philo_thread	*philo;

	if (!arg || !wait_dinner((t_philo_thread *) arg, get_time_in_ms()))
		return (NULL);
	philo = (t_philo_thread *)arg;
/*	while (1)
	{
		pthread_mutex_lock(philo->write_mutex);
		if (*philo->dinner_started == true)
		{
			pthread_mutex_unlock(philo->write_mutex);
			break ;
		}
		if (*(philo->error_detected) == true)
		{
			pthread_mutex_unlock(philo->write_mutex);
			return (NULL);
		}
		pthread_mutex_unlock(philo->write_mutex);
		limit_time = get_time_in_ms();
		if (time + 100 < limit_time || limit_time == 1)
			return (NULL);
	}*/
	print_message(philo, THINK);
	while (*(philo->dead_detected) == false
		&& (philo->meals_defined == false
			|| philo->meals_eaten < philo->meals_num))
	{
//		if (philo->id % 2 == 0)
//			eat(philo);
//		else
//			eat(philo);
		print_message(philo, SLEEP);
		print_message(philo, FORK);
		print_message(philo, EAT);
		print_message(philo, THINK);
		philo->meals_eaten++;
		if (philo->id % 2 == 0)
			ft_usleep(1);
	}
	return (NULL);
}
