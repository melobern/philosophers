/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbernard <mbernard@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 08:44:55 by mbernard          #+#    #+#             */
/*   Updated: 2024/06/14 13:04:31 by mbernard         ###   ########.fr       */
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
		pthread_mutex_lock(philo->death_mutex);
		if (*(philo->error_detected) == true)
		{
			pthread_mutex_unlock(philo->death_mutex);
			return (false);
		}
		if (*philo->dinner_started == true)
		{
			pthread_mutex_unlock(philo->death_mutex);
			return (true);
		}
		pthread_mutex_unlock(philo->death_mutex);
		limit_time = get_time_in_ms();
		if (time + 100 < limit_time || limit_time == 1)
			return (false);
	}
}

void	eating_phase(t_philo_thread **p)
{
	print_msg((*p), EAT, 0, 1);
	(*p)->last_meal = get_time_in_ms();
	(*p)->meals_eaten++;
	if ((*p)->meals_defined)
	{
		pthread_mutex_lock((*p)->death_mutex);
		if ((*p)->meals_eaten == (*p)->meals_num)
			(*p)->table->finished_meals++;
		if ((*p)->table->finished_meals == (*p)->num_of_philos)
		{
			pthread_mutex_unlock((*p)->death_mutex);
			return ;
		}
		pthread_mutex_unlock((*p)->death_mutex);
	}
	ft_usleep((*p)->eat_time, *p);
	assign_bool_mutex(&(*p)->l_fork_taken, &(*p)->l_fork, false);
	assign_bool_mutex((*p)->r_fork_taken, (*p)->r_fork, false);
	if (everyone_has_eaten((*p)))
		return ;
	print_msg((*p), SLEEP, 0, 0);
	ft_usleep((*p)->sleep_time, *p);
	if (everyone_has_eaten((*p)))
		return ;
	print_msg((*p), THINK, 0, 0);
}

void	eat_left(t_philo_thread **p)
{
	bool	fork_is_free;

	fork_is_free = assign_bool_mutex(&(*p)->l_fork_taken, &(*p)->l_fork, true);
	if (fork_is_free == true)
	{
		print_msg((*p), FORK, 0, 0);
		(*p)->num_forks++;
	}
	fork_is_free = assign_bool_mutex((*p)->r_fork_taken, (*p)->r_fork, true);
	if (fork_is_free == true)
	{
		print_msg((*p), FORK, 0, 0);
		(*p)->num_forks++;
	}
	if ((*p)->num_forks == 2)
	{
		eating_phase(p);
		(*p)->num_forks = 0;
	}
}

void	eat_right(t_philo_thread **p)
{
	bool	fork_is_free;

	fork_is_free = assign_bool_mutex((*p)->r_fork_taken, (*p)->r_fork, true);
	if (fork_is_free == true)
	{
		print_msg((*p), FORK, 0, 0);
		(*p)->num_forks++;
	}
	fork_is_free = assign_bool_mutex(&(*p)->l_fork_taken, &(*p)->l_fork, true);
	if (fork_is_free == true)
	{
		print_msg((*p), FORK, 0, 0);
		(*p)->num_forks++;
	}
	if ((*p)->num_forks == 2)
	{
		eating_phase(p);
		(*p)->num_forks = 0;
	}
}

void	*routine(void *arg)
{
	t_philo_thread	*p;

	if (!arg || !wait_dinner((t_philo_thread *)arg, get_time_in_ms()))
		return (NULL);
	p = (t_philo_thread *)arg;
	p->last_meal = get_time_in_ms();
	if (p->id % 2 == 0)
		ft_usleep(p->eat_time * 0.1, p);
	while (no_death_detected(&(*p)))
	{
		if (p->meals_defined == false || p->meals_eaten < p->meals_num)
		{
			if (p->id % 2 == 0)
				eat_left(&p);
			else
				eat_right(&p);
		}
		if (p->meals_defined && p->meals_eaten == p->meals_num)
			break ;
	}
	return (NULL);
}
