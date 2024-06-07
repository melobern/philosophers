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

void	*routine(void *arg)
{
	t_philo_thread	*philo;

	philo = (t_philo_thread *)arg;
	while (philo->dinner_started == false)
		;
	while (*(philo->dead_detected) == false
		&& (philo->meals_defined == false
			|| philo->meals_eaten < philo->num_of_meals))
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
