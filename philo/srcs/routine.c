/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbernard <mbernard@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 08:44:55 by mbernard          #+#    #+#             */
/*   Updated: 2024/06/10 15:47:15 by mbernard         ###   ########.fr       */
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
		if (mutex_lock(philo->write_mutex) == false)
			return (false);
		if (*philo->dinner_started == true)
		{
			if (mutex_unlock(philo->write_mutex) == false)
				return (false);
			return (true);
		}
		if (*(philo->error_detected) == true)
		{
			mutex_unlock(philo->write_mutex);
			return (false);
		}
		if (mutex_unlock(philo->write_mutex) == false)
			return (false);
		limit_time = get_time_in_ms();
		if (time + 100 < limit_time || limit_time == 1)
			return (false);
	}
}

void	eat_left(t_philo_thread *p)
{
	while (p->is_eating == false && *(p->dead_detected) == false
		&& (p->meals_defined == false || p->meals_eaten < p->meals_num))
	{
			if (assign_bool_mutex(&p->l_fork_taken,
								  &p->l_fork, true) == false)
				return;
			print_message(p, FORK);
			if (assign_bool_mutex(p->right_fork_taken,
								  p->right_fork, true) == false)
				return;
			print_message(p, FORK);
			print_message(p, EAT);
			p->is_eating = true;
			ft_usleep(p->eat_time);
			p->last_meal = get_time_in_ms();
			p->is_eating = false;
			if (assign_bool_mutex(&p->l_fork_taken,
								  &p->l_fork, false) == false)
				return;
			print_message(p, FORK);
			if (assign_bool_mutex(p->right_fork_taken,
								  p->right_fork, false) == false)
				return;
	}
}

void	eat_right(t_philo_thread *p)
{
	int protect;

	while (p->is_eating == false && *(p->dead_detected) == false
		   && (p->meals_defined == false || p->meals_eaten < p->meals_num))
	{
		if (*p->right_fork_taken == false && p->l_fork_taken == false )
		{
			protect = assign_bool_mutex(&p->l_fork_taken,&p->l_fork, true);
			if (protect == -1)
				return;
			else if (protect == true)
				print_message(p, FORK);
			protect = assign_bool_mutex(p->right_fork_taken,p->right_fork, true);
			if (protect == -1)
				return ;
			else if (protect == true)
			{
				print_message(p, FORK);
				print_message(p, EAT);
				p->is_eating = true;
				ft_usleep(p->eat_time);
				p->last_meal = get_time_in_ms();
				p->is_eating = false;
				if (assign_bool_mutex(&p->l_fork_taken,
									  &p->l_fork, false) == -1)
					return;
				print_message(p, FORK);
				if (assign_bool_mutex(p->right_fork_taken,
									  p->right_fork, false) == -1)
					return;
			}
		}
	}
}
void	eat(t_philo_thread *philo, int id)
{

	if (id % 2 == 0)
		eat_left(philo);
	else
		eat_right(philo);
}

void	*routine(void *arg)
{
	t_philo_thread	*philo;

	if (!arg || !wait_dinner((t_philo_thread *) arg, get_time_in_ms()))
		return (NULL);
	philo = (t_philo_thread *)arg;
	while (*(philo->dead_detected) == false
		&& (philo->meals_defined == false
			|| philo->meals_eaten < philo->meals_num))
	{
		if (philo->id % 2 == 0)
			ft_usleep(1);
//		if (philo->id % 2 == 0)
		eat(philo, philo->id);
		philo->meals_eaten++;
//		if (philo->id % 2 == 1)
//			eat(philo);
	}
	return (NULL);
}

/*
  		print_message(philo, SLEEP);
		print_message(philo, FORK);
		print_message(philo, EAT);
		print_message(philo, THINK);
*/