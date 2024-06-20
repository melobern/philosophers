/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbernard <mbernard@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 14:05:49 by mbernard          #+#    #+#             */
/*   Updated: 2024/06/14 10:56:04 by mbernard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	assign_bool_mutex(bool *var, pthread_mutex_t *m, bool val)
{
	bool	flag;

	flag = true;
	pthread_mutex_lock(m);
	if (*var != val)
		*var = val;
	else
		flag = false;
	pthread_mutex_unlock(m);
	return (flag);
}

bool	no_death_detected(t_philo_thread *p)
{
	bool	flag;

	flag = false;
	if (p->last_meal + p->die_time < get_time_in_ms())
		print_msg(p, DIED, 1, 0);
	pthread_mutex_lock(p->death_mutex);
	if (*(p->dead_detected) == false)
		flag = true;
//	printf("HELLOOOOOO ==== %d\n", flag);
	pthread_mutex_unlock(p->death_mutex);
	return (flag);
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
			table->philos[i].mutex_created = false;
			return (false);
		}
		table->philos[i].mutex_created = true;
		i++;
	}
	return (true);
}

static bool	init_table_mutex(pthread_mutex_t *m, char *mutex_name, size_t len)
{
	if (pthread_mutex_init(m, NULL))
	{
		write(2, "Error: pthread_mutex_init of ", 29);
		write(2, mutex_name, len);
		write(2, " failed\n", 8);
		return (false);
	}
	return (true);
}

bool	init_mutex(t_table *t)
{
	bool	result;

	if (!init_table_mutex(&(t->write_mutex), "write_mutex", 11))
		return (false);
	if (!init_table_mutex(&(t->death_mutex), "death_mutex", 11))
	{
		pthread_mutex_destroy(&(t->write_mutex));
		return (false);
	}
	if (!init_table_mutex(&(t->meals_mutex), "meals_mutex", 11))
	{
		pthread_mutex_destroy(&(t->write_mutex));
		pthread_mutex_destroy(&(t->death_mutex));
		return (false);
	}
	if (!init_table_mutex(&(t->errors_mutex), "errors_mutex", 12))
	{
		pthread_mutex_destroy(&(t->write_mutex));
		pthread_mutex_destroy(&(t->death_mutex));
		pthread_mutex_destroy(&(t->meals_mutex));
		return (false);
	}
	t->mutex_created = true;
	result = init_left_fork_mutex(t);
	return (result);
}