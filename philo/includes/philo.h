/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbernard <mbernard@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 11:56:09 by mbernard          #+#    #+#             */
/*   Updated: 2024/06/07 08:41:43 by mbernard         ###   ########.fr       */
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
number_of_philosophers\tdie_time\teat_time\tsleep_time\t\
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

/*
Check the code of Philo for the following things and ask for an explanation.
Check if there is one thread per philosopher.
Check there's only one fork per philosopher.
<<<<<<< Updated upstream
Check if there is a mutex per fork and
that it's used to check the fork value and/or change it.
=======
Check if there is a mutex per fork and that it's used to
 check the fork value and/or change it.
>>>>>>> Stashed changes
Check the output should never produce a scrambled view.
Check how the death of a philosopher is checked and if there is a mutex
to protect that a philosopher dies and start eating at the same time.
*/

typedef struct s_philo_thread
{
	pthread_t		thread;
	int				id;
	bool			is_eating;
	int				meals_eaten;
	u_int64_t		last_meal;
	bool			left_fork_taken;
	bool			*right_fork_taken;
	pthread_mutex_t	death_mutex;
	pthread_mutex_t	left_fork;
	pthread_mutex_t	*right_fork;
	pthread_mutex_t	*write_mutex;
	bool			is_dead;
	bool			*dead_detected;
	bool			*dinner_started;
	bool			*meals_defined;
<<<<<<< Updated upstream
	int				num_of_meals;
	unsigned long	*start_time;
=======
	int				meals_num;
	unsigned int	start_time;
>>>>>>> Stashed changes
}					t_philo_thread;

typedef struct s_table
{
	bool			meals_defined;
	bool			dead_detected;
	int				num_of_philos;
	int				die_time;
	int				eat_time;
	int				sleep_time;
	int				meals_num;
	bool			dinner_started;
<<<<<<< Updated upstream
	unsigned long	start_time;
=======
	unsigned int	start_time;
>>>>>>> Stashed changes
	pthread_mutex_t	write_mutex;
	t_philo_thread	*philos;
}					t_table;

//////////////////////		CHECK AND ASSIGN 		////////////////////////////
bool				check_arguments_and_assign(char **av, t_table *p);
//////////////////////		UTILS						////////////////////////
void				*ft_calloc(size_t nmemb, size_t size);
int					ft_usleep(useconds_t time);
u_int64_t			get_time_in_ms(void);
//////////////////////		ROUTINE 				////////////////////////////
void				*routine(void *arg);
//////////////////////		MESSAGES 				////////////////////////////
<<<<<<< Updated upstream
void				print_message(t_philo_thread *philo, char *msg);
//////////////////////		INIT	 				////////////////////////////
bool				init_philo_table(t_philo_table *table);
//////////////////////		DESTROY	 				////////////////////////////
void				destroy_philo_table(t_philo_table *philo_table);
=======
void				print_msg(t_table *table, t_philo_thread *philo, char *msg);
//////////////////////		INIT	 				////////////////////////////
bool				init_philo_table(t_table *table);
//////////////////////		DESTROY	 				////////////////////////////
void				destroy_philo_table(t_table *philo_table);
>>>>>>> Stashed changes
#endif // PHILO_H
