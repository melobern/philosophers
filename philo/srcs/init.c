/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbernard <mbernard@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 18:57:26 by mbernard          #+#    #+#             */
/*   Updated: 2024/06/14 13:04:28 by mbernard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	assign_forks(t_table *t, int i)
{
	t->philos[i].num_forks = 0;
	t->philos[i].l_fork_taken = false;
	if (i < t->num_of_philos - 1)
	{
		t->philos[i].r_fork = &(t->philos[i + 1].l_fork);
		t->philos[i].r_fork_taken = &(t->philos[i + 1].l_fork_taken);
	}
	else
	{
		t->philos[i].r_fork = &(t->philos[0].l_fork);
		t->philos[i].r_fork_taken = &(t->philos[0].l_fork_taken);
	}
}

static void	assign_philos(t_table *t, int i)
{
	t->philos[i].id = i + 1;
	t->philos[i].meals_eaten = 0;
//	t->philos[i].start_time = &(t->start_time);
	t->philos[i].dead_detected = &(t->dead_detected);
	t->philos[i].error_detected = &(t->error_detected);
	t->philos[i].write_mutex = &(t->write_mutex);
	t->philos[i].death_mutex = &(t->death_mutex);
	t->philos[i].meals_mutex = &(t->meals_mutex);
	t->philos[i].errors_mutex = &(t->errors_mutex);
	t->philos[i].dinner_started = &(t->dinner_started);
	t->philos[i].num_of_philos = t->num_of_philos;
	t->philos[i].meals_defined = t->meals_defined;
	t->philos[i].meals_num = t->meals_num;
	t->philos[i].eat_time = t->eat_time;
	t->philos[i].sleep_time = t->sleep_time;
	t->philos[i].die_time = t->die_time;
	t->philos[i].thread_created = false;
	t->philos[i].table = t;
	assign_forks(t, i);
}

bool	init_table(t_table *table)
{
	int			i;

	i = 0;
	table->dead_detected = false;
	table->dinner_started = false;
	table->error_detected = false;
	table->finished_meals = 0;
	table->philos = ft_calloc(table->num_of_philos, sizeof(t_philo_thread));
	if (!table->philos)
	{
		write(2, "Error: malloc failed at init_table\n", 41);
		return (false);
	}
	while (i < table->num_of_philos)
	{
		assign_philos(table, i);
		i++;
	}
	return (true);
}

static bool	init_left_fork_mutex(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->num_of_philos)
	{
		if (pthread_mutex_init(&(table->philos[i].l_fork), NULL))
		{
			write(2, "Error: pthread_mutex_init of fork_mutex failed\n", 47);
//			pthread_mutex_destroy(table->philos[i].death_mutex);
//			pthread_mutex_destroy(table->philos[i].meals_mutex);
			table->philos[i].mutex_created = false;
			return (false);
		}
		table->philos[i].mutex_created = true;
		i++;
	}
	return (true);
}

bool	init_mutex(t_table *table)
{
	bool	result;

	if (pthread_mutex_init(&(table->write_mutex), NULL))
	{
		write(2, "Error: pthread_mutex_init of write_mutex failed\n", 48);
		return (false);
	}
	if (pthread_mutex_init(&(table->death_mutex), NULL))
	{
		write(2, "Error: pthread_mutex_init of write_mutex failed\n", 48);
		return (false);
	}
	if (pthread_mutex_init(&(table->meals_mutex), NULL))
	{
		write(2, "Error: pthread_mutex_init of meals_mutex failed\n", 48);
		return (false);
	}
	if (pthread_mutex_init(&(table->errors_mutex), NULL))
	{
		write(2, "Error: pthread_mutex_init of errors_mutex failed\n", 49);
		return (false);
	}
	result = init_left_fork_mutex(table);
	return (result);
}
