/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbernard <mbernard@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 11:56:09 by mbernard          #+#    #+#             */
/*   Updated: 2024/06/14 13:04:28 by mbernard         ###   ########.fr       */
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
Check if there is a mutex per fork and
that it's used to check the fork value and/or change it.
Check the output should never produce a scrambled view.
Check how the death of a philosopher is checked and if there is a mutex
to protect that a philosopher dies and start eating at the same time.
*/
typedef struct s_table	t_table;

typedef struct s_philo_thread
{
	pthread_t		thread;
	int				id;
	bool			thread_created;
	bool			mutex_created;
	int				meals_eaten;
	u_int64_t		last_meal;
	int				num_forks;
	bool			l_fork_taken;
	bool			*r_fork_taken;
	pthread_mutex_t	l_fork;
	pthread_mutex_t	*r_fork;
	pthread_mutex_t	*death_mutex;
	pthread_mutex_t	*write_mutex;
	bool			*dead_detected;
	bool			*error_detected;
	bool			*everyone_has_eaten;
	bool			*dinner_started;
	bool			meals_defined;
	int				num_of_philos;
	int				die_time;
	int				eat_time;
	int				sleep_time;
	int				meals_num;
	u_int64_t		*start_time;
//	t_table			*table;
}					t_philo_thread;

typedef struct s_table
{
	bool			meals_defined;
	bool			dead_detected;
	bool			dinner_started;
	bool			error_detected;
	bool			everyone_has_eaten;
	int				num_of_philos;
	int				die_time;
	int				eat_time;
	int				sleep_time;
	int				meals_num;
	u_int64_t		start_time;
	pthread_mutex_t	write_mutex;
	pthread_mutex_t	death_mutex;
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
void				print_message(t_philo_thread *p, char *msg, bool is_dead);
//////////////////////		INIT	 				////////////////////////////
bool				init_philo_table(t_table *table);
bool				init_mutex(t_table *table);
//////////////////////		MUTEX	 				////////////////////////////
bool				no_death_detected(t_philo_thread *p);
bool 				assign_bool_mutex(bool *var, pthread_mutex_t *m, bool value);

//////////////////////		DESTROY	 				////////////////////////////
void				destroy_philo_table(t_table *table);
#endif // PHILO_H
