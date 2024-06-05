/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbernard <mbernard@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 11:56:09 by mbernard          #+#    #+#             */
/*   Updated: 2024/06/04 13:30:42 by mbernard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <limits.h>
# include <pthread.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>
# include <sys/types.h>
# include <unistd.h>

typedef struct s_philo_table
{
	bool	table_assigned;
	bool	meals_defined;
	int		num_of_philos;
	int		time_to_die;
	int		time_to_eat;
	int		time_to_sleep;
	int		number_of_meals;
}			t_philo_table;

//////////////////////				UTILS 			////////////////////////////
//////////////////////		CHECK AND ASSIGN 		////////////////////////////
void		check_arguments_and_assign(char **av, t_philo_table *philo_table);

// int	ft_atol_int(const char *str);
// int	ft_usleep(useconds_t time);
// u_int64_t	get_time(void);

#endif // PHILO_H
