/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbernard <mbernard@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 11:56:09 by mbernard          #+#    #+#             */
/*   Updated: 2024/06/06 11:00:57 by mbernard         ###   ########.fr       */
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

# ifndef PHILO_200_ERROR
#  define PHILO_200_ERROR \
	"Error: number of philosophers should be inferior to 200\n"
# endif

# ifndef WRONG_NUMBER_OF_ARGUMENTS
#  define WRONG_NUMBER_OF_ARGUMENTS \
	"Error: wrong number of arguments\n\
Correct format should contains 5 or 6 arguments :\n\
number_of_philosophers	time_to_die	time_to_eat	time_to_sleep\t\
[number_of_times_each_philosopher_must_eat]\n"
# endif

# ifndef FORK
#  define FORK " has taken a fork\n"
# endif

# ifndef EAT
#  define EAT " is eating\n"
# endif

# ifndef THINK
#  define THINK " is thinking\n"
# endif

# ifndef SLEEP
#  define SLEEP " is sleeping\n"
# endif

# ifndef DIED
#  define DIED " died\n"
# endif

typedef struct s_philo_thread
{
	pthread_t		thread;
	int				id;
	bool			is_dead;
	bool			is_eating;
	int				meals_eaten;
	u_int64_t		last_meal;
//	bool			lock;
	pthread_mutex_t	mutex;
}					t_philo_thread;

typedef struct s_philo_table
{
	bool			table_assigned;
	bool			meals_defined;
	int				num_of_philos;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				number_of_meals;
	t_philo_thread	*philos;
}					t_philo_table;

//////////////////////		CHECK AND ASSIGN 		////////////////////////////
void				check_arguments_and_assign(char **av,
						t_philo_table *philo_table);
//////////////////////		UTILS						////////////////////////
int					ft_usleep(useconds_t time);
u_int64_t			get_time_in_ms(void);
//////////////////////		ROUTINE 				////////////////////////////
void				*routine(void *arg);

#endif // PHILO_H
