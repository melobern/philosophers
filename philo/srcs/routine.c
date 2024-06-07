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

	philo = (t_philo_thread *)arg;
	printf("philo id: %d\n", philo->id);
	while (philo->dinner_started == false)
		;
	//philo->start_time = get_time_in_ms();
	return (NULL);
}
