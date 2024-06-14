/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbernard <mbernard@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 08:44:55 by mbernard          #+#    #+#             */
/*   Updated: 2024/06/14 10:53:12 by mbernard         ###   ########.fr       */
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
		if (*philo->dinner_started == true)
		{
			pthread_mutex_unlock(philo->death_mutex);
			return (true);
		}
		if (*(philo->error_detected) == true)
		{
			pthread_mutex_unlock(philo->death_mutex);
			return (false);
		}
		pthread_mutex_unlock(philo->death_mutex);
		limit_time = get_time_in_ms();
		if (time + 100 < limit_time || limit_time == 1)
			return (false);
	}
}

void eating_phase(t_philo_thread **p)
{
	print_message((*p), EAT, 0);
	(*p)->last_meal = get_time_in_ms();
	ft_usleep((*p)->eat_time);
	assign_bool_mutex(&(*p)->l_fork_taken,&(*p)->l_fork, false);
	assign_bool_mutex((*p)->r_fork_taken,(*p)->r_fork, false);
	(*p)->meals_eaten++;
	if ((*p)->meals_defined == false || (*p)->meals_eaten < (*p)->meals_num
		&& everyone_has_eaten((*p), 0) == false)
	{
		print_message((*p), SLEEP, 0);
		ft_usleep((*p)->sleep_time);
		print_message((*p), THINK, 0);
	}
}

void	eat_left(t_philo_thread **p)
{
	bool fork_is_free;

	fork_is_free = assign_bool_mutex(&(*p)->l_fork_taken, &(*p)->l_fork, true);
	if (fork_is_free == true)
	{
		print_message((*p), FORK, 0);
		(*p)->num_forks++;
	}
	fork_is_free = assign_bool_mutex((*p)->r_fork_taken, (*p)->r_fork,
									 true);
	if (fork_is_free == true)
	{
		print_message((*p), FORK, 0);
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
		print_message((*p), FORK, 0);
		(*p)->num_forks++;
	}
	fork_is_free = assign_bool_mutex(&(*p)->l_fork_taken, &(*p)->l_fork,
									 true);
	if (fork_is_free == true)
	{
		print_message((*p), FORK, 0);
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

	if (!arg || !wait_dinner((t_philo_thread *) arg, get_time_in_ms()))
		return (NULL);
	p = (t_philo_thread *)arg;
	if (p->id % 2 == 0)
		ft_usleep(p->eat_time / 2);
	while (no_death_detected(&(*p)))
	{
		if (p->last_meal + p->die_time < get_time_in_ms())
		{
			print_message(p, DIED, 1);
			break ;
		}
		if (p->meals_defined == false || p->meals_eaten < p->meals_num)
		{
			if (p->id % 2 == 0)
				eat_left(&p);
			else
				eat_right(&p);
		}
		if(p->meals_defined == true && everyone_has_eaten(p, 1) == true)
			break ;
	}
	return (NULL);
}
