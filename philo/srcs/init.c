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

static void	assign_forks(t_table *t, int i)
{
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

static void	assign_table(t_table *t, int i, u_int64_t time)
{
	t->philos[i].id = i + 1;
	t->philos[i].is_eating = false;
	t->philos[i].meals_eaten = 0;
	t->philos[i].last_meal = time;
	t->philos[i].num_forks = 0;
	t->philos[i].start_time = &(t->start_time);
	t->philos[i].is_dead = false;
	t->philos[i].dead_detected = &(t->dead_detected);
	t->philos[i].error_detected = &(t->error_detected);
	t->philos[i].write_mutex = &(t->write_mutex);
	t->philos[i].dinner_started = &(t->dinner_started);
	t->philos[i].meals_defined = &(t->meals_defined);
	t->philos[i].meals_num = t->meals_num;
	t->philos[i].eat_time = t->eat_time;
	t->philos[i].sleep_time = t->sleep_time;
	t->philos[i].die_time = t->die_time;
	t->philos[i].l_fork_taken = false;
	t->philos[i].thread_created = false;
	assign_forks(t, i);
}

bool	init_philo_table(t_table *table)
{
	int				i;
	u_int64_t	time;

	i = 0;
	time = get_time_in_ms();
	table->dead_detected = false;
	table->dinner_started = false;
	table->error_detected = false;
	table->start_time = time;
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

static bool	init_left_and_death_mutex(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->num_of_philos)
	{
		if (pthread_mutex_init(&(table->philos[i].death_mutex), NULL))
		{
			write(2, "Error: pthread_mutex_init of death_mutex failed\n", 48);
			table->philos[i].mutex_created = false;
			return (false);
		}
		if (pthread_mutex_init(&(table->philos[i].l_fork), NULL))
		{
			write(2, "Error: pthread_mutex_init of fork_mutex failed\n", 47);
			pthread_mutex_destroy(&(table->philos[i].death_mutex));
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
	if (pthread_mutex_init(&(table->write_mutex), NULL))
	{
		write(2, "Error: pthread_mutex_init of write_mutex failed\n", 48);
		return (false);
	}
	result = init_left_and_death_mutex(table);
	return (result);
}
