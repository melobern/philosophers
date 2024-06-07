/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbernard <mbernard@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 08:44:55 by mbernard          #+#    #+#             */
/*   Updated: 2024/06/06 08:44:55 by mbernard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*routine(void *arg)
{
	t_philo_thread	*philo;
//	unsigned int	time;

	philo = (t_philo_thread *)arg;
//	time = get_time_in_ms();
//	write(1, "routine\n", 8);
	//printf("philo id: %d\n", philo->id);
	while (philo->dinner_started == false)
		;
	pthread_mutex_lock(philo->write_mutex);
//	printf("%d %s", philo->id, SLEEP);
//	printf("%lu %d %s\n", get_time_in_ms(), philo->id, SLEEP);
	printf("%lu %d %s", get_time_in_ms() - philo->start_time, philo->id, SLEEP);
	pthread_mutex_unlock(philo->write_mutex);
//	if (philo->id % 2 == 0)
//		ft_usleep(1);
	//philo->start_time = get_time_in_ms();
	while (philo->dead_detected == false
		&& (philo->meals_defined == false || philo->meals_eaten < philo->num_of_meals))
	{
//		if (philo->id % 2 == 0)
//			eat(philo);
//		else
//			eat(philo);
		if (philo->id % 2 == 0)
			ft_usleep(1);
	}
	return (NULL);
}
