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
<<<<<<< Updated upstream
	while (*(philo->dead_detected) == false
		&& (philo->meals_defined == false
			|| philo->meals_eaten < philo->num_of_meals))
=======
	pthread_mutex_lock(philo->write_mutex);
	printf("%u %d %s", time - philo->start_time, philo->id, SLEEP);
	pthread_mutex_unlock(philo->write_mutex);
//	if (philo->id % 2 == 0)
//		ft_usleep(1);
	//philo->start_time = get_time_in_ms();
	while (philo->dead_detected == 0
		&& (philo->meals_defined == 0 || philo->meals_eaten < philo->meals_num))
>>>>>>> Stashed changes
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
