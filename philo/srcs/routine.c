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
	int protect;
//
//	while (p->is_eating == false && *(p->dead_detected) == false
//		   && (p->meals_defined == false || p->meals_eaten < p->meals_num))

	while (mutex_check_if_can_eat(p))
	{
		if (p->last_meal + p->die_time < get_time_in_ms())
		{
			print_message(p, DIED, 1);
			return ;
		}
		protect = assign_bool_mutex(&p->l_fork_taken,&p->l_fork, true);
		if (protect == -1)
			return;
		if (protect == true)
		{
			print_message(p, FORK, 0);
			p->num_forks++;
		}
		protect = assign_bool_mutex(p->r_fork_taken, p->r_fork, true);
		if (protect == -1)
			return ;
		else if (protect == true && p->num_forks == 1)
		{
			print_message(p, FORK, 0);
			print_message(p, EAT, 0);
			p->is_eating = true;
			ft_usleep(p->eat_time);
			p->last_meal = get_time_in_ms();
			if (assign_bool_mutex(&p->l_fork_taken,&p->l_fork, false) == -1)
				return ;
			if (assign_bool_mutex(p->r_fork_taken,p->r_fork, false) == -1)
				return ;
			p->meals_eaten++;
			p->is_eating = false;
			p->num_forks = 0;
			print_message(p, SLEEP, 0);
			ft_usleep(p->sleep_time);
			print_message(p, THINK, 0);
		}
	}
}

//void	eat_right(t_philo_thread *p)
//{
//	int protect;
//
////	while (p->is_eating == false && *(p->dead_detected) == false
////		   && (p->meals_defined == false || p->meals_eaten < p->meals_num))
//	while (mutex_check_if_can_eat(p))
//	{
//		if (p->last_meal + p->die_time < get_time_in_ms())
//		{
//			print_message(p, DIED);
//			if (assign_bool_mutex(p->dead_detected, p->write_mutex, true))
//				return ;
//			p->is_dead = true;
////			*(p->dead_detected) = true;
//			return ;
//		}
//		protect = assign_bool_mutex(p->r_fork_taken,p->r_fork, true);
//		if (protect == -1)
//			return;
//		if (protect == true)
//		{
//			print_message(p, FORK);
//			p->num_forks++;
//		}
//		protect = assign_bool_mutex(&p->l_fork_taken, &p->l_fork, true);
//		if (protect == -1)
//			return ;
//		else if (protect == true && p->num_forks == 1)
//		{
//			print_message(p, FORK);
//			print_message(p, EAT);
//			p->is_eating = true;
//			ft_usleep(p->eat_time);
//			p->last_meal = get_time_in_ms();
//			if (assign_bool_mutex(p->r_fork_taken,
//								  p->r_fork, false) == -1)
//				return;
//			if (assign_bool_mutex(&p->l_fork_taken,
//								  &p->l_fork, false) == -1)
//			p->meals_eaten++;
//			p->is_eating = false;
//			print_message(p, SLEEP);
//			ft_usleep(p->sleep_time);
//			print_message(p, THINK);
//				return;
//		}
//	}
//}

void	eat(t_philo_thread *philo, int id)
{
	if (id % 2 == 0)
		ft_usleep(philo->eat_time / 2);
//	if (id % 2 == 0)
	eat_left(philo);
//	else
//		eat_right(philo);
}

void	*routine(void *arg)
{
	t_philo_thread	*p;

	if (!arg || !wait_dinner((t_philo_thread *) arg, get_time_in_ms()))
		return (NULL);
	p = (t_philo_thread *)arg;
//	while (*(p->dead_detected) == false
//		&& (p->meals_defined == false
//			|| p->meals_eaten < p->meals_num))
//	while (mutex_check_if_can_eat(p))
//	{
//		if (p->meals_eaten < p->meals_num)
//			break ;

//		if (p->id % 2 == 0)
		eat(p, p->id);
//		if (p->id % 2 == 1)
//			eat(p);
//	}
	return (NULL);
}

/*
  		print_message(philo, SLEEP);
		print_message(philo, FORK);
		print_message(philo, EAT);
		print_message(philo, THINK);
*/