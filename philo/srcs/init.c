/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbernard <mbernard@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 18:57:26 by mbernard          #+#    #+#             */
/*   Updated: 2024/06/07 08:31:29 by mbernard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	assign_table(t_table *t, int i, unsigned int time)
{
	t->philos[i].id = i + 1;
	t->philos[i].is_eating = false;
	t->philos[i].meals_eaten = 0;
	t->philos[i].last_meal = time;
	t->philos[i].start_time = &(t->start_time);
	t->philos[i].is_dead = false;
	t->philos[i].dead_detected = &(t->dead_detected);
	t->philos[i].write_mutex = &(t->write_mutex);
	t->philos[i].dinner_started = &(t->dinner_started);
	t->philos[i].meals_defined = &(t->meals_defined);
	t->philos[i].meals_num = t->meals_num;
	t->philos[i].left_fork_taken = false;
	if (i < t->num_of_philos - 1)
	{
		t->philos[i].right_fork = &(t->philos[i + 1].left_fork);
		t->philos[i].right_fork_taken = &(t->philos[i + 1].left_fork_taken);
	}
	else
	{
		t->philos[i].right_fork = &(t->philos[0].left_fork);
		t->philos[i].right_fork_taken = &(t->philos[0].left_fork_taken);
	}
}

bool	init_philo_table(t_table *table)
{
	int				i;
	unsigned int	time;

	i = 0;
	time = get_time_in_ms();
	table->dead_detected = false;
	table->philos = ft_calloc(table->num_of_philos, sizeof(t_philo_thread));
	if (!table->philos)
	{
		write(2, "Error: malloc failed at init_philo_table\n", 41);
		return (false);
	}
	while (i < table->num_of_philos)
	{
		assign_table(table, i, time);
		i++;
	}
	return (true);
}
