/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbernard <mbernard@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 08:44:55 by mbernard          #+#    #+#             */
/*   Updated: 2024/06/14 09:31:01 by mbernard         ###   ########.fr       */
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
		pthread_mutex_lock(philo->write_mutex);
		if (*philo->dinner_started == true)
		{
			pthread_mutex_unlock(philo->write_mutex);
			return (true);
		}
		if (*(philo->error_detected) == true)
		{
			pthread_mutex_unlock(philo->write_mutex);
			return (false);
		}
		pthread_mutex_unlock(philo->write_mutex);
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
//	(*p)->num_forks = 0;
	if ((*p)->meals_defined == false || (*p)->meals_eaten < (*p)->meals_num)
	{
		print_message((*p), SLEEP, 0);
		ft_usleep((*p)->sleep_time);
		print_message((*p), THINK, 0);
	}
/*	else
	{
		pthread_mutex_lock((*p)->write_mutex);
		printf("%d HAS EATEN ENOUGH !\n", (*p)->id);
		pthread_mutex_unlock((*p)->write_mutex);
	}*/
}

void	eat_left(t_philo_thread **p)
{
	bool fork_is_free;

	while (mutex_check_if_can_eat(*p))
	{
		if ((*p)->last_meal + (*p)->die_time < get_time_in_ms())
		{
			print_message((*p), DIED, 1);
			return ;
		}
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
}

void	eat_right(t_philo_thread **p)
{
	bool	fork_is_free;

	while (mutex_check_if_can_eat(*p))
	{
		if ((*p)->last_meal + (*p)->die_time < get_time_in_ms())
		{
			print_message((*p), DIED, 1);
			return ;
		}
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
}

void	eat(t_philo_thread *philo, int id)
{
	if (id % 2 == 0)
		ft_usleep(philo->eat_time / 2);
	if (id % 2 == 0)
		eat_left(&philo);
	else
		eat_right(&philo);
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