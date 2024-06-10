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

bool	wait_dinner(t_philo_thread *philo, u_int64_t time)
{
	u_int64_t	limit_time;

	if (time == 1)
		return (false);
	while (1)
	{
		if (mutex_lock(philo->write_mutex) == false)
			return (false);
		if (*philo->dinner_started == true)
		{
			if (mutex_unlock(philo->write_mutex) == false)
				return (false);
			return (true);
		}
		if (*(philo->error_detected) == true)
		{
			mutex_unlock(philo->write_mutex);
			return (false);
		}
		if (mutex_unlock(philo->write_mutex) == false)
			return (false);
		limit_time = get_time_in_ms();
		if (time + 100 < limit_time || limit_time == 1)
			return (false);
	}
}

void	*routine(void *arg)
{
	t_philo_thread	*philo;

	if (!arg || !wait_dinner((t_philo_thread *) arg, get_time_in_ms()))
		return (NULL);
	philo = (t_philo_thread *)arg;
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
